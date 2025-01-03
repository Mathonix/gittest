#include "uart.h"

void configUART_Init(void)
{
		USART_InitTypeDef USART_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8,ENABLE);
	
		//USART1 SBUS
		USART_DeInit(USART1);
		USART_StructInit(&USART_InitStructure);
		USART_InitStructure.USART_BaudRate = 100000;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_Even;
		USART_InitStructure.USART_Mode = USART_Mode_Rx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART1, &USART_InitStructure);
		USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); 
		USART_Cmd(USART1,ENABLE);
        
        //USART2 VOFA用调试串口
        USART_DeInit(USART2);
        USART_StructInit(&USART_InitStructure);
        USART_InitStructure.USART_BaudRate = 115200;         
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_Init(USART2,&USART_InitStructure);
        USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
        USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
        USART_Cmd(USART2,ENABLE);
        
		//USART3 线顺不同
        USART_DeInit(USART3);
        USART_StructInit(&USART_InitStructure);
        USART_InitStructure.USART_BaudRate = 115200;         
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_Init(USART3,&USART_InitStructure);
        USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
        USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);
        USART_Cmd(USART3,ENABLE);
	
        //Judge USART6
		USART_DeInit(USART6);
		USART_StructInit(&USART_InitStructure);
		USART_InitStructure.USART_BaudRate = 115200; //接收器固定波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART6, &USART_InitStructure);
		USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);
		USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE);
        USART_ITConfig(USART6, USART_IT_IDLE, ENABLE); //使能串口空闲中断
        USART_Cmd(USART6,ENABLE);
        
        //miniPC UART7
		USART_DeInit(UART7);
		USART_StructInit(&USART_InitStructure);
		USART_InitStructure.USART_BaudRate = 115200;         
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(UART7,&USART_InitStructure);
		USART_DMACmd(UART7, USART_DMAReq_Rx, ENABLE);
		USART_DMACmd(UART7, USART_DMAReq_Tx, ENABLE);
		USART_ITConfig(UART7,USART_IT_IDLE,ENABLE);		//使能串口空闲中断
		USART_Cmd(UART7,ENABLE);
	
	

		
		//没配DMA	
        //H219 UART8
        USART_DeInit(UART8);
        USART_StructInit(&USART_InitStructure);
        USART_InitStructure.USART_BaudRate = 115200;         
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_Init(UART8,&USART_InitStructure);
          USART_DMACmd(UART8, USART_DMAReq_Rx, ENABLE);
        USART_ITConfig(UART8,USART_IT_IDLE,ENABLE);
        USART_Cmd(UART8,ENABLE);
		

		

}
