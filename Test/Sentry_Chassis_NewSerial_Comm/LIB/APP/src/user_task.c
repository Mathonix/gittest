#include "user_task.h"

#define START_TASK_PRIO 1
#define START_STK_SIZE 128

#define TASK_CHASSISCTRL_PRIO 3
#define TASK_CHASSISCTRL_STK_SIZE 300

#define TASK_MINIPCDATASEND_PRIO 4
#define TASK_MINIPCDATASEND_STK_SIZE 300

#define TASK_MINIPCDATADECODE_PRIO 4
#define TASK_MINIPCDATADECODE_STK_SIZE 300

#define TASK_HI219MDATADECODE_PRIO 4
#define TASK_HI219MDATADECODE_STK_SIZE 300

#define TASK_JUDGEDATADECODE_PRIO 4
#define TASK_JUDGEDATADECODE_STK_SIZE 200

#define TASK_SEND2GIMBAL_PRIO 4
#define TASK_SEND2GIMBAL_STK_SIZE 200

TaskHandle_t StartTask_Handler;
TaskHandle_t Task_ChassisCtrl_Handler;
TaskHandle_t Task_MiniPCDataDecode_Handler;
TaskHandle_t Task_MiniPCDataSend_Handler;
TaskHandle_t Task_Hi219mDataDecode_Handler;
TaskHandle_t Task_JudgeDataDecode_Handler;
TaskHandle_t Task_Send2Gimbal_Handler;

SemaphoreHandle_t P_shH219DataDecode_Binary;    //Hi219m数据处理任务二值信号量
SemaphoreHandle_t P_stPCDataDecode_Binary;      //miniPC数据处理任务二值信号量
SemaphoreHandle_t JudgeDataDecode_Binary;       //Judge数据处理任务二值信号量




/**
 * @name       裁判系统数据处理任务
 * @brief      解析裁判系统数据
 * @param[in]  void
 * @retval     void
 */
void Task_JudgeDataDecode(void)
{
    BaseType_t stError=pdFALSE;
        while(1)
	{
		if(JudgeDataDecode_Binary!=NULL)
		{
			stError=xSemaphoreTake(JudgeDataDecode_Binary,portMAX_DELAY);	//获取信号量
			if(stError==pdTRUE)												//获取信号量成功
			{
				RM_Judge_DataDecodeByBuff(P_ucJudgeDataBuffer);	//裁判数据解析（缓存数据方式）
			}
		}
		else if(stError==pdFALSE)
		{
			vTaskDelay(10);      //延时10ms，也就是10个时钟节拍	
		}
        }
}

/**
 * @name       Hi219m数据处理任务
 * @brief      解析陀螺仪数据
 * @param[in]  void
 * @retval     void
 */
void Task_Hi219mDataDecode(void)
{
    
    	BaseType_t stError=pdFALSE;
	uint16_t i = 0;
	uint8_t ch;
        while(1)
        {
            if(P_shH219DataDecode_Binary!=NULL)
	    {
	        stError=xSemaphoreTake(P_shH219DataDecode_Binary,portMAX_DELAY);	//获取信号量
		if(stError==pdTRUE)	//获取信号量成功
		{
		    for (i = 0;i < P_uintH219BuffLength;i++)  
			{  
			    ch = P_uintH219MDataBuffer[i]; 
			    Packet_Decode(ch);
					
			    fnHi219m_DataDecode(&P_stHi219m); //获取陀螺仪值
			} 
		}
		
		else if(stError==pdFALSE)
		{
		    vTaskDelay(10);      //延时10ms，也就是10个时钟节拍	
		}
	    }
        }
}

/**
 * @name      云台板发送任务
 * @brief     发送底盘数据至云台，转发裁判系统数据至云台
 * @param[in] void
 * @retval    void
 */
void Task_Send2Gimbal(void)
{
    portTickType CurrentControlTick = 0;
    while(1)
    {
        
        vTaskDelayUntil(&CurrentControlTick, 1/portTICK_RATE_MS);
    } 
}


















void Task_Init(void)
{
     xTaskCreate((TaskFunction_t)Start_Task,          //任务函数
                (const char *)"Start_Task",          //任务名称
                (uint16_t)START_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)START_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&StartTask_Handler); //任务句柄
}

void Start_Task(void)
{
        P_shH219DataDecode_Binary = xSemaphoreCreateBinary();
	P_stPCDataDecode_Binary = xSemaphoreCreateBinary();   	//miniPC数据处理任务
	JudgeDataDecode_Binary = xSemaphoreCreateBinary();	//Judge数据处理任务二值信号量
	//initArray(&P_stJudgeDataArrayListBuff,200);

        taskENTER_CRITICAL(); //进入临界区

        xTaskCreate((TaskFunction_t)Task_ChassisCtrl,          //任务函数
                (const char *)"Task_ChassisCtrl",          //任务名称
                (uint16_t)TASK_CHASSISCTRL_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)TASK_CHASSISCTRL_PRIO,        //任务优先级
                (TaskHandle_t *)&Task_ChassisCtrl_Handler); //任务句柄
    
        xTaskCreate((TaskFunction_t)Task_Send2Gimbal,          //任务函数
                (const char *)"Task_Send2Gimbal",          //任务名称
                (uint16_t)    TASK_SEND2GIMBAL_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t) TASK_SEND2GIMBAL_PRIO,        //任务优先级
                (TaskHandle_t *)&Task_Send2Gimbal_Handler); //任务句柄

        xTaskCreate((TaskFunction_t)Task_MiniPCDataDecode,          //任务函数
                (const char *)"Task_MiniPCDataDecode",          //任务名称
                (uint16_t)TASK_MINIPCDATADECODE_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)TASK_MINIPCDATADECODE_PRIO,        //任务优先级
                (TaskHandle_t *)&Task_MiniPCDataDecode_Handler); //任务句柄

        xTaskCreate((TaskFunction_t)Task_MiniPCDataSend,          //任务函数
                (const char *)"Task_MiniPCDataSend",          //任务名称
                (uint16_t)TASK_MINIPCDATASEND_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)TASK_MINIPCDATASEND_PRIO,        //任务优先级
                (TaskHandle_t *)&Task_MiniPCDataSend_Handler); //任务句柄
        
        xTaskCreate((TaskFunction_t)Task_Hi219mDataDecode,          //任务函数
                (const char *)"Task_Hi219mDataDecode",          //任务名称
                (uint16_t)TASK_HI219MDATADECODE_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)TASK_HI219MDATADECODE_PRIO,        //任务优先级
                (TaskHandle_t *)&Task_Hi219mDataDecode_Handler); //任务句柄

        xTaskCreate((TaskFunction_t)Task_JudgeDataDecode,          //任务函数
                (const char *)"Task_JudgeDataDecode",          //任务名称
                (uint16_t)TASK_JUDGEDATADECODE_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)TASK_JUDGEDATADECODE_PRIO,        //任务优先级
                (TaskHandle_t *)&Task_JudgeDataDecode_Handler); //任务句柄
        
        xTaskCreate((TaskFunction_t)Task_JudgeDataDecode,          //任务函数
                (const char *)"Task_JudgeDataDecode",          //任务名称
                (uint16_t)TASK_JUDGEDATADECODE_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)TASK_JUDGEDATADECODE_PRIO,        //任务优先级
                (TaskHandle_t *)&Task_JudgeDataDecode_Handler); //任务句柄

        taskEXIT_CRITICAL(); //退出临界区

        vTaskDelete(StartTask_Handler); //删除开始任务
} 
