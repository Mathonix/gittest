#include "minipc.h"

uint8_t P_ucPCVisionDataBuffer[PC_VISION_DATA_BUFFER_LENGTH]; 
uint8_t P_ucPCVisionDataBuffer_Last[PC_VISION_DATA_BUFFER_LENGTH]; //PC_VISION数据缓存数组
uint8_t P_ucPCVisionDataBuffer_L[PC_VISION_DATA_BUFFER_LENGTH];
uint8_t P_ucPCVisionDataSender[PC_VISION_DATA_SEND_LENGTH];
MiniPC_Recive_Data_TypeDef MiniPC_Data_Recv;
u8 Send_Data[PC_VISION_DATA_SEND_LENGTH];
MiniPC_Send_Data_TypeDef MiniPC_Data_Send;
uint16_t P_nPCBuffLength = 0;

/**
 * @name miniPC数据解析任务
 * @brief 解析miniPC数据
 * @param void *pvParameters
 * @return void
 */
void Task_MiniPCDataDecode(void *pvParameters)
{
    portTickType CurrentControlTick = 0;
    while (1)
    {
        
        
        vTaskDelayUntil(&CurrentControlTick, 1/portTICK_RATE_MS);
    }
}

/**
 * @name miniPC数据发送任务
 * @brief 向miniPC发送数据
 * @param void *pvParameters
 * @return void
 */
void Task_MiniPCDataSend(void *pvParameters)
{
    portTickType CurrentControlTick = 0;
    while (1)
    {
        
        
        vTaskDelayUntil(&CurrentControlTick, 1/portTICK_RATE_MS);
    }
}
