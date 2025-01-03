#include "chassis_behavior.h"
#include "arm_math.h"

/************************参数设定************************/
#define CHASSIS_DISABLE 0
#define CHASSIS_SPEED_MAX_X 12//底盘X方向最大速度3
#define CHASSIS_SPEED_MAX_Y 12 //底盘Y方向最大速度3
#define CHASSIS_SPEED_MAX_W 0.009f //底盘自转角速度最大速度

//底盘参数设置
#define CHASSIS_LENGTH 254      //底盘长的一半
#define CHASSIS_WIDTH 254       //底盘宽的一半
#define WHEEL_PERIMETER 960       //车轮周长
#define CHASSIS_DECELE_RATIO  19 //电机减速比
#define CHASSIS_CALI_ANGLE 0.f

//宏定义函数
#define LIMIT_ANGLE(angle) ((angle) < 0 ? fmod((angle), 360) + 360 : fmod((angle), 360))
#define limit(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\

/***********************变量定义***********************/
Chassis_WhlVct_Typedef Vector_F;  //左上
Chassis_WhlVct_Typedef Vector_B;  //右下

extern bool TeamColor;
extern M6020_TypeDef P_stMotor_Gimbal_YawL; //云台大yaw参数结构体
extern M6020_TypeDef P_stMotor_Gimbal_YawH; //云台小yaw参数结构体

Chassis_TypeDef P_stChassis = {Chassis_BlackOut};//底盘参数结构体
/**
 * @name    底盘控制任务
 * @brief   通过遥控器挡位控制底盘模式
 * @param   无
 * @retval  无
*/

float vx,vy,vw;         //底盘速度
float vx_1,vy_1,vw_1;   //底盘预处理速度
float a,b; 
void Task_ChassisCtrl(void)
{
    portTickType CurrentControlTick = 0;
    
    u16 countT  = 0; //用于记录启动时的对应时刻
    while(1)
    {
        switch(P_stRemoteData_Recv.Switch_B)//获取遥控器挡位
        {
            case Down:  // 全部下电
            {
                P_stChassis.State = Chassis_BlackOut;
                Chassis_SetMode(&P_stChassis,Chassis_NoFollow);//运动模式设置为底盘跟随

                vx = 0;
                vy = 0;
                vw = 0;
                countT = 0;
                
                    P_stChassis.RstPara.Initial_Yaw = 0;
                    P_stChassis.RstPara.Initial_Encoder = 0;  //记录初始编码器
                    P_stChassis.RstPara.Initial_Gyro = 0;       //记录当前陀螺仪Yaw轴数据
                    P_stChassis.RstPara.Pos_Diff = 0;        //记录当前云台与底盘前进中心的差值
                    P_stChassis.RstPara.Converted_GyroYaw = 0;
                
            }break;

            case Middle:   //底盘以云台朝向为正方向移动             //Switch_B为中间挡位时，根据Switch_C的值进行判断
            {
                switch(P_stRemoteData_Recv.Switch_C)
                {
                    case Down:  //遥控模式
                    {
                        if(countT ++ < 1000)
                        {         
//                            P_stChassis.RstPara.Initial_Encoder = P_stMotor_Gimbal_Yaw.RecvData.Raw_Angle;  //记录初始编码器
//                            P_stChassis.RstPara.Initial_Gyro = P_stHi219m.Continuous_Yaw;       //记录当前陀螺仪Yaw轴数据
//                            P_stChassis.RstPara.Pos_Diff = P_stChassis.Cali.Cali_Yaw_180;        //记录当前云台与底盘前进中心的差值
//                            
//                            P_stChassis.RstPara.Converted_GyroYaw = 
//                                            LIMIT_ANGLE(P_stChassis.RstPara.Initial_Gyro + P_stChassis.Cali.Cali_Yaw_180);
//                                                        //陀螺仪加上 当前云台与底盘前进中心的差值 为当前云台朝向 对角度值取模
//                            P_stChassis.RstPara.Initial_Yaw = P_stChassis.RstPara.Converted_GyroYaw ;
                        P_stChassis.State = Chassis_BlackOut;
                        }
                        else
                        {
                            countT = 2600;
                            P_stChassis.State = Chassis_Working;
                            Chassis_SetMode(&P_stChassis,Chassis_Fix);//运动模式设置为底盘不跟随移动
                        }

                    }break;

                    case Middle: //发射准备，启动摩擦轮
                    {
                        if(countT ++ < 1000)
                        {
//                            P_stChassis.RstPara.Initial_Encoder = P_stMotor_Gimbal_Yaw.RecvData.Raw_Angle;  //记录初始编码器
//                            P_stChassis.RstPara.Initial_Gyro = P_stHi219m.Continuous_Yaw;       //记录当前陀螺仪Yaw轴数据
//                            P_stChassis.RstPara.Pos_Diff = P_stChassis.Cali.Cali_Yaw_180;        //记录当前云台与底盘前进中心的差值
//                            
//                            P_stChassis.RstPara.Converted_GyroYaw = 
//                                            LIMIT_ANGLE(P_stChassis.RstPara.Initial_Gyro + P_stChassis.Cali.Cali_Yaw_180);
//                                                        //陀螺仪加上 当前云台与底盘前进中心的差值 为当前云台朝向 对角度值取模
//                            P_stChassis.RstPara.Initial_Yaw = P_stChassis.RstPara.Converted_GyroYaw ;

						P_stChassis.State = Chassis_BlackOut;
                        }
                        else
                        {
                            countT = 2600;
                            P_stChassis.State = Chassis_Working;
                            Chassis_SetMode(&P_stChassis,Chassis_Navigator);//运动模式设置为底盘不跟随
                        }
                    }break;

                    case Up:    //自瞄模式
                    {
                        if(countT++ < 1000)
						{									
//                            P_stChassis.RstPara.Initial_Encoder = P_stMotor_Gimbal_Yaw.RecvData.Raw_Angle;  //记录初始编码器
//                            P_stChassis.RstPara.Initial_Gyro = P_stHi219m.Continuous_Yaw;       //记录当前陀螺仪Yaw轴数据
//                            P_stChassis.RstPara.Pos_Diff = P_stChassis.Cali.Cali_Yaw_180;        //记录当前云台与底盘前进中心的差值
//                            
//                            P_stChassis.RstPara.Converted_GyroYaw = 
//                                            LIMIT_ANGLE(P_stChassis.RstPara.Initial_Gyro + P_stChassis.Cali.Cali_Yaw_180);
//                                                        //陀螺仪加上 当前云台与底盘前进中心的差值 为当前云台朝向 对角度值取模
//                            P_stChassis.RstPara.Initial_Yaw = P_stChassis.RstPara.Converted_GyroYaw ;
						P_stChassis.State = Chassis_BlackOut;
						}
						else
						{
							countT = 2600;
							P_stChassis.State = Chassis_Working;
							Chassis_SetMode(&P_stChassis,Chassis_Navigator);//运动模式设置为底盘跟随
						}
                    }break;
                }
            }break;   

            case Up: //底盘以初始云台或复位后云台朝向为正方向移动              //Switch_B为上挡位时，根据Switch_C的值进行判断
            {
                switch(P_stRemoteData_Recv.Switch_C)
                {
                    case Down:  //遥控模式
                    {
                        if(countT++ < 1000)
				        {		
//                    P_stChassis.RstPara.Initial_Yaw = 0;
//                    P_stChassis.RstPara.Initial_Encoder = 0;  //记录初始编码器
//                    P_stChassis.RstPara.Initial_Gyro = 0;       //记录当前陀螺仪Yaw轴数据
//                    P_stChassis.RstPara.Pos_Diff = 0;        //记录当前云台与底盘前进中心的差值
//                    P_stChassis.RstPara.Converted_GyroYaw = 0;    
                            
							P_stChassis.State = Chassis_BlackOut;				        
                        }
				        else
				        {
					        countT = 2600;
					        P_stChassis.State = Chassis_Working;
					        Chassis_SetMode(&P_stChassis,Chassis_Spin);//运动模式设置为底盘旋转
				        }
                    }break;

                    case Middle://导航测试模式
                    {
                        if(countT++ < 1000)
				        {		
//                    P_stChassis.RstPara.Initial_Yaw = 0;
//                    P_stChassis.RstPara.Initial_Encoder = 0;  //记录初始编码器
//                    P_stChassis.RstPara.Initial_Gyro = 0;       //记录当前陀螺仪Yaw轴数据
//                    P_stChassis.RstPara.Pos_Diff = 0;        //记录当前云台与底盘前进中心的差值
//                    P_stChassis.RstPara.Converted_GyroYaw = 0;

							P_stChassis.State = Chassis_BlackOut;				        
                        }
				        else
				        {
					        countT = 2600;
					        P_stChassis.State = Chassis_Working;
					        Chassis_SetMode(&P_stChassis,Chassis_AI);//运动模式设置为AI模式
				        }
                    }break;

                    case Up:    //AI模式
                    {
                        if(countT++ < 1000)
				        {		
//                    P_stChassis.RstPara.Initial_Yaw = 0;
//                    P_stChassis.RstPara.Initial_Encoder = 0;  //记录初始编码器
//                    P_stChassis.RstPara.Initial_Gyro = 0;       //记录当前陀螺仪Yaw轴数据
//                    P_stChassis.RstPara.Pos_Diff = 0;        //记录当前云台与底盘前进中心的差值
//                    P_stChassis.RstPara.Converted_GyroYaw = 0;

							P_stChassis.State = Chassis_BlackOut;				        
                        }
				        else
				        {
					        countT = 2600;
					        P_stChassis.State = Chassis_Working;
					        Chassis_SetMode(&P_stChassis,Chassis_AI);//运动模式设置为AI模式
				        }
                    }break;
                }
            }break;
        }
        Chassis_Control(vx,vy,vw);
        vTaskDelayUntil(&CurrentControlTick, 1/portTICK_RATE_MS);
    }
}

/**
 * @name    底盘控制函数
 * @brief   控制底盘运动,通过分配速度实现输出电机控制电流和舵角的调整
 * @param   vx:x轴速度 vy:y轴速度 vw:自转速度
 * @retval  无
 */
void Chassis_Control(float vx,float vy,float vw)
{
    static float32_t chassis_rudder_angle[2];       //舵向轮目标角度
    static float32_t chassis_rudder_crtangle[2];    //舵向轮当前角度
    static float32_t chassis_rudder_cvtangle[2];    //舵向轮就近转角目标角度
    /*记录当前舵向电机角度*/
    chassis_rudder_crtangle[0] = P_stMotor_RudderF.RecvData.Custom_Angle;
    chassis_rudder_crtangle[1] = P_stMotor_RudderB.RecvData.Custom_Angle;

    /*6020舵向轮目标角度计算 if((vy - vw * SIN45 != 0) && (vy + vw * COS45 != 0))*/
    if(vx != 0  && vy != 0 && vw != 0)     //保证除数不为零
    {
        chassis_rudder_angle[0] = atan2(vx + vw * SIN45,vy + vw * COS45);
        chassis_rudder_angle[1] = atan2(vx - vw * COS45,vy - vw * SIN45);
    }
    else    //舵向轮角度默认朝向正右方
    {
        chassis_rudder_angle[0] = 0;
        chassis_rudder_angle[1] = 0;
    }
    /*3508动力轮目标速度计算*/
    
}

/**
 * @name 底盘参数初始化
 * @brief   初始化底盘参数
 * @param   无
 * @retval  无
 */
void configChassis_ParaInit(void)
{
    /*舵向轮自定义零点值设置*/
    P_stMotor_RudderF.RecvData.Custom_Angle_Zero = 165.62f;//左前
    P_stMotor_RudderB.RecvData.Custom_Angle_Zero = 0.f;//右后
    /*底盘结构体参数初始化*/
    
    /*底盘舵向轮、动力轮pid参数初始化*/
    
    
}
/**
 * @name    底盘工作状态设置
 * @brief   设置底盘工作状态
 * @param   st_data:底盘参数结构体 state:工作状态
 * @retval  无
 */
void Chassis_SetWorkState(Chassis_TypeDef* st_data,e_Chassis_State state)
{
	st_data->State = state;
}

/**
 * @name    底盘运动模式设置
 * @brief   设置底盘运动模式
 * @param   st_data:底盘参数结构体 mode:运动模式
 * @retval  无
 */
static void Chassis_SetMode(Chassis_TypeDef *st_data,e_ChassisMotion_State mode)
{
    st_data->Mode = mode;

    switch(st_data->Mode)
    {
        case Chassis_Fix:
        {
            vx = vx_1;
			vy = vy_1;
			vw = vw_1;
                
			limit(vx,-CHASSIS_SPEED_MAX_X,CHASSIS_SPEED_MAX_X);
			limit(vy,-CHASSIS_SPEED_MAX_Y,CHASSIS_SPEED_MAX_Y);
            limit(vw,-CHASSIS_SPEED_MAX_W,CHASSIS_SPEED_MAX_W);
        }break;
        case Chassis_Follow:
        {
            
        }break;
        case Chassis_NoFollow:
        {
            
        }break;
        case Chassis_Spin:
        {
            
        }break;
        case Chassis_AI:
        {

        }break;

        default:
        break;

    }
}


static void Chassis_Cali_Calc(Chassis_TypeDef* st_data)   //底盘距中心值校准计算
{
//        P_stChassis.Cali.Cali_Yaw_180 = (float)(((P_stMotor_Gimbal_Yaw.RecvData.Raw_Angle - CHASSIS_CALI_ANGLE) / 360.0f) * 360.0);
    
        if (P_stChassis.Cali.Cali_Yaw_180 > 180)    P_stChassis.Cali.Cali_Yaw_180 -= 360;  //将范围调整至-180~+180度
}
