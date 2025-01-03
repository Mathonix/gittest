#include "main.h"


void BSP_Init(void);
void Task_Init(void);
void Hardware_Init(void);


int main()
{
    BSP_Init();
    Hardware_Init();

    Task_Init();//创建开始任务
    vTaskStartScheduler();//开始任务调度
    while(1);
}


void BSP_Init(void)
{
    configIO_Init();
    configCAN_Init();
    configDMA_Init();
    configNVIC_Init();
    configUART_Init();
    
}

void Hardware_Init()
{
    configHi219m_ParaInit();
    configChassis_ParaInit();
    
}


