//信号生成器
#include "signal.h"

Signal_TypeDef P_stvy_Ramp = {&fnSignal_BackRamp_Generate,&fnSiganl_IsOverFlow,&fnSiganl_Reset};
Signal_TypeDef P_stvx_Ramp = {&fnSignal_BackRamp_Generate,&fnSiganl_IsOverFlow,&fnSiganl_Reset};
Signal_TypeDef P_stvw_Ramp = {&fnSignal_BackRamp_Generate,&fnSiganl_IsOverFlow,&fnSiganl_Reset};
Signal_TypeDef P_sttranslate_Ramp = {&fnSignal_BackRamp_Generate,&fnSiganl_IsOverFlow,&fnSiganl_Reset};
Signal_TypeDef P_sttranslate_Re_Ramp = {&fnSignal_BackRamp_Generate,&fnSiganl_IsOverFlow,&fnSiganl_Reset};

Signal_TypeDef P_stYawReset_Ramp = {&fnSignal_BackRamp_Generate};//Yaw轴复位斜坡
Signal_TypeDef P_stPitchReset_Ramp = {&fnSignal_BackRamp_Generate};//Pitch轴复位斜坡
void configSignal_ParaInit(void)
{

	fnSignal_SetScale(&P_stvy_Ramp,400);
	fnSignal_SetScale(&P_stvx_Ramp,400);
	fnSignal_SetScale(&P_stvw_Ramp,400);
	fnSignal_SetScale(&P_sttranslate_Ramp,300);
	fnSignal_SetScale(&P_sttranslate_Re_Ramp,800);
	
	fnSignal_SetScale(&P_stYawReset_Ramp,400);
	fnSignal_SetScale(&P_stPitchReset_Ramp,400);
	
	fnSiganl_Reset(&P_stYawReset_Ramp);
	fnSiganl_Reset(&P_stPitchReset_Ramp);
}

//void cofigSignal_vyInit(void)
//{
//	fnSiganl_Reset(&P_stvy_Ramp);
//}

//void cofigSignal_vxInit(void)
//{
//	fnSiganl_Reset(&P_stvx_Ramp);
//}

uint8_t fnSiganl_IsOverFlow(Signal_TypeDef* st_data)
{
	if(st_data->output >= 1)
	{
		return 1;
	}
	
	return 0;
}


void fnSignal_SetScale(Signal_TypeDef* st_data,uint32_t scale)
{
	st_data->scale = scale;
}

void fnSiganl_Reset(Signal_TypeDef* st_data)
{
	st_data->input = 0;
	st_data->output = 0;
}

//斜坡信号生成
float fnSignal_Ramp_Generate(Signal_TypeDef* st_data)
{
	st_data->input += 1/(float)st_data->scale;//自变量累加
	
	st_data->output = st_data->input;

	if(st_data->output >= 1)
	{
		st_data->output = 1;
	}
	
	return st_data->output;
}

//逆向斜坡生产 从1到0
float fnSignal_BackRamp_Generate(Signal_TypeDef* st_data)
{
	st_data->input += 1/(float)st_data->scale;
	
	st_data->output = 1 - st_data->input;
	
	if(st_data->output <= 0)
	{
		st_data->output = 0;
	}
	
	return st_data->output;
}

