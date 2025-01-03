#ifndef __CHASSIS_BEHAVIOR_H__
#define __CHASSIS_BEHAVIOR_H__
#include "main.h"

#include "motor.h"
#include "pid.h"
#include "arm_math.h"

/*����ֵ*/
#define SIN45 0.707107f
#define COS45 0.707107f
typedef enum
{
	Chassis_BlackOut,//���̶ϵ�
	Chassis_Working//�˶�״̬
}e_Chassis_State;//����״̬

typedef enum
{
    /*----------*/
    Chassis_NoFollow,//���̲�����״̬
    Chassis_AI,//���ڿ���״̬
    Chassis_Navigator,//��������ģʽ
    /*----------*/
    
	Chassis_Follow,//���̸���״̬
	Chassis_Twist,//Ť��״̬
	Chassis_Spin,//С����״̬
	Chassis_Spin_Finish,//С���ݸ�λ״̬
    Chassis_Fix,//����ǰ������̶�״̬

}e_ChassisMotion_State;//�����˶�״̬

typedef struct Chassis_Speed_TypeDef
{
	float vx;//����ƽ���ٶ�
	float vy;//ǰ��ƽ���ٶ�
	float vw;//��ת�ٶ�
	
}Chassis_Speed_TypeDef;//�����ٶȽṹ��


typedef struct {       //�����ٶȽṹ��
	float32_t v;//m/s
	float32_t angle;//degree
}Chassis_WhlVct_Typedef;      //�ٶ������ṹ��

typedef struct Chassis_RstPara_Typedef
{
    float Initial_Yaw;              //��ʼYawֵ
    float Initial_Encoder;           //��������ʼֵ
    float Initial_Gyro;             //�����ǳ�ʼֵ
    float Pos_Diff;             //�ϵ�������ֵ �� �����������ֵ �Ĳ�ֵ
    float Converted_GyroYaw;        //���ϲ�ֵ�������ǵ�ǰ����ʼ����
    
}Chassis_RstPara_Typedef;


typedef struct Chassis_Cali_TypeDef
{
	bool Cali_Finish_Flag;
	
	float Cali_Yaw_180; //��̨YawУ׼ֵ
	float Cali_Yaw_360; //��̨YawУ׼ֵ

}Chassis_Cali_TypeDef;


typedef struct Chassis_TypeDef
{
	//����״̬
	e_Chassis_State State;
	e_ChassisMotion_State Mode;
	 
	bool Spin_Reset_Flag;
    
	//�����ٶȲ���
	Chassis_Speed_TypeDef Para;	
    Chassis_RstPara_Typedef RstPara;    //�������������ò���
    Chassis_Cali_TypeDef Cali;
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
