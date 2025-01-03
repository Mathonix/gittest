#ifndef __PID_H__
#define __PID_H__

#include "stm32f4xx.h"
//变积分PID属性表
typedef struct PID_Scope_TypeDef
{
	float cmd,//是否使用标志位
				min,//最小范围
				max,//最大范围
				Error,//误差
				Scope_Max,//动态最大值
				Scope;//动态值
}PID_Scope_TypeDef;

//PID属性列表
typedef struct PID_TypeDef
{
    float Kp;	//比例系数
    float Ki;	//积分系数
    float Kd;	//微分系数
    float Target;	//当前误差
    float IntPartMax;	//最大积分限制
    float OutputMax;	//PID输出
    float CurrentValue;	//当前值
    float CurrentError;	//当前误差
		float LastCurrentValue;
    float LastLastError;	 //上一次误差
    float ProPart;	//比例项
    float DiffPart;	//微分项
    float IntPart;	//积分项
    float Output;	//PID输出
		PID_Scope_TypeDef Scope_Kp;//范围比例系数
	  PID_Scope_TypeDef Scope_Ki;//范围积分系数
}PID_InitTypeDef;

void fnPID_SetPara_P_I_D(PID_InitTypeDef *pid,float kp,float ki,float kd);
void fnPID_SetPara_OM(PID_InitTypeDef *pid,float outputmax);
void fnPID_SetPara_IM(PID_InitTypeDef *pid,float intpartmax);
float fnPID_Calc(PID_InitTypeDef *pid);
void fnPID_SetTarget(PID_InitTypeDef *pid,float target);
void fnPID_SetFeedback(PID_InitTypeDef *pid,float feedback);
float fnPID_GetOutput(PID_InitTypeDef *pid);
/*****************************变积分pid设置**********************************/
void Set_Fabs_Scope_PI(PID_Scope_TypeDef *PID_Scope,float min,float max,float Error,float Scope_Max);
void Clear_Fabs_Scope_PI(PID_Scope_TypeDef *PID_Scope);//清除使能标准位
/***********************变积分pid计算***************************/
void Calc_Scope_PI(PID_Scope_TypeDef *PID_Scope);
/***********************增量式pid设置*********************************/
float fnPID_Add_Calc(PID_InitTypeDef *pid);
#endif
