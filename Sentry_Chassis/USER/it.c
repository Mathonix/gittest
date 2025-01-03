#include "it.h"

CanRxMsg P_stCAN1DataRecv; //CAN1数据接收结构体
CanRxMsg P_stCAN2DataRecv; //CAN2数据接收结构体

extern SemaphoreHandle_t P_stPCDataDecode_Binary;
extern SemaphoreHandle_t JudgeDataDecode_Binary;
extern SemaphoreHandle_t InfraredDecode_Binary;

uint16_t P_nJudgeBuffLength=0;

/*************************************************************************
*  函数名称：CAN1_TX_IRQHandler
*  功能说明：CAN1发送中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void CAN1_RX0_IRQHandler(void)
{   
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN1, CAN_FIFO0, &P_stCAN1DataRecv);	//接收数据
		
		fnMotor_CanRecvDataDecode(CAN1,&P_stCAN1DataRecv);	//电机处理数据
		
		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);	//清除中断标志位
		CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 	//清除标志位
	}
}
/*************************************************************************
*  函数名称：CAN1_RX0_IRQHandler
*  功能说明：CAN1接收中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：电机CAN传送数据解析
*************************************************************************/
void CAN1_TX_IRQHandler(void) //CAN TX
{
    if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
    }
}

/*************************************************************************
*  函数名称：CAN1_TX_IRQHandler
*  功能说明：CAN1发送中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void CAN2_RX0_IRQHandler(void)
{   
//	CanRxMsg P_stCAN2DataRecv;
	if(CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN2, CAN_FIFO0, &P_stCAN2DataRecv);	//接收数据
		
		fnMotor_CanRecvDataDecode(CAN2,&P_stCAN2DataRecv);	//电机处理数据
		
		CAN_ClearITPendingBit(CAN2, CAN_IT_FF0);	//清除中断标志位
		CAN_ClearFlag(CAN2, CAN_FLAG_FF0); 	//清除标志位
		 
	}
}

/**
 *  函数名称：CAN2_TX_IRQHandler
 *  功能说明：CAN2发送中断服务函数
 *  参数说明：无
 *  函数返回：无
 */
void CAN2_TX_IRQHandler(void) //CAN TX
{
    if(CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
    }
}

/**
 *  函数名称：USART1_IRQHandler
 *  功能说明：遥控器USART1中断
 *  参数说明：无
 *  函数返回：无
 */
void USART1_IRQHandler(void)            //遥控器USART1中断
{
		static uint32_t rx_len = 0;
		
		if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
		{
			//clear the idle pending flag 
			(void)USART1->SR;
			(void)USART1->DR;
			
			//Target is Memory0
			if(DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0)
			{
				DMA_Cmd(DMA2_Stream2, DISABLE);
				rx_len = REMOTE_DATA_RX_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
				DMA2_Stream2->NDTR = (uint16_t)REMOTE_DATA_RX_LEN;     //relocate the dma memory pointer to the beginning position
				DMA2_Stream2->CR |= (uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 1
				DMA_Cmd(DMA2_Stream2, ENABLE);
				if(rx_len == REMOTE_DATAFRAME_LEN)
				{
					fnRemote_RawDataDecode(&P_stRemoteData_Recv,P_uintRemote_Data_Buf[0]);
				}
			}
			//Target is Memory1
			else 
			{
				DMA_Cmd(DMA2_Stream2, DISABLE);
				rx_len = REMOTE_DATA_RX_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
				DMA2_Stream2->NDTR = (uint16_t)REMOTE_DATA_RX_LEN;      //relocate the dma memory pointer to the beginning position
				DMA2_Stream2->CR &= ~(uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 0
				DMA_Cmd(DMA2_Stream2, ENABLE);
				if(rx_len == REMOTE_DATAFRAME_LEN)
				{
					fnRemote_RawDataDecode(&P_stRemoteData_Recv,P_uintRemote_Data_Buf[1]);
				}
			}
		}    
}
/**
 * 函数名称：USART3_IRQHandler
 *  功能说明：VOFA调试用USART3接收中断
 *  参数说明：无
 *  函数返回：无
 */
void USART3_IRQHandler(void)            //VOFA调试用USART3中断
{
    
}

/**
 * 函数名称：USART6_IRQHandler
 * 功能说明：裁判系统USART6接收中断
 * 参数说明：无
 * 函数返回：无
 */
void USART6_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken;
//    uint8_t utempUART;
	if(USART_GetITStatus(USART6,USART_IT_IDLE) != RESET)
	{
		USART6->DR;
		USART6->SR;
		DMA_Cmd(DMA2_Stream1, DISABLE); 
		P_nJudgeBuffLength=JUDGE_BUFFER_LENGTH-(DMA2_Stream1->NDTR);//获取接受数据的长度
		RM_Judge_DataEnqueue((unsigned char *)P_ucJudgeDataBuffer,&P_stJudgeDataArrayListBuff,P_nJudgeBuffLength);//数据入队
		DMA2_Stream1->NDTR=JUDGE_BUFFER_LENGTH; 
		//重启DMA
		DMA_ClearFlag(DMA2_Stream1, DMA_FLAG_TCIF1 | DMA_FLAG_HTIF1);
		while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
		DMA_SetCurrDataCounter(DMA2_Stream1, JUDGE_BUFFER_LENGTH);
		DMA_Cmd(DMA2_Stream1, ENABLE);
	
		if(JudgeDataDecode_Binary!=NULL)//若未创建切换任务会死机
		{
			xSemaphoreGiveFromISR(JudgeDataDecode_Binary,&xHigherPriorityTaskWoken);//释放二值信号量
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}
}

/**
 * 函数名称：UART7_IRQHandler
 * 功能说明：miniPC UART7接收中断
 * 参数说明：无
 * 函数返回：无
 */
void UART7_IRQHandler(void)            //miniPC接收UART7中断
{
    
}

/**
 * 函数名称：UART8_IRQHandler
 * 功能说明：陀螺仪Hi229接收UART8中断
 * 参数说明：无
 * 函数返回：无
 */
void UART8_IRQHandler(void)            //陀螺仪Hi229接收UART8中断
{

}
