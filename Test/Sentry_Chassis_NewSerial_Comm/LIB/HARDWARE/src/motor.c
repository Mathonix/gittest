#include "motor.h"

M3508_TypeDef P_stMotor_ChassisF = {1};//������ǰ�ֵ��
M3508_TypeDef P_stMotor_ChassisB = {2};//�����Һ��ֵ��

M6020_TypeDef P_stMotor_SteerF = {7};  //������ǰ����
M6020_TypeDef P_stMotor_SteerB = {8};  //�����Һ����

M6020_TypeDef P_stMotor_Gimbal_YawH ={5};//��̨СYaw����
M6020_TypeDef P_stMotor_Gimbal_YawL ={6};//��̨��Yaw����
M6020_TypeDef P_stMotor_Gimbal_Pitch ={7};//��̨Pitch����

int8_t Reset_yaw;
extern float vx,vy,vw;

/*******************************************************************************
* Function Name  : void configMotor_ParaInit(void)
* Description    : ���̵����YAW�����̬PID����;
* Input          : ��
* Output         : ��
* Return         : ��
*******************************************************************************/ 
//���������ʼ��
void configMotor_ParaInit(void)
{	
//	//���̵������
//	//��
//	fnPID_SetPara_P_I_D(&P_stMotor_ChassisL.SpeedPID,5,0,0);
//	fnPID_SetPara_IM(&P_stMotor_ChassisL.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_ChassisL.SpeedPID,8000);

//	//ǰ
//	fnPID_SetPara_P_I_D(&P_stMotor_ChassisF.SpeedPID,5,0,0);
//	fnPID_SetPara_IM(&P_stMotor_ChassisF.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_ChassisF.SpeedPID,8000);
//	
//	//��
//	fnPID_SetPara_P_I_D(&P_stMotor_ChassisB.SpeedPID,5,0,0);
//	fnPID_SetPara_IM(&P_stMotor_ChassisB.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_ChassisB.SpeedPID,8000);
//	
//	//��
//	fnPID_SetPara_P_I_D(&P_stMotor_ChassisR.SpeedPID,5,0,0);
//	fnPID_SetPara_IM(&P_stMotor_ChassisR.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_ChassisR.SpeedPID,8000);
//	//��̨�������
//	//yaw�����ٶȻ�
//	fnPID_SetPara_P_I_D(&P_stMotor_Gimbal_Yaw.SpeedPID,98,0,0);
//	fnPID_SetPara_IM(&P_stMotor_Gimbal_Yaw.SpeedPID,1000);
//	fnPID_SetPara_OM(&P_stMotor_Gimbal_Yaw.SpeedPID,25000);
//	//�ǶȻ�
//	fnPID_SetPara_P_I_D(&P_stMotor_Gimbal_Yaw.AnglePID,5.87,0,0);
//	fnPID_SetPara_IM(&P_stMotor_Gimbal_Yaw.AnglePID,1000);
//	fnPID_SetPara_OM(&P_stMotor_Gimbal_Yaw.AnglePID,3000);
//	
}

/*******************************************************************************
* Function Name  : void fnMotor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg)
* Description    : Can���ݽ���;
* Input          : ���ID
* Output         : ��
* Return         : ��
*******************************************************************************/ 
void fnMotor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg)
{
	if(canx == CAN1)
	{
		//���ݶ�ӦID,�������ݽ���
			switch(msg->StdId)
			{
			case MOTOR_CHASSIS_F_CAN_ID:
			{
				s_fnM3508_RawDataDecode(&P_stMotor_ChassisF,msg);//ԭʼ���ݽ���
			}break;
			
			case MOTOR_CHASSIS_B_CAN_ID:
			{
				s_fnM3508_RawDataDecode(&P_stMotor_ChassisB,msg);//ԭʼ���ݽ���
			}break;
			
			case MOTOR_STEER_F_CAN_ID:
			{
				s_fnM6020_RawDataDecode(&P_stMotor_SteerF,msg);//ԭʼ���ݽ���
			}break;
			
			case MOTOR_STEER_B_CAN_ID:
			{
				s_fnM6020_RawDataDecode(&P_stMotor_SteerB,msg);//ԭʼ���ݽ���
			}break;
			
			default:
			{
			}break;
		}
	}
	else if(canx == CAN2)
	{
		//���ݶ�ӦID,�������ݽ���
		switch(msg->StdId)
		{

			case MOTOR_GIMBAL_YAWL_CAN_ID:
			{
				s_fnM6020_RawDataDecode(&P_stMotor_Gimbal_YawL,msg);//ԭʼ���ݽ���
			}break;

            case MOTOR_GIMBAL_YAWH_CAN_ID:
            {
                 s_fnM6020_RawDataDecode(&P_stMotor_Gimbal_YawH,msg);//ԭʼ���ݽ���
            }break;

			// case MOTOR_GIMBAL_PITCH_CAN_ID:
			// {
			// 	s_fnM6020_RawDataDecode(&P_stMotor_Gimbal_Pitch,msg);//ԭʼ���ݽ���
			// }break;

			default:
			{
			}break;
		}
	}
}

/*******************************************************************************
* Function Name  : void fnM3508_SpeedCotrol( M3508_TypeDef* st_data,float target_speed)
* Description    : CAN1�ϵ�3508����ٶȿ��ƺ���;
* Input          : 3508���ID��Ŀ���ٶ�;
* Output         : ��
* Return         : ��
*******************************************************************************/ 
void fnM3508_SpeedCotrol( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//����Ŀ��
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//��ȡ����ֵ;
	fnPID_Calc(&st_data->SpeedPID);//PID����
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//��ȡ������
	
	fnMotor_SetCurrentVal(CAN1,st_data->CAN_ID,ctrl_val);//����ִ�е��
}

/*******************************************************************************
* Function Name  : void fnM6020_Cotrol( M6020_TypeDef* st_data,float target_angle,float feedback_angle,float feedback_speed)
* Description    : CAN1�ϵ�6020����ٶȿ��ƺ���;6020˫������;
* Input          : st_data��M6020_TypeDef�ṹ��ָ�룬��ʾҪ���Ƶĵ���Ĳ�����״̬;
									 target_angle��  Ŀ��Ƕȣ���ʾ�����ĵ���Ƕ�;
									 feedback_angle�������Ƕȣ���ʾ��ǰ�ĵ���Ƕ�;
                   feedback_speed�������ٶȣ���ʾ��ǰ�ĵ���ٶ�;
* Output         : ��
* Return         : ��
*******************************************************************************/ 
void fnM6020_Cotrol( M6020_TypeDef* st_data,float target_angle,float feedback_angle,float feedback_speed)
{
	float ctrl_val_speed,crtl_val_angle;

	fnPID_SetTarget(&st_data->AnglePID,target_angle);//����Ŀ��
	fnPID_SetFeedback(&st_data->AnglePID,feedback_angle);//��ȡ����ֵ;
	fnPID_Calc(&st_data->AnglePID);//PID����
    crtl_val_angle = fnPID_GetOutput(&st_data->AnglePID);//��ȡ������
	
	fnPID_SetTarget(&st_data->SpeedPID,crtl_val_angle);//����Ŀ��
	fnPID_SetFeedback(&st_data->SpeedPID,feedback_speed);//��ȡ����ֵ;
	fnPID_Calc(&st_data->SpeedPID);//PID����
	ctrl_val_speed = fnPID_GetOutput(&st_data->SpeedPID);//��ȡ������
	
	fnMotor_SetCurrentVal(CAN1,st_data->CAN_ID,ctrl_val_speed);
}

/*******************************************************************************
* Function Name  : void fnMotor_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i)
* Description    : ��Ҫ�����Ǹ�������Ĳ������õ���Ŀ��Ƶ���ֵ����ͨ��CAN���߷�����Ӧ������֡��

* Input          : CANx��һ��CAN_TypeDef���͵�ָ�룬����ָ��ѡ���ĸ�CAN���߽���ͨ�š��ò���������CAN1��CAN2;
									 motor_id��һ��uint8_t���͵Ĳ���������ָ��Ҫ���õ���ֵ�ĵ����š���Χ��1��8;
                   cm_i��һ��int16_t���͵Ĳ�������ʾҪ���õĿ��Ƶ���ֵ;

* Output         : ��
* Return         : ��
*******************************************************************************/ 
//���������ÿ��Ƶ���ֵ
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
* Description    : 3508���ԭʼ���ݽ�������;
* Input          : st_data: ָ��M3508������ݽṹ���ָ��;
									 msg: ���յ���CAN��Ϣ���ݽṹ��;
* Output         : ��
* Return         : ��
*******************************************************************************/ 
static void s_fnM3508_RawDataDecode(M3508_TypeDef* st_data,CanRxMsg * msg)
{
	uint8_t i;
	int32_t temp_sum = 0;
	
	st_data->RecvData.Encoder_Val = (int16_t)((msg->Data[0]<<8)|(msg->Data[1]));//������ֵ
	st_data->RecvData.Rotate_Speed = (int16_t)((msg->Data[2]<<8)|(msg->Data[3]));//��������ٶ�
	st_data->RecvData.Armature_Current = (int16_t)((msg->Data[4]<<8)|(msg->Data[5]));//�����������
	st_data->RecvData.Motor_Temperature = (int8_t)(msg->Data[6]);//����¶�
	
	//����ٶ��˲�
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
* Description    : 6020���ԭʼ���ݽ�������;
* Input          : st_data: ָ��M6020������ݽṹ���ָ��;
									 msg: ���յ���CAN��Ϣ���ݽṹ��;
* Output         : 
* Return         : 
*******************************************************************************/ 
static void s_fnM6020_RawDataDecode(M6020_TypeDef* st_data,CanRxMsg * msg)
{
	int16_t diff_val = 0;
	static uint16_t init_time;
	
	st_data->RecvData.Encoder_Val = (int16_t)((msg->Data[0]<<8)|(msg->Data[1]));//������ֵ
	st_data->RecvData.Rotate_Speed = (int16_t)((msg->Data[2]<<8)|(msg->Data[3]));//��������ٶ�
	st_data->RecvData.Armature_Current = (int16_t)((msg->Data[4]<<8)|(msg->Data[5]));//�����������
	st_data->RecvData.Motor_Temperature = (int8_t)(msg->Data[6]);//����¶�
	st_data->RecvData.Raw_Angle = st_data->RecvData.Encoder_Val/8192.f * 360;
	
	if(init_time ++ < 500)//ǰ500�ν����������ʱֱ���������һ����¼��һ�α�����ֵ
	{
		goto step_recode;
	}
	
	diff_val = st_data->RecvData.Encoder_Val - st_data->RecvData.Last_Encoder_Val;//��ȡǰ�����α������ǶȲ�ֵ

	//��¼��תȦ��
	if(diff_val < -4000)
	{
		st_data->RecvData.Number_Of_Turns ++;
	}
	else if(diff_val > 4000)
	{
		st_data->RecvData.Number_Of_Turns --;
	}
	//��ȡ������������ת�ӽǶ�
	st_data->RecvData.Shaft_Angle = st_data->RecvData.Number_Of_Turns * 360.f + st_data->RecvData.Encoder_Val/8192.f * 360.f;
	
	step_recode:st_data->RecvData.Last_Encoder_Val = st_data->RecvData.Encoder_Val;//��ȡ��ֵ���¼��һ�α�����ֵ
}

/*******************************************************************************
* Function Name  : static void s_fnMotor_CANSend(CAN_TypeDef *CANx, CanTxMsg *stMotorSendData)
* Description    : �ײ�CAN���ͺ���;
* Input          : CANx: CAN���ߵ����ͣ�����CAN1��CAN2�ȣ�;
									 stMotorSendData: Ҫ���͵�CAN��Ϣ���ݽṹ��;
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
		i++;	//�ȴ����ͽ���
	}
}
