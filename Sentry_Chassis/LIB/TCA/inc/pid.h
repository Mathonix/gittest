#ifndef __PID_H__
#define __PID_H__

#include "stm32f4xx.h"
//�����PID���Ա�
typedef struct PID_Scope_TypeDef
{
	float cmd,//�Ƿ�ʹ�ñ�־λ
				min,//��С��Χ
				max,//���Χ
				Error,//���
				Scope_Max,//��̬���ֵ
				Scope;//��ֵ̬
}PID_Scope_TypeDef;

//PID�����б�
typedef struct PID_TypeDef
{
    float Kp;	//����ϵ��
    float Ki;	//����ϵ��
    float Kd;	//΢��ϵ��
    float Target;	//��ǰ���
    float IntPartMax;	//����������
    float OutputMax;	//PID���
    float CurrentValue;	//��ǰֵ
    float CurrentError;	//��ǰ���
		float LastCurrentValue;
    float LastLastError;	 //��һ�����
    float ProPart;	//������
    float DiffPart;	//΢����
    float IntPart;	//������
    float Output;	//PID���
		PID_Scope_TypeDef Scope_Kp;//��Χ����ϵ��
	  PID_Scope_TypeDef Scope_Ki;//��Χ����ϵ��
}PID_InitTypeDef;

void fnPID_SetPara_P_I_D(PID_InitTypeDef *pid,float kp,float ki,float kd);
void fnPID_SetPara_OM(PID_InitTypeDef *pid,float outputmax);
void fnPID_SetPara_IM(PID_InitTypeDef *pid,float intpartmax);
float fnPID_Calc(PID_InitTypeDef *pid);
void fnPID_SetTarget(PID_InitTypeDef *pid,float target);
void fnPID_SetFeedback(PID_InitTypeDef *pid,float feedback);
float fnPID_GetOutput(PID_InitTypeDef *pid);
/*****************************�����pid����**********************************/
void Set_Fabs_Scope_PI(PID_Scope_TypeDef *PID_Scope,float min,float max,float Error,float Scope_Max);
void Clear_Fabs_Scope_PI(PID_Scope_TypeDef *PID_Scope);//���ʹ�ܱ�׼λ
/***********************�����pid����***************************/
void Calc_Scope_PI(PID_Scope_TypeDef *PID_Scope);
/***********************����ʽpid����*********************************/
float fnPID_Add_Calc(PID_InitTypeDef *pid);
#endif
