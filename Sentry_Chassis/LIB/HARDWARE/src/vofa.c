#include "vofa.h"

float VOFA_Origin_Data[VOFA_MAX_CHANNELS];      //VOFAԭ����Ƶ����
uint8_t VOFA_Send_Data[VOFA_SEND_SIZE];         //VOFA������������

float test = 0;
/*--------------�ⲿ����---------------*/



/*--------------�ⲿ����---------------*/

void configVOFA_ParaInit(void)
{
    //д��justfloat��β֡����
    VOFA_Send_Data[VOFA_MAX_CHANNELS*4] = 0x00;                    
	VOFA_Send_Data[VOFA_MAX_CHANNELS*4+1] = 0x00;
	VOFA_Send_Data[VOFA_MAX_CHANNELS*4+2] = 0x80;
	VOFA_Send_Data[VOFA_MAX_CHANNELS*4+3] = 0x7f;
}

void VOFA_Send(void)
{
    //д�봫������
    VOFA_Origin_Data[0] = (float)(test);
//    VOFA_Origin_Data[1] = (float)(P_stMotor_Gimbal_Yaw.AnglePID.CurrentError);
//    VOFA_Origin_Data[2] = (float)(P_stMotor_Gimbal_Yaw.SpeedPID.CurrentError);
//    VOFA_Origin_Data[3] = (float)(P_stMotor_Gimbal_Yaw.SpeedPID.CurrentValue);
//    VOFA_Origin_Data[4] = (float)(P_stMotor_Gimbal_Yaw.AnglePID.Target);
//    VOFA_Origin_Data[5] = (float)(P_stMotor_Gimbal_Yaw.AnglePID.CurrentValue);
//    VOFA_Origin_Data[6] = (float)(P_stMotor_Gimbal_Yaw.SpeedPID.Target);
//    VOFA_Origin_Data[7] = (float)(0);
//    VOFA_Origin_Data[8] = (float)();
//    VOFA_Origin_Data[9] = (float)();
    
    //���������ͻ�����
    memcpy(VOFA_Send_Data,(uint8_t *)VOFA_Origin_Data,sizeof(VOFA_Origin_Data));
    
    VOFA_DMAx_STREAMx ->NDTR = VOFA_SEND_SIZE;       //�������������Сд�� ���������Ĵ���NDTR
    DMA_Cmd(VOFA_DMAx_STREAMx, ENABLE);              //ʹ��DMA1_Stream6
}

void DMA1_Stream6_IRQHandler()  //DMA�ж�
{    
    if(DMA_GetITStatus(VOFA_DMAx_STREAMx,VOFA_DMA_IT_TCIFx))//��鴫������жϱ�־λ
	{
		DMA_ClearITPendingBit(VOFA_DMAx_STREAMx,VOFA_DMA_IT_TCIFx);//�����������жϱ�־λ
		DMA_Cmd(VOFA_DMAx_STREAMx, DISABLE);                     //�ر�DMA���ʹ���
    }
}
