#include "it.h"

CanRxMsg P_stCAN1DataRecv; //CAN1���ݽ��սṹ��
CanRxMsg P_stCAN2DataRecv; //CAN2���ݽ��սṹ��

extern SemaphoreHandle_t P_stPCDataDecode_Binary;
extern SemaphoreHandle_t JudgeDataDecode_Binary;
extern SemaphoreHandle_t InfraredDecode_Binary;

uint16_t P_nJudgeBuffLength=0;

/*************************************************************************
*  �������ƣ�CAN1_TX_IRQHandler
*  ����˵����CAN1�����жϷ�����
*  ����˵������
*  �������أ���	 
*  ��    ע����
*************************************************************************/
void CAN1_RX0_IRQHandler(void)
{   
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN1, CAN_FIFO0, &P_stCAN1DataRecv);	//��������
		
		fnMotor_CanRecvDataDecode(CAN1,&P_stCAN1DataRecv);	//�����������
		
		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);	//����жϱ�־λ
		CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 	//�����־λ
	}
}
/*************************************************************************
*  �������ƣ�CAN1_RX0_IRQHandler
*  ����˵����CAN1�����жϷ�����
*  ����˵������
*  �������أ���	 
*  ��    ע�����CAN�������ݽ���
*************************************************************************/
void CAN1_TX_IRQHandler(void) //CAN TX
{
    if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
    }
}

/*************************************************************************
*  �������ƣ�CAN1_TX_IRQHandler
*  ����˵����CAN1�����жϷ�����
*  ����˵������
*  �������أ���	 
*  ��    ע����
*************************************************************************/
void CAN2_RX0_IRQHandler(void)
{   
//	CanRxMsg P_stCAN2DataRecv;
	if(CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN2, CAN_FIFO0, &P_stCAN2DataRecv);	//��������
		
		fnMotor_CanRecvDataDecode(CAN2,&P_stCAN2DataRecv);	//�����������
		
		CAN_ClearITPendingBit(CAN2, CAN_IT_FF0);	//����жϱ�־λ
		CAN_ClearFlag(CAN2, CAN_FLAG_FF0); 	//�����־λ
		 
	}
}

/**
 *  �������ƣ�CAN2_TX_IRQHandler
 *  ����˵����CAN2�����жϷ�����
 *  ����˵������
 *  �������أ���
 */
void CAN2_TX_IRQHandler(void) //CAN TX
{
    if(CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
    }
}

/**
 *  �������ƣ�USART1_IRQHandler
 *  ����˵����ң����USART1�ж�
 *  ����˵������
 *  �������أ���
 */
void USART1_IRQHandler(void)            //ң����USART1�ж�
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
 * �������ƣ�USART3_IRQHandler
 *  ����˵����VOFA������USART3�����ж�
 *  ����˵������
 *  �������أ���
 */
void USART3_IRQHandler(void)            //VOFA������USART3�ж�
{
    
}

/**
 * �������ƣ�USART6_IRQHandler
 * ����˵��������ϵͳUSART6�����ж�
 * ����˵������
 * �������أ���
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
		P_nJudgeBuffLength=JUDGE_BUFFER_LENGTH-(DMA2_Stream1->NDTR);//��ȡ�������ݵĳ���
		RM_Judge_DataEnqueue((unsigned char *)P_ucJudgeDataBuffer,&P_stJudgeDataArrayListBuff,P_nJudgeBuffLength);//�������
		DMA2_Stream1->NDTR=JUDGE_BUFFER_LENGTH; 
		//����DMA
		DMA_ClearFlag(DMA2_Stream1, DMA_FLAG_TCIF1 | DMA_FLAG_HTIF1);
		while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
		DMA_SetCurrDataCounter(DMA2_Stream1, JUDGE_BUFFER_LENGTH);
		DMA_Cmd(DMA2_Stream1, ENABLE);
	
		if(JudgeDataDecode_Binary!=NULL)//��δ�����л����������
		{
			xSemaphoreGiveFromISR(JudgeDataDecode_Binary,&xHigherPriorityTaskWoken);//�ͷŶ�ֵ�ź���
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}
}

/**
 * �������ƣ�UART7_IRQHandler
 * ����˵����miniPC UART7�����ж�
 * ����˵������
 * �������أ���
 */
void UART7_IRQHandler(void)            //miniPC����UART7�ж�
{
    
}

/**
 * �������ƣ�UART8_IRQHandler
 * ����˵����������Hi229����UART8�ж�
 * ����˵������
 * �������أ���
 */
void UART8_IRQHandler(void)            //������Hi229����UART8�ж�
{

}
