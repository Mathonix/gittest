#include "nvic.h"

void configNVIC_Init(void)
{
		NVIC_InitTypeDef       NVIC_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//中断优先级分组
	
    
    /*-------------------CAN----------------------*/
    //CAN1 NVIC
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;		//CAN1接收中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;		//CAN1发送中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	
	 //CAN2 NVIC
    NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
    NVIC_InitStructure.NVIC_IRQChannel = CAN2_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
    /*----------------UART------------------*/
		//USART1 NVIC
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                          
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //pre-emption priority 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		    //subpriority 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	

		//USART2 NVIC
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;                          
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //pre-emption priority 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		    //subpriority 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	
		//USART3 NVIC
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;                          
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //pre-emption priority 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		    //subpriority 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	
		//USART6
		NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =	0;
		NVIC_InitStructure.NVIC_IRQChannelCmd =	ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		//USART7
		NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =	0;
		NVIC_InitStructure.NVIC_IRQChannelCmd =	ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
        //UART8
		NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =	0;
		NVIC_InitStructure.NVIC_IRQChannelCmd =	ENABLE;
		NVIC_Init(&NVIC_InitStructure);

	/*-------------------------DMA---------------------------*/
		//VOFA
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =	0;
		NVIC_InitStructure.NVIC_IRQChannelCmd =	ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

//	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; //子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//		NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器2中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; //子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
