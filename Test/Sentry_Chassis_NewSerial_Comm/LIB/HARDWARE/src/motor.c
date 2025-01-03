#include "motor.h"

M3508_TypeDef P_stMotor_ChassisF = {1};//底盘左前轮电机
M3508_TypeDef P_stMotor_ChassisB = {2};//底盘右后轮电机

M6020_TypeDef P_stMotor_SteerF = {7};  //底盘左前舵电机
M6020_TypeDef P_stMotor_SteerB = {8};  //底盘右后舵电机

M6020_TypeDef P_stMotor_Gimbal_YawH ={5};//云台小Yaw轴电机
M6020_TypeDef P_stMotor_Gimbal_YawL ={6};//云台大Yaw轴电机
M6020_TypeDef P_stMotor_Gimbal_Pitch ={7};//云台Pitch轴电机

int8_t Reset_yaw;
extern float vx,vy,vw;

/*******************************************************************************
* Function Name  : void configMotor_ParaInit(void)
* Description    : 底盘电机与YAW电机静态PID设置;
* Input          : 无
* Output         : 无
* Return         : 无
*******************************************************************************/ 
//电机参数初始化
void configMotor_ParaInit(void)
{	
//	//底盘电机配置
//	//左
//	fnPID_SetPara_P_I_D(&P_stMotor_ChassisL.SpeedPID,5,0,0);
//	fnPID_SetPara_IM(&P_stMotor_ChassisL.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_ChassisL.SpeedPID,8000);

//	//前
//	fnPID_SetPara_P_I_D(&P_stMotor_ChassisF.SpeedPID,5,0,0);
//	fnPID_SetPara_IM(&P_stMotor_ChassisF.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_ChassisF.SpeedPID,8000);
//	
//	//后
//	fnPID_SetPara_P_I_D(&P_stMotor_ChassisB.SpeedPID,5,0,0);
//	fnPID_SetPara_IM(&P_stMotor_ChassisB.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_ChassisB.SpeedPID,8000);
//	
//	//右
//	fnPID_SetPara_P_I_D(&P_stMotor_ChassisR.SpeedPID,5,0,0);
//	fnPID_SetPara_IM(&P_stMotor_ChassisR.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_ChassisR.SpeedPID,8000);
//	//云台电机配置
//	//yaw轴电机速度环
//	fnPID_SetPara_P_I_D(&P_stMotor_Gimbal_Yaw.SpeedPID,98,0,0);
//	fnPID_SetPara_IM(&P_stMotor_Gimbal_Yaw.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_Gimbal_Yaw.SpeedPID,25000);
//	//角度环
//	fnPID_SetPara_P_I_D(&P_stMotor_Gimbal_Yaw.AnglePID,5.87,0,0);
//	fnPID_SetPara_IM(&P_stMotor_Gimbal_Yaw.AnglePID,1000);
//	fnPID_SetPara_OM(&P_stMotor_Gimbal_Yaw.AnglePID,3000);
//	
}

/*******************************************************************************
* Function Name  : void fnMotor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg)
* Description    : Can数据解析;
* Input          : 电机ID
* Output         : 无
* Return         : 无
*******************************************************************************/ 
void fnMotor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg)
{
	if(canx == CAN1)
	{
		//根据对应ID,进行数据解析
			switch(msg->StdId)
			{
			case MOTOR_CHASSIS_F_CAN_ID:
			{
				s_fnM3508_RawDataDecode(&P_stMotor_ChassisF,msg);//原始数据解析
			}break;
			
			case MOTOR_CHASSIS_B_CAN_ID:
			{
				s_fnM3508_RawDataDecode(&P_stMotor_ChassisB,msg);//原始数据解析
			}break;
			
			case MOTOR_STEER_F_CAN_ID:
			{
				s_fnM6020_RawDataDecode(&P_stMotor_SteerF,msg);//原始数据解析
			}break;
			
			case MOTOR_STEER_B_CAN_ID:
			{
				s_fnM6020_RawDataDecode(&P_stMotor_SteerB,msg);//原始数据解析
			}break;
			
			default:
			{
			}break;
		}
	}
	else if(canx == CAN2)
	{
		//根据对应ID,进行数据解析
		switch(msg->StdId)
		{

			case MOTOR_GIMBAL_YAWL_CAN_ID:
			{
				s_fnM6020_RawDataDecode(&P_stMotor_Gimbal_YawL,msg);//原始数据解析
			}break;

            case MOTOR_GIMBAL_YAWH_CAN_ID:
            {
                 s_fnM6020_RawDataDecode(&P_stMotor_Gimbal_YawH,msg);//原始数据解析
            }break;

			// case MOTOR_GIMBAL_PITCH_CAN_ID:
			// {
			// 	s_fnM6020_RawDataDecode(&P_stMotor_Gimbal_Pitch,msg);//原始数据解析
			// }break;

			default:
			{
			}break;
		}
	}
}

/*******************************************************************************
* Function Name  : void fnM3508_SpeedCotrol( M3508_TypeDef* st_data,float target_speed)
* Description    : CAN1上的3508电机速度控制函数;
* Input          : 3508电机ID，目标速度;
* Output         : 无
* Return         : 无
*******************************************************************************/ 
void fnM3508_SpeedCotrol( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量
	
	fnMotor_SetCurrentVal(CAN1,st_data->CAN_ID,ctrl_val);//控制执行电机
}

/*******************************************************************************
* Function Name  : void fnM6020_Cotrol( M6020_TypeDef* st_data,float target_angle,float feedback_angle,float feedback_speed)
* Description    : CAN1上的6020电机速度控制函数;6020双环控制;
* Input          : st_data：M6020_TypeDef结构体指针，表示要控制的电机的参数和状态;
									 target_angle：  目标角度，表示期望的电机角度;
									 feedback_angle：反馈角度，表示当前的电机角度;
                   feedback_speed：反馈速度，表示当前的电机速度;
* Output         : 无
* Return         : 无
*******************************************************************************/ 
void fnM6020_Cotrol( M6020_TypeDef* st_data,float target_angle,float feedback_angle,float feedback_speed)
{
	float ctrl_val_speed,crtl_val_angle;

	fnPID_SetTarget(&st_data->AnglePID,target_angle);//设置目标
	fnPID_SetFeedback(&st_data->AnglePID,feedback_angle);//获取反馈值;
	fnPID_Calc(&st_data->AnglePID);//PID计算
    crtl_val_angle = fnPID_GetOutput(&st_data->AnglePID);//获取控制量
	
	fnPID_SetTarget(&st_data->SpeedPID,crtl_val_angle);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,feedback_speed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	ctrl_val_speed = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量
	
	fnMotor_SetCurrentVal(CAN1,st_data->CAN_ID,ctrl_val_speed);
}

/*******************************************************************************
* Function Name  : void fnMotor_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i)
* Description    : 主要功能是根据输入的参数设置电机的控制电流值，并通过CAN总线发送相应的数据帧。

* Input          : CANx是一个CAN_TypeDef类型的指针，用于指定选择哪个CAN总线进行通信。该参数可以是CAN1或CAN2;
									 motor_id是一个uint8_t类型的参数，用于指定要设置电流值的电机编号。范围是1到8;
                   cm_i是一个int16_t类型的参数，表示要设置的控制电流值;

* Output         : 无
* Return         : 无
*******************************************************************************/ 
//电机电调设置控制电流值
void fnMotor_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i)
{	
  static CanSend_Type MotorSendData1_4CAN1;
	static CanSend_Type MotorSendData5_8CAN1;
	
	static CanSend_Type MotorSendData1_4CAN2;
	static CanSend_Type MotorSendData5_8CAN2;

	if(CANx==CAN1)
	
	{
		MotorSendData1_4CAN1.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER1_4;
		MotorSendData1_4CAN1.SendCanTxMsg.DLC = 8;
		MotorSendData1_4CAN1.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData1_4CAN1.SendCanTxMsg.RTR = CAN_RTR_Data;
		
		MotorSendData5_8CAN1.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER5_8;
		MotorSendData5_8CAN1.SendCanTxMsg.DLC = 8;
		MotorSendData5_8CAN1.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData5_8CAN1.SendCanTxMsg.RTR = CAN_RTR_Data;
		
		switch(motor_id)
        {
						
            case 1:
            {
                MotorSendData1_4CAN1.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
                MotorSendData1_4CAN1.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
            }break;
            
            case 2:
            {
                MotorSendData1_4CAN1.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
                MotorSendData1_4CAN1.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
            }break;
            
            case 3:
            {
                MotorSendData1_4CAN1.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
                MotorSendData1_4CAN1.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
            }break;
            
            case 4:
            {
                MotorSendData1_4CAN1.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
                MotorSendData1_4CAN1.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
            }break;
            
            case 5:
            {
                MotorSendData5_8CAN1.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
                MotorSendData5_8CAN1.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
            }break;
            
            case 6:
            {
                MotorSendData5_8CAN1.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
                MotorSendData5_8CAN1.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
            }break;
            
            case 7:
            {
                MotorSendData5_8CAN1.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
                MotorSendData5_8CAN1.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
            }break;
            
            case 8:
            {
                MotorSendData5_8CAN1.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
                MotorSendData5_8CAN1.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
            }break;
        }
        
        s_fnMotor_CANSend(CAN1,(CanTxMsg* )&(MotorSendData1_4CAN1.SendCanTxMsg));
        s_fnMotor_CANSend(CAN1,(CanTxMsg* )&(MotorSendData5_8CAN1.SendCanTxMsg));	
        
    }
	
	else if(CANx==CAN2)
	{
		MotorSendData1_4CAN2.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER1_4;
		MotorSendData1_4CAN2.SendCanTxMsg.DLC = 8;
		MotorSendData1_4CAN2.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData1_4CAN2.SendCanTxMsg.RTR = CAN_RTR_Data;
		
		MotorSendData5_8CAN2.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER5_8;
		MotorSendData5_8CAN2.SendCanTxMsg.DLC = 8;
		MotorSendData5_8CAN2.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData5_8CAN2.SendCanTxMsg.RTR = CAN_RTR_Data;
		
		switch(motor_id)
        {
				
            case 1:
            {
                MotorSendData1_4CAN2.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
                MotorSendData1_4CAN2.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
            }break;
            
            case 2:
            {
                MotorSendData1_4CAN2.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
                MotorSendData1_4CAN2.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
            }break;
            
            case 3:
            {
                MotorSendData1_4CAN2.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
                MotorSendData1_4CAN2.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
            }break;
            
            case 4:
            {
                MotorSendData1_4CAN2.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
                MotorSendData1_4CAN2.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
            }break;
            
            case 5:
            {
                MotorSendData5_8CAN2.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
                MotorSendData5_8CAN2.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
            }break;
            
            case 6:
            {
                MotorSendData5_8CAN2.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
                MotorSendData5_8CAN2.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
            }break;
            
            case 7:
            {
                MotorSendData5_8CAN2.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
                MotorSendData5_8CAN2.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
            }break;
            
            case 8:
            {
                MotorSendData5_8CAN2.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
                MotorSendData5_8CAN2.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
            }break;
        }
        
			s_fnMotor_CANSend(CAN2,(CanTxMsg* )&(MotorSendData1_4CAN2.SendCanTxMsg));
      s_fnMotor_CANSend(CAN2,(CanTxMsg* )&(MotorSendData5_8CAN2.SendCanTxMsg));	
	}
}

/*******************************************************************************
* Function Name  : static void s_fnM3508_RawDataDecode(M3508_TypeDef* st_data,CanRxMsg * msg)
* Description    : 3508电机原始数据解析函数;
* Input          : st_data: 指向M3508电机数据结构体的指针;
									 msg: 接收到的CAN消息数据结构体;
* Output         : 无
* Return         : 无
*******************************************************************************/ 
static void s_fnM3508_RawDataDecode(M3508_TypeDef* st_data,CanRxMsg * msg)
{
	uint8_t i;
	int32_t temp_sum = 0;
	
	st_data->RecvData.Encoder_Val = (int16_t)((msg->Data[0]<<8)|(msg->Data[1]));//编码器值
	st_data->RecvData.Rotate_Speed = (int16_t)((msg->Data[2]<<8)|(msg->Data[3]));//电机反馈速度
	st_data->RecvData.Armature_Current = (int16_t)((msg->Data[4]<<8)|(msg->Data[5]));//电机反馈电流
	st_data->RecvData.Motor_Temperature = (int8_t)(msg->Data[6]);//电机温度
	
	//电机速度滤波
	st_data->RecvData.Rotate_SpeedBuf[st_data->RecvData.Rotate_BufCount ++] = st_data->RecvData.Rotate_Speed;
	
	if(st_data->RecvData.Rotate_BufCount == ROTATE_SPEEDBUF_LEN)
	{
		st_data->RecvData.Rotate_BufCount = 0;
	}
	
	for(i = 0;i < ROTATE_SPEEDBUF_LEN; i++)
	{
		temp_sum +=	st_data->RecvData.Rotate_SpeedBuf[i];
	}
	
	st_data->RecvData.Rotate_FliterSpeed = (int32_t)(temp_sum/ROTATE_SPEEDBUF_LEN);
}

/*******************************************************************************
* Function Name  : static void s_fnM6020_RawDataDecode(M6020_TypeDef* st_data,CanRxMsg * msg)
* Description    : 6020电机原始数据解析函数;
* Input          : st_data: 指向M6020电机数据结构体的指针;
									 msg: 接收到的CAN消息数据结构体;
* Output         : 
* Return         : 
*******************************************************************************/ 
static void s_fnM6020_RawDataDecode(M6020_TypeDef* st_data,CanRxMsg * msg)
{
	int16_t diff_val = 0;
	static uint16_t init_time;
	
	st_data->RecvData.Encoder_Val = (int16_t)((msg->Data[0]<<8)|(msg->Data[1]));//编码器值
	st_data->RecvData.Rotate_Speed = (int16_t)((msg->Data[2]<<8)|(msg->Data[3]));//电机反馈速度
	st_data->RecvData.Armature_Current = (int16_t)((msg->Data[4]<<8)|(msg->Data[5]));//电机反馈电流
	st_data->RecvData.Motor_Temperature = (int8_t)(msg->Data[6]);//电机温度
	st_data->RecvData.Raw_Angle = st_data->RecvData.Encoder_Val/8192.f * 360;
	
	if(init_time ++ < 500)//前500次进入这个函数时直接跳到最后一步记录上一次编码器值
	{
		goto step_recode;
	}
	
	diff_val = st_data->RecvData.Encoder_Val - st_data->RecvData.Last_Encoder_Val;//获取前后两次编码器角度差值

	//记录旋转圈数
	if(diff_val < -4000)
	{
		st_data->RecvData.Number_Of_Turns ++;
	}
	else if(diff_val > 4000)
	{
		st_data->RecvData.Number_Of_Turns --;
	}
	//获取连续化处理后的转子角度
	st_data->RecvData.Shaft_Angle = st_data->RecvData.Number_Of_Turns * 360.f + st_data->RecvData.Encoder_Val/8192.f * 360.f;
	
	step_recode:st_data->RecvData.Last_Encoder_Val = st_data->RecvData.Encoder_Val;//获取差值后记录上一次编码器值
}

/*******************************************************************************
* Function Name  : static void s_fnMotor_CANSend(CAN_TypeDef *CANx, CanTxMsg *stMotorSendData)
* Description    : 底层CAN发送函数;
* Input          : CANx: CAN总线的类型（例如CAN1、CAN2等）;
									 stMotorSendData: 要发送的CAN消息数据结构体;
* Output         : 
* Return         : 
*******************************************************************************/ 
static void s_fnMotor_CANSend(CAN_TypeDef *CANx, CanTxMsg *stMotorSendData)
{
	uint16_t i=0;
	u8 nMailBox=0;
	nMailBox=CAN_Transmit(CANx, stMotorSendData);
	while((CAN_TransmitStatus(CANx,nMailBox)==CAN_TxStatus_Failed)&&(i<0XFFF))
	{
		i++;	//等待发送结束
	}
}
