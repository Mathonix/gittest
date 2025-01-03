#ifndef __MINIPC_H__
#define __MINIPC_H__
#include "main.h"

#define RED 0
#define BLUE 1
#define PC_VISION_DATA_BUFFER_LENGTH 11  //PC视觉数据缓存长度
#define PC_VISION_DATA_SEND_LENGTH 27

void Task_MiniPCDataDecode(void *pvParameters);
void Task_MiniPCDataSend(void *pvParameters);


typedef struct MiniPC_Send_Data_TypeDef
{
	u8 header;
	u8 save;
	int16_t vx;
	int16_t vy;
	int16_t vw;
	int8_t mode;
	int16_t target_x;
	int16_t target_y;
	int16_t target_w;
	u8 ctrl_mode;
	u16 tower_boold_blue;
	u16 tower_boold_red;
	u32 save1;
	u8 checksum;
	u8 ender;
}MiniPC_Send_Data_TypeDef;

typedef struct MiniPC_Recive_Data_TypeDef
{
	u8 header;
	u8 mode;
	u8 save;
	int16_t yaw;
	int16_t vx;
	int16_t vy;
	int16_t vw;
	u8 flag_pc_send;
	u8 checksum;
	u8 ender;
}MiniPC_Recive_Data_TypeDef;
extern float gim_yaw;
extern uint16_t P_nPCBuffLength;
extern uint8_t P_ucPCVisionDataBuffer[PC_VISION_DATA_BUFFER_LENGTH];          //PC_VISION数据缓存数组
extern MiniPC_Recive_Data_TypeDef MiniPC_Data_Recv;

void Task_MiniPCDataDecode(void *Parameters);
void Task_MiniPCDataSend(void *Parameters);
#endif
