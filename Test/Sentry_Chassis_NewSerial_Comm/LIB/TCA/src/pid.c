/**
****************************(C) COPYRIGHT 2019 Wei Chen****************************
* @file       pid.c/h
* @brief      pid�㷨�⣬ʵ��pid����
* @note       
* @history
*  Version    Date                 Author                                Modification
*  V1.0.0     Sept-8-2019     Wei Chen                             1. δ���
@verbatim
==============================================================================

==============================================================================
@endverbatim
****************************(C) COPYRIGHT 2019 Wei Chen****************************
*/

#include "pid.h"

#define PID_OUTPUT_LIMIT_ALLOW 1 //����޷�����
#define PID_INTPART_LIMIT_ALLOW 1//�����޷�����
//�궨�壬���ڽ�ֵval���������ֵmax����Сֵmin֮��
#define limit(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\

/*************************************************************************
*  �������ƣ�fnPID_SetPara_P_I_D
*  ����˵��������Kp,Ki,Kd
*  ����˵������ 
*  �������أ���	 
*  ��    ע����
*************************************************************************/
void fnPID_SetPara_P_I_D(PID_InitTypeDef *pid,float kp,float ki,float kd)
{
	pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;
}

/*************************************************************************
*  �������ƣ�fnPID_SetPara_OM
*  ����˵������������޷�
*  ����˵������ 
*  �������أ���	 
*  ��    ע����
*************************************************************************/
void fnPID_SetPara_OM(PID_InitTypeDef *pid,float outputmax)
{
	pid->OutputMax = outputmax ;
}

/*************************************************************************
*  �������ƣ�fnPID_SetPara_IM
*  ����˵�������û����޷�
*  ����˵������ 
*  �������أ���	 
*  ��    ע����
*************************************************************************/
void fnPID_SetPara_IM(PID_InitTypeDef *pid,float intpartmax)
{
	pid->IntPartMax = intpartmax;
}
/*************************************************************************
*  �������ƣ�fnPID_Calc
*  ����˵��������PID����
*  ����˵������ 
*  �������أ���	 
*  ��    ע����
*************************************************************************/
float fnPID_Calc(PID_InitTypeDef *pid)
{
	float Kp,Ki;
	//���
	pid->CurrentError = pid->Target - pid->CurrentValue;
	
	if(pid->Scope_Kp.cmd==0)
	{
		Kp=pid->Kp;
	}
	else if(pid->Scope_Kp.cmd==1)
	{
		Calc_Scope_PI(&pid->Scope_Kp);
		Kp=pid->Kp+pid->Scope_Kp.Scope;
	}
	if(pid->Scope_Ki.cmd==0)
	{
		Ki=pid->Ki;
	}
	else if(pid->Scope_Ki.cmd==1)
	{
		Calc_Scope_PI(&pid->Scope_Ki);
		Ki=pid->Ki+pid->Scope_Ki.Scope;
	}
	
	//������
	pid->ProPart = Kp * pid->CurrentError;
	//΢����
	pid->DiffPart = pid->Kd * (pid->CurrentValue - pid->LastCurrentValue);
	//������
	pid->IntPart += Ki * pid->CurrentError;
	//�����޷�
	#if PID_INTPART_LIMIT_ALLOW
	limit(pid->IntPart,-pid->IntPartMax,pid->IntPartMax);
	#endif
	//�������
	pid->Output = pid->ProPart + pid->IntPart + pid->DiffPart;
	pid->LastCurrentValue = pid->CurrentValue;
	//����޷�
	#if PID_OUTPUT_LIMIT_ALLOW
	limit(pid->Output,-pid->OutputMax,pid->OutputMax);
	#endif
	
	return pid->Output;
}


/*************************************************************************
*  �������ƣ�fnPID_Add_Calc
*  ����˵��������PID_Add����
*  ����˵������ 
*  �������أ���	 
*  ��    ע����
*************************************************************************/
float fnPID_Add_Calc(PID_InitTypeDef *pid)
{
	float Kp,Ki;
	//���
	pid->CurrentError = pid->Target - pid->CurrentValue;
	
	if(pid->Scope_Kp.cmd==0)
	{
		Kp=pid->Kp;
	}
	else if(pid->Scope_Kp.cmd==1)
	{
		Calc_Scope_PI(&pid->Scope_Kp);
		Kp=pid->Kp+pid->Scope_Kp.Scope;
	}
	if(pid->Scope_Ki.cmd==0)
	{
		Ki=pid->Ki;
	}
	else if(pid->Scope_Ki.cmd==1)
	{
		Calc_Scope_PI(&pid->Scope_Ki);
		Ki=pid->Ki+pid->Scope_Ki.Scope;
	}

	//������
	pid->ProPart = Kp * (pid->CurrentError-pid->LastCurrentValue);
	//΢����
	pid->DiffPart = pid->Kd * (pid->CurrentValue - 2*pid->LastCurrentValue + pid->LastLastError);
	//������
	pid->IntPart = Ki * pid->CurrentError;
	//�����޷�
	#if PID_INTPART_LIMIT_ALLOW
	limit(pid->IntPart,-pid->IntPartMax,pid->IntPartMax);
	#endif
	//�������
	pid->Output += pid->ProPart + pid->IntPart + pid->DiffPart;
	pid->LastLastError=pid->LastCurrentValue;
	pid->LastCurrentValue = pid->CurrentValue;
	//����޷�
	#if PID_OUTPUT_LIMIT_ALLOW
	limit(pid->Output,-pid->OutputMax,pid->OutputMax);
	#endif
	
	return pid->Output;
}

/*************************************************************************
*  �������ƣ�fnPID_SetTarget
*  ����˵��������PIDĿ��ֵ
*  ����˵������ 
*  �������أ���	 
*  ��    ע����
*************************************************************************/
void fnPID_SetTarget(PID_InitTypeDef *pid,float target)
{
	pid->Target = target;
}

/*************************************************************************
*  �������ƣ�fnPID_SetFeedback
*  ����˵������ȡPID����ֵ
*  ����˵������ 
*  �������أ���	 
*  ��    ע����
*************************************************************************/
void fnPID_SetFeedback(PID_InitTypeDef *pid,float feedback)
{
	pid->CurrentValue = feedback;
}

/*************************************************************************
*  �������ƣ�fnPID_GetOutput
*  ����˵������ȡPID���
*  ����˵������ 
*  �������أ���	 
*  ��    ע����
*************************************************************************/
float fnPID_GetOutput(PID_InitTypeDef *pid)
{
	return pid->Output;
}
/*****************************��Χpid����**********************************/
void Set_Fabs_Scope_PI(PID_Scope_TypeDef *PID_Scope,float min,float max,float Error,float Scope_Max)
{
	PID_Scope->max=max;
	PID_Scope->min=min;
	PID_Scope->Error=Error;
	PID_Scope->Scope_Max=Scope_Max;
	PID_Scope->cmd=1;//ʹ�ܱ�׼λ
}	
void Clear_Fabs_Scope_PI(PID_Scope_TypeDef *PID_Scope)//���ʹ�ܱ�׼λ
{
	PID_Scope->cmd=0;
}

/*****************************��Χpid����**********************************/
void Calc_Scope_PI(PID_Scope_TypeDef *PID_Scope)
{
	float Error,Scope;
	if(PID_Scope->Error<0)
	{
		Error=-PID_Scope->Error;
	}
	else if (PID_Scope->Error>0)
	{
		Error=PID_Scope->Error;
	}
	if(Error>PID_Scope->max)
	{
		Scope=0;
	}
	else if ((Error>PID_Scope->min)&&(Error<PID_Scope->max))
	{
		Scope=((Error-PID_Scope->min)/(PID_Scope->max-PID_Scope->min));
	}
	else if(Error<PID_Scope->min)
	{
		Scope=1;
	}
	PID_Scope->Scope=Scope*PID_Scope->Scope_Max;
}
