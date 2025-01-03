#ifndef __CHASSIS_BEHAVIOR_H__
#define __CHASSIS_BEHAVIOR_H__
#include "main.h"
#include "motor.h"
#include "pid.h"
typedef enum
{
	Chassis_BlackOut,//���̶ϵ�
	Chassis_Working//�˶�״̬
}e_Chassis_State;//����״̬

typedef enum
{
	Chassis_Follow,//���̸���״̬
    Chassis_NoFollow,//���̲�����״̬
	Chassis_Twist,//Ť��״̬(����RM�޻���ʱ������С���ݵ�ģʽ)
	Chassis_Spin,//С����״̬
	Chassis_Spin_Finish,//С���ݸ�λ״̬
    Chassis_Fix,//����ǰ������̶�״̬
	Chassis_AI,//���ڿ���״̬
}e_ChassisMotion_State;//�����˶�״̬

typedef struct Chassis_Speed_TypeDef
{
	float vx;//����ƽ���ٶ�
	float vy;//ǰ��ƽ���ٶ�
	float vw;//��ת�ٶ�
	
}Chassis_Speed_TypeDef;//�����ٶȽṹ��

typedef struct Chassis_Direction_TypeDef
{
    float Encoder_Direction;//��ʼ����������
    float Gyro_Direction;//��ʼ�����Ƿ���
	
}Chassis_Direction_TypeDef;//�����ٶȽṹ��

typedef enum
{
	Chassis_Spin_speed_high,//С����״̬
	Chassis_Spin_speed_low,
}e_Chassis_Spin_State;//�����˶�״̬

typedef struct {
	float32_t v;//m/s
	float32_t yaw;//rad
}Chassis_Vector_Typedef;      //�ٶ������ṹ��

       //�����ٶȽṹ��

typedef struct Chassis_TypeDef
{
	//����״̬
	e_Chassis_State State;
	e_ChassisMotion_State Mode;
  e_Chassis_Spin_State Spin_State;
	 
	bool Spin_Reset_Flag;
	//�����ٶȲ���
    Chassis_Direction_TypeDef Init_Direction; //��ʼ����
	Chassis_Speed_TypeDef Para;	
	PID_InitTypeDef Follow_PID;
	PID_InitTypeDef Twist_PID;
  PID_InitTypeDef Spin_Finish_PID;
	PID_InitTypeDef AI_PID;
}Chassis_TypeDef;//���̽ṹ��

/******************��������*********************/
void Task_ChassisCtrl(void);
void Chassis_Control(float vx,float vy,float vw);
void configChassis_ParaInit(void);
static void Chassis_SetMode(Chassis_TypeDef *st_data,e_ChassisMotion_State mode);
#endif
