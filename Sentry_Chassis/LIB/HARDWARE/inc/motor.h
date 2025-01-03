#ifndef __MOTOR_H__
#define __MOTOR_H__
#include <stdio.h>
#include "stdbool.h"
#include "stm32f4xx.h"
#include "pid.h"
#include "rm_remote.h"

#define MOTOR_3508_REDUCTIONRATE 19.f //3508������ٱ�Ϊ19��1
#define MOTOR_C620_REDUCTIONRATE 19.f //3508������ٱ�Ϊ19��1

#define MOTOR_CANSEND_IDENTIFIER1_4 0x200 // ���ID 1~4ʹ�ô˱�ʶ��
#define MOTOR_CANSEND_IDENTIFIER5_8 0x1ff // ���ID 5~8ʹ�ô˱�ʶ��

#define MOTOR_CHASSIS_F_CAN_ID 0x201 //������ǰ�ֵ��CAN��ID
#define MOTOR_CHASSIS_B_CAN_ID 0x202 //�����Һ��ֵ��CAN��ID

#define MOTOR_RUDDER_F_CAN_ID 0x205  //������ǰ�����ֵ��CAN��ID
#define MOTOR_RUDDER_B_CAN_ID 0x206  //�����Һ�����ֵ��CAN��ID

#define MOTOR_GIMBAL_YAWL_CAN_ID 0x205 //��̨��Yaw����CAN��ID
#define MOTOR_GIMBAL_YAWH_CAN_ID 0x206 //��̨СYaw����CAN��ID
#define MOTOR_GIMBAL_PITCH_CAN_ID 0x207 //��̨Pitch����CAN��ID

#define ROTATE_SPEEDBUF_LEN  6 //�ٶ��˲����黺�泤��

typedef struct 
{
  uint8_t     CANx;               //CAN���     1 CAN1      2 CAN2
  CanTxMsg    SendCanTxMsg;       //��������
}CanSend_Type;



//3508���ԭʼ���ݴ���ṹ��
typedef struct M3508_Data_TypeDef
{
	//ԭʼ����
	int16_t Encoder_Val;//������ֵ
	int16_t Rotate_Speed;//ת���ٶ�
	int16_t Armature_Current;//�������
	int8_t Motor_Temperature; //����¶�
	
	//�ٶ��˲�
	int16_t Rotate_FliterSpeed;//�˲�����ٶ�
	int16_t Rotate_SpeedBuf[ROTATE_SPEEDBUF_LEN];
	int16_t Rotate_BufCount;//�������ݼ���

}M3508_DataRecv_TypeDef;

//3508������ݽṹ��
typedef struct M3508_TypeDef
{
	int8_t CAN_ID;//CAN ID��
	uint8_t Reduction_Rate;//������ٱ�
	M3508_DataRecv_TypeDef RecvData;//������ݴ���
	PID_InitTypeDef SpeedPID;//�ٶȻ�PID��������
}M3508_TypeDef;

//6020���ԭʼ���ݴ���ṹ��
typedef struct M6020_Data_TypeDef
{
	//ԭʼ����
	int16_t Encoder_Val;//������ֵ
	int16_t Rotate_Speed;//ת���ٶ�
	int16_t Armature_Current;//�������
	int8_t Motor_Temperature; //����¶�
	
	int16_t Last_Encoder_Val;//��һ�α�����ֵ
	int32_t Number_Of_Turns;//�����תȦ��
    float Custom_Angle_Zero;    //����Զ���Ƕ�Ԥ�����ֵ����λΪ�ȣ���Raw_Angle����

	float Raw_Angle;//���ת�� 0-360��
	float Shaft_Angle;//���ת���ĽǶ�
	float Custom_Angle;//����Զ���Ƕ�
	//�ٶ��˲�
	int16_t Rotate_FliterSpeed;//�˲�����ٶ�
	int16_t Rotate_SpeedBuf[ROTATE_SPEEDBUF_LEN];
	int16_t Rotate_BufCount;//�������ݼ���

}M6020_DataRecv_TypeDef;

//6020���ݽṹ��
typedef struct M6020_TypeDef
{
	int8_t CAN_ID;//CAN ID��
	M6020_DataRecv_TypeDef RecvData;//������ݴ���

	PID_InitTypeDef SpeedPID;//�ٶȻ�PID��������
	PID_InitTypeDef AnglePID;//�ǶȻ�PID��������
}M6020_TypeDef;



extern M3508_TypeDef P_stMotor_ChassisF;//������ǰ���
extern M3508_TypeDef P_stMotor_ChassisB;//���������
extern M6020_TypeDef P_stMotor_RudderF;  //������ǰ����
extern M6020_TypeDef P_stMotor_RudderB;  //�����Һ����

extern M6020_TypeDef P_stMotor_Gimbal_Yaw;//��̨Yaw����

void configMotor_ParaInit(void);

void fnMotor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg);
void fnMotor_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i);

void fnM3508_SpeedCotrol( M3508_TypeDef* st_data,float target_speed);

void fnM6020_Cotrol( M6020_TypeDef* st_data,float target_angle,float feedback_angle,float feedback_speed);

static void s_fnMotor_CANSend(CAN_TypeDef *CANx, CanTxMsg *stMotorSendData);
static void s_fnM3508_RawDataDecode(M3508_TypeDef* st_data,CanRxMsg * msg);
static void s_fnM6020_RawDataDecode(M6020_TypeDef* st_data,CanRxMsg * msg);

#endif
