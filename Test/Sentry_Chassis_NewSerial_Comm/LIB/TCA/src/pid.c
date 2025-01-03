/**
****************************(C) COPYRIGHT 2019 Wei Chen****************************
* @file       pid.c/h
* @brief      pid算法库，实现pid运算
* @note       
* @history
*  Version    Date                 Author                                Modification
*  V1.0.0     Sept-8-2019     Wei Chen                             1. 未完成
@verbatim
==============================================================================

==============================================================================
@endverbatim
****************************(C) COPYRIGHT 2019 Wei Chen****************************
*/

#include "pid.h"

#define PID_OUTPUT_LIMIT_ALLOW 1 //输出限幅开启
#define PID_INTPART_LIMIT_ALLOW 1//积分限幅开启
//宏定义，用于将值val限制在最大值max与最小值min之间
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
*  函数名称：fnPID_SetPara_P_I_D
*  功能说明：设置Kp,Ki,Kd
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetPara_P_I_D(PID_InitTypeDef *pid,float kp,float ki,float kd)
{
	pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;
}

/*************************************************************************
*  函数名称：fnPID_SetPara_OM
*  功能说明：设置输出限幅
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetPara_OM(PID_InitTypeDef *pid,float outputmax)
{
	pid->OutputMax = outputmax ;
}

/*************************************************************************
*  函数名称：fnPID_SetPara_IM
*  功能说明：设置积分限幅
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetPara_IM(PID_InitTypeDef *pid,float intpartmax)
{
	pid->IntPartMax = intpartmax;
}
/*************************************************************************
*  函数名称：fnPID_Calc
*  功能说明：进行PID计算
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
float fnPID_Calc(PID_InitTypeDef *pid)
{
	float Kp,Ki;
	//误差
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
	
	//比例项
	pid->ProPart = Kp * pid->CurrentError;
	//微分项
	pid->DiffPart = pid->Kd * (pid->CurrentValue - pid->LastCurrentValue);
	//积分项
	pid->IntPart += Ki * pid->CurrentError;
	//积分限幅
	#if PID_INTPART_LIMIT_ALLOW
	limit(pid->IntPart,-pid->IntPartMax,pid->IntPartMax);
	#endif
	//计算输出
	pid->Output = pid->ProPart + pid->IntPart + pid->DiffPart;
	pid->LastCurrentValue = pid->CurrentValue;
	//输出限幅
	#if PID_OUTPUT_LIMIT_ALLOW
	limit(pid->Output,-pid->OutputMax,pid->OutputMax);
	#endif
	
	return pid->Output;
}


/*************************************************************************
*  函数名称：fnPID_Add_Calc
*  功能说明：进行PID_Add计算
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
float fnPID_Add_Calc(PID_InitTypeDef *pid)
{
	float Kp,Ki;
	//误差
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

	//比例项
	pid->ProPart = Kp * (pid->CurrentError-pid->LastCurrentValue);
	//微分项
	pid->DiffPart = pid->Kd * (pid->CurrentValue - 2*pid->LastCurrentValue + pid->LastLastError);
	//积分项
	pid->IntPart = Ki * pid->CurrentError;
	//积分限幅
	#if PID_INTPART_LIMIT_ALLOW
	limit(pid->IntPart,-pid->IntPartMax,pid->IntPartMax);
	#endif
	//计算输出
	pid->Output += pid->ProPart + pid->IntPart + pid->DiffPart;
	pid->LastLastError=pid->LastCurrentValue;
	pid->LastCurrentValue = pid->CurrentValue;
	//输出限幅
	#if PID_OUTPUT_LIMIT_ALLOW
	limit(pid->Output,-pid->OutputMax,pid->OutputMax);
	#endif
	
	return pid->Output;
}

/*************************************************************************
*  函数名称：fnPID_SetTarget
*  功能说明：设置PID目标值
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetTarget(PID_InitTypeDef *pid,float target)
{
	pid->Target = target;
}

/*************************************************************************
*  函数名称：fnPID_SetFeedback
*  功能说明：获取PID反馈值
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetFeedback(PID_InitTypeDef *pid,float feedback)
{
	pid->CurrentValue = feedback;
}

/*************************************************************************
*  函数名称：fnPID_GetOutput
*  功能说明：获取PID输出
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
float fnPID_GetOutput(PID_InitTypeDef *pid)
{
	return pid->Output;
}
/*****************************范围pid设置**********************************/
void Set_Fabs_Scope_PI(PID_Scope_TypeDef *PID_Scope,float min,float max,float Error,float Scope_Max)
{
	PID_Scope->max=max;
	PID_Scope->min=min;
	PID_Scope->Error=Error;
	PID_Scope->Scope_Max=Scope_Max;
	PID_Scope->cmd=1;//使能标准位
}	
void Clear_Fabs_Scope_PI(PID_Scope_TypeDef *PID_Scope)//清除使能标准位
{
	PID_Scope->cmd=0;
}

/*****************************范围pid计算**********************************/
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
