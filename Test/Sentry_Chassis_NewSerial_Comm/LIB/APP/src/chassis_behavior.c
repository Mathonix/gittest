#include "chassis_behavior.h"
#include "arm_math.h"

/************************参数设定************************/
#define CHASSIS_DISABLE 0
#define CHASSIS_SPEED_MAX_X 12//底盘X方向最大速度3
#define CHASSIS_SPEED_MAX_Y 12 //底盘Y方向最大速度3
#define CHASSIS_SPEED_MAX_W 0.009f //底盘Y方向最大速度

//底盘参数设置
#define CHASSIS_LENGTH 254      //底盘长的一半
#define CHASSIS_WIDTH 254       //底盘宽的一半
#define WHEEL_PERIMETER 960       //车轮周长
#define CHASSIS_DECELE_RATIO  19 //底盘减速比

/***********************变量定义***********************/
float Gimbal_Gyro_Continuous_Yaw; //云台陀螺仪连续Yaw角度
float Gimbal_Gyro_Initial_Yaw; //云台陀螺仪初始Yaw角度
extern bool TeamColor;
extern M6020_TypeDef P_stMotor_Gimbal_YawL; //云台大yaw参数结构体
extern M6020_TypeDef P_stMotor_Gimbal_YawH; //云台小yaw参数结构体

Chassis_TypeDef P_stChassis ={Chassis_BlackOut};//底盘参数结构体
/**
 * @name    底盘控制任务
 * @brief   通过遥控器挡位控制底盘模式
 * @param   无
 * @retval  无
 */
float vx,vy,vw; 
float vx_1,vy_1,vw_1;
float Reset_Gyro_Angle;
float Reset_Encoder_Angle;
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
                Reset_Gyro_Angle = 0; //重置陀螺仪复位角度
                Reset_Encoder_Angle = 0; //重置编码器复位角度
                Chassis_SetMode(&P_stChassis,Chassis_Follow);//运动模式设置为底盘跟随

                vx_1 = 0;
                vy_1 = 0;
                vw_1 = 0;
                countT = 0;
                
                
                
            }break;

            case Middle:   //底盘以云台朝向为正方向移动             //Switch_B为中间挡位时，根据Switch_C的值进行判断
            {
                switch(P_stRemoteData_Recv.Switch_C)
                {
                    case Down:  //遥控模式
                    {
                        if(countT ++ < 1000)
                        {

                            P_stChassis.Init_Direction.Gyro_Direction = P_stHi219m.Continuous_Yaw; //记录复位结束时的底盘陀螺仪角度	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //记录复位结束时的大Yaw编码器角度
							P_stChassis.State = Chassis_BlackOut;
                        }
                        else
                        {
                            countT = 2600;
                            P_stChassis.State = Chassis_Working;
                            if(P_stRemoteData_Recv.Switch_D == Down)
                            Chassis_SetMode(&P_stChassis,Chassis_Follow);//运动模式设置为底盘跟随移动
                            else if(P_stRemoteData_Recv.Switch_D == Up)
                            Chassis_SetMode(&P_stChassis,Chassis_Spin);//运动模式设置为小陀螺
                        }

                    }break;

                    case Middle: //遥控模式，Switch_D的多数功能在云台实现
                    {
                        if(countT ++ < 1000)
                        {
                            P_stChassis.Init_Direction.Gyro_Direction = P_stHi219m.Continuous_Yaw; //记录复位结束时的陀螺仪角度	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //记录复位结束时的大Yaw编码器角度	
							P_stChassis.State = Chassis_BlackOut;
                        }
                        else
                        {
                            countT = 2600;
                            P_stChassis.State = Chassis_Working;
                            Chassis_SetMode(&P_stChassis,Chassis_NoFollow);//运动模式设置为底盘不跟随
                            //Switch_D的功能在云台实现
                        }
                    }break;

                    case Up:    //自瞄模式
                    {
                        if(countT++ < 1000)
						{									
							P_stChassis.Init_Direction.Gyro_Direction = P_stHi219m.Continuous_Yaw; //记录复位结束时的陀螺仪角度	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //记录复位结束时的大Yaw编码器角度	
							P_stChassis.State = Chassis_BlackOut;
						}
						else
						{
							countT = 2600;
							P_stChassis.State = Chassis_Working;
							Chassis_SetMode(&P_stChassis,Chassis_Spin);//运动模式设置为底盘跟随
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
							P_stChassis.Init_Direction.Gyro_Direction = P_stHi219m.Continuous_Yaw; //记录复位结束时的陀螺仪角度	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //记录复位结束时的大Yaw编码器角度	
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
							P_stChassis.Init_Direction.Gyro_Direction = Gimbal_Gyro_Continuous_Yaw; //记录复位结束时的陀螺仪角度	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //记录复位结束时的大Yaw编码器角度	
							P_stChassis.State = Chassis_BlackOut;				        
                        }
				        else
				        {
					        countT = 2600;
					        P_stChassis.State = Chassis_Working;
					        Chassis_SetMode(&P_stChassis,Chassis_AI);//运动模式设置为AI模式
				        }
                    }break;

                    case Up:    //AI模式，烧饼，启动！！！
                    {
                        if(countT++ < 1000)
				        {		
							P_stChassis.Init_Direction.Gyro_Direction = Gimbal_Gyro_Continuous_Yaw; //记录复位结束时的陀螺仪角度	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //记录复位结束时的大Yaw编码器角度	
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

    
}

/**
 * @name 底盘参数初始化
 * @brief   初始化底盘参数
 * @param   无
 * @retval  无
 */
void configChassis_ParaInit(void)
{


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
            vx=vx_1;
			vy=vy_1;
			vw = vw_1;
                
			limit(vx,-CHASSIS_SPEED_MAX_X,CHASSIS_SPEED_MAX_X);
			limit(vy,-CHASSIS_SPEED_MAX_Y,CHASSIS_SPEED_MAX_Y);
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
