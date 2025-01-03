#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include "stm32f4xx.h"
#include <stdio.h>
#include <math.h>
#include <main.h>


typedef struct Signal_TypeDef
{
	float (*Calc) (struct Signal_TypeDef *Signal);//���㹫ʽ����ָ��
	uint8_t (*isOverFlow) (struct Signal_TypeDef *Signal);//���㹫ʽ����ָ��
	void (*Reset) (struct Signal_TypeDef *Signal);//���㹫ʽ����ָ��
	float input;//��������
	uint32_t scale;//б��
	float output;//���ֵ
}Signal_TypeDef;//�źŽṹ��

void cofigSignal_vyInit(void);
void configSignal_ParaInit(void);
void fnSiganl_Reset(Signal_TypeDef* st_data);
float fnSignal_Ramp_Generate(Signal_TypeDef* st_data);
void fnSignal_SetScale(Signal_TypeDef* st_data,uint32_t scale);
float fnSignal_BackRamp_Generate(Signal_TypeDef* st_data);
uint8_t fnSiganl_IsOverFlow(Signal_TypeDef* st_data);

extern Signal_TypeDef P_stYawReset_Ramp;//Yaw�Ḵλб��
extern Signal_TypeDef P_stPitchReset_Ramp;

extern Signal_TypeDef P_stvy_Ramp;
extern Signal_TypeDef P_stvx_Ramp;
extern Signal_TypeDef P_stvw_Ramp;
extern Signal_TypeDef P_sttranslate_Ramp;
extern Signal_TypeDef P_sttranslate_Re_Ramp;
#endif
