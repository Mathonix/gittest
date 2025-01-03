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

SemaphoreHandle_t P_shH219DataDecode_Binary;    //Hi219m���ݴ��������ֵ�ź���
SemaphoreHandle_t P_stPCDataDecode_Binary;      //miniPC���ݴ��������ֵ�ź���
SemaphoreHandle_t JudgeDataDecode_Binary;       //Judge���ݴ��������ֵ�ź���




/**
 * @name       ����ϵͳ���ݴ�������
 * @brief      ��������ϵͳ����
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
			stError=xSemaphoreTake(JudgeDataDecode_Binary,portMAX_DELAY);	//��ȡ�ź���
			if(stError==pdTRUE)												//��ȡ�ź����ɹ�
			{
				RM_Judge_DataDecodeByBuff(P_ucJudgeDataBuffer);	//�������ݽ������������ݷ�ʽ��
			}
		}
		else if(stError==pdFALSE)
		{
			vTaskDelay(10);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
		}
        }
}

/**
 * @name       Hi219m���ݴ�������
 * @brief      ��������������
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
	        stError=xSemaphoreTake(P_shH219DataDecode_Binary,portMAX_DELAY);	//��ȡ�ź���
		if(stError==pdTRUE)	//��ȡ�ź����ɹ�
		{
		    for (i = 0;i < P_uintH219BuffLength;i++)  
			{  
			    ch = P_uintH219MDataBuffer[i]; 
			    Packet_Decode(ch);
					
			    fnHi219m_DataDecode(&P_stHi219m); //��ȡ������ֵ
			} 
		}
		
		else if(stError==pdFALSE)
		{
		    vTaskDelay(10);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
		}
	    }
        }
}

/**
 * @name      ��̨�巢������
 * @brief     ���͵�����������̨��ת������ϵͳ��������̨
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
     xTaskCreate((TaskFunction_t)Start_Task,          //������
                (const char *)"Start_Task",          //��������
                (uint16_t)START_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)START_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&StartTask_Handler); //������
}

void Start_Task(void)
{
        P_shH219DataDecode_Binary = xSemaphoreCreateBinary();
	P_stPCDataDecode_Binary = xSemaphoreCreateBinary();   	//miniPC���ݴ�������
	JudgeDataDecode_Binary = xSemaphoreCreateBinary();	//Judge���ݴ��������ֵ�ź���
	//initArray(&P_stJudgeDataArrayListBuff,200);

        taskENTER_CRITICAL(); //�����ٽ���

        xTaskCreate((TaskFunction_t)Task_ChassisCtrl,          //������
                (const char *)"Task_ChassisCtrl",          //��������
                (uint16_t)TASK_CHASSISCTRL_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)TASK_CHASSISCTRL_PRIO,        //�������ȼ�
                (TaskHandle_t *)&Task_ChassisCtrl_Handler); //������
    
        xTaskCreate((TaskFunction_t)Task_Send2Gimbal,          //������
                (const char *)"Task_Send2Gimbal",          //��������
                (uint16_t)    TASK_SEND2GIMBAL_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t) TASK_SEND2GIMBAL_PRIO,        //�������ȼ�
                (TaskHandle_t *)&Task_Send2Gimbal_Handler); //������

        xTaskCreate((TaskFunction_t)Task_MiniPCDataDecode,          //������
                (const char *)"Task_MiniPCDataDecode",          //��������
                (uint16_t)TASK_MINIPCDATADECODE_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)TASK_MINIPCDATADECODE_PRIO,        //�������ȼ�
                (TaskHandle_t *)&Task_MiniPCDataDecode_Handler); //������

        xTaskCreate((TaskFunction_t)Task_MiniPCDataSend,          //������
                (const char *)"Task_MiniPCDataSend",          //��������
                (uint16_t)TASK_MINIPCDATASEND_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)TASK_MINIPCDATASEND_PRIO,        //�������ȼ�
                (TaskHandle_t *)&Task_MiniPCDataSend_Handler); //������
        
        xTaskCreate((TaskFunction_t)Task_Hi219mDataDecode,          //������
                (const char *)"Task_Hi219mDataDecode",          //��������
                (uint16_t)TASK_HI219MDATADECODE_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)TASK_HI219MDATADECODE_PRIO,        //�������ȼ�
                (TaskHandle_t *)&Task_Hi219mDataDecode_Handler); //������

        xTaskCreate((TaskFunction_t)Task_JudgeDataDecode,          //������
                (const char *)"Task_JudgeDataDecode",          //��������
                (uint16_t)TASK_JUDGEDATADECODE_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)TASK_JUDGEDATADECODE_PRIO,        //�������ȼ�
                (TaskHandle_t *)&Task_JudgeDataDecode_Handler); //������
        
        xTaskCreate((TaskFunction_t)Task_JudgeDataDecode,          //������
                (const char *)"Task_JudgeDataDecode",          //��������
                (uint16_t)TASK_JUDGEDATADECODE_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)TASK_JUDGEDATADECODE_PRIO,        //�������ȼ�
                (TaskHandle_t *)&Task_JudgeDataDecode_Handler); //������

        taskEXIT_CRITICAL(); //�˳��ٽ���

        vTaskDelete(StartTask_Handler); //ɾ����ʼ����
} 
