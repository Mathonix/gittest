#ifndef __VOFA_H__
#define __VOFA_H__
#include "main.h"

#define VOFA_MAX_CHANNELS 3     //VOFA通道数
#define VOFA_SEND_SIZE (VOFA_MAX_CHANNELS * 4 + 4)//VOFA发送缓冲区

//VOFA配置部分
#define VOFA_DMAx_STREAMx DMA1_Stream6
#define VOFA_DMA_IT_TCIFx DMA_IT_TCIF6
#define VOFA_DMAx_Streamx_IRQHandler DMA1_Stream6_IRQHandler
#define VOFA_


void VOFA_Send(void);
void configVOFA_ParaInit(void);

extern float VOFA_Origin_Data[VOFA_MAX_CHANNELS];
extern uint8_t VOFA_Send_Data[VOFA_SEND_SIZE];

#endif

