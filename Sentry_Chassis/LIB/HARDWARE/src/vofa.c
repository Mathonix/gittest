#include "vofa.h"

float VOFA_Origin_Data[VOFA_MAX_CHANNELS];      //VOFA原数据频道数
uint8_t VOFA_Send_Data[VOFA_SEND_SIZE];         //VOFA发送数据数组

float test = 0;
/*--------------外部引用---------------*/



/*--------------外部引用---------------*/

void configVOFA_ParaInit(void)
{
    //写入justfloat结尾帧数据
    VOFA_Send_Data[VOFA_MAX_CHANNELS*4] = 0x00;                    
	VOFA_Send_Data[VOFA_MAX_CHANNELS*4+1] = 0x00;
	VOFA_Send_Data[VOFA_MAX_CHANNELS*4+2] = 0x80;
	VOFA_Send_Data[VOFA_MAX_CHANNELS*4+3] = 0x7f;
}

void VOFA_Send(void)
{
    //写入传输数据
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
    
    //复制至发送缓冲区
    memcpy(VOFA_Send_Data,(uint8_t *)VOFA_Origin_Data,sizeof(VOFA_Origin_Data));
    
    VOFA_DMAx_STREAMx ->NDTR = VOFA_SEND_SIZE;       //发送数据数组大小写入 数据数量寄存器NDTR
    DMA_Cmd(VOFA_DMAx_STREAMx, ENABLE);              //使能DMA1_Stream6
}

void DMA1_Stream6_IRQHandler()  //DMA中断
{    
    if(DMA_GetITStatus(VOFA_DMAx_STREAMx,VOFA_DMA_IT_TCIFx))//检查传输完成中断标志位
	{
		DMA_ClearITPendingBit(VOFA_DMAx_STREAMx,VOFA_DMA_IT_TCIFx);//清除传输完成中断标志位
		DMA_Cmd(VOFA_DMAx_STREAMx, DISABLE);                     //关闭DMA发送传输
    }
}
