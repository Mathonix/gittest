#include "judge.h"

uint8_t P_ucJudgeDataBuffer[JUDGE_BUFFER_LENGTH];  					//Judge数据缓存数组
struct ArrayList P_stJudgeDataArrayListBuff;//裁判系统串口接受数据缓冲 //用于解决粘包，半包等问题
u8 Send_Data_Lidar[3];
fn_P_stgamestatus P_stgamestatus;

fn_game_robot_pos_t fn_game_robot_pos;
//SemaphoreHandle_t JudgeDataDecode_Binary;
u16 x_c;
///*************************************************************************
//*  函数名称：Task_JudgeDataDecode
//*  功能说明：Judge裁判系统解析数据任务
//*  参数说明：void *Parameters
//*  函数返回：无
//*  备    注：
//*************************************************************************/
//void Task_JudgeDataDecode(void *Parameters)
//{
//    BaseType_t stError=pdFALSE;
//	while(1)
//	{
//		if(JudgeDataDecode_Binary!=NULL)
//		{
//			stError=xSemaphoreTake(JudgeDataDecode_Binary,portMAX_DELAY);	//获取信号量
//			if(stError==pdTRUE)												//获取信号量成功
//			{
//				RM_Judge_DataDecodeByBuff(P_ucJudgeDataBuffer);	//裁判数据解析（缓存数据方式）
//			}
//		}
//		else if(stError==pdFALSE)
//		{
//			vTaskDelay(10);      //延时10ms，也就是10个时钟节拍	
//		}
//	}
//}

void RM_Judge_DataDecodeByBuff(uint8_t *pDecodeData)
{
	u8 nTempData[150] = { 0 };
	
	while(RM_Judge_FindFrame(&P_stJudgeDataArrayListBuff))	//查找完整数据帧
	{
		int nDataLenth=RM_Judge_DataLength(&P_stJudgeDataArrayListBuff);  //获取完整帧数据长度
		RM_Judge_DataDequeue(nTempData,&P_stJudgeDataArrayListBuff,0,nDataLenth);
		x_c=(uint16_t)(nTempData[6]<<8|nTempData[5]);

		switch(x_c)//
		{
			case 0x0001:
			{
				memcpy(&P_stgamestatus.game_status,nTempData,JUDGE_GAME_STATE_DATA_LENGTH);    //拷贝比赛状态数据
			};break;
			case 0x0002:
			{
				memcpy(&P_stgamestatus.game_result,nTempData,JUDGE_GAME_RESULT_LENGTH);    //拷贝比赛结果数据**
			};break;
			case 0x0003:
			{
				memcpy(&P_stgamestatus.game_robot_HP,nTempData,JUDGE_GAME_ROBOT_HP_LENGTH);    //拷贝实时机器人血量数据
			}break;
			case 0x0005:
			{
				memcpy(&P_stgamestatus.ICRA_buff_debuff_zone_status,nTempData,JUDGE_ICRA_BUFF_DEBUFF_ZONE_STATUS);    //拷贝ICRA数据**
			}break;
			case 0x0101:
			{
				memcpy(&P_stgamestatus.event_data,nTempData,JUDGE_EVENT_DATA_LENGTH);    //拷贝场地事件数据
			}break;
			case 0x0102:
			{
				memcpy(&P_stgamestatus.supply_projectile_action,nTempData,JUDGE_SUPPLY_ACTION_LENGTH);    //拷贝场地事件数据**
			}break;

			case 0x0104:
			{
				memcpy(&P_stgamestatus.referee_warning,nTempData,JUDGE_REFEREE_WARNING_LENGTH);    //拷贝场地事件数据**
			}break;
			case 0x0105:
			{
				memcpy(&P_stgamestatus.dart_remaining_time,nTempData,JUDGE_DART_REMAINING_TIME_LENGTH);    //拷贝场地事件数据
			}break;
			case 0x0201:
			{
				memcpy(&P_stgamestatus.game_robot_status,nTempData,JUDGE_ROBOT_STAUS_LENGTH);    //拷贝场地事件数据
			}break;
			case 0x0202:
			{
				memcpy(&P_stgamestatus.power_heat_data,nTempData,JUDGE_POWER_DATA_LENGTH);    //拷贝场地事件数据
			}break;
			case 0x0203:
			{
				memcpy(&P_stgamestatus.game_robot_pos,nTempData,JUDGE_ROBOT_POS_LENGTH);    //拷贝场地事件数据
			}break;
			case 0x0204:
			{
				memcpy(&P_stgamestatus.buff,nTempData,JUDGE_ROBOT_BUFF_LENGTH);    //拷贝场地事件数据
			}break;
			case 0x0205:
			{
				memcpy(&P_stgamestatus.aerial_robot_energy,nTempData,JUDGE_AERIAL_ROBOT_ENERGY_LENGTH);    //拷贝场地事件数据**
			}break;
			case 0x0206:
			{
				memcpy(&P_stgamestatus.robot_hurt,nTempData,JUDGE_ROBOT_HURT_LENGTH);    //拷贝场地事件数据**
			}break;
			case 0x0207:
			{
				memcpy(&P_stgamestatus.shoot_data,nTempData,JUDGE_SHOOT_DATA_LENGTH);    //拷贝场地事件数据**
			}break;
			case 0x0208:
			{
				memcpy(&P_stgamestatus.bullet_remaining,nTempData,JUDGE_BULLET_REMAINING_LENGTH);    //拷贝场地事件数据
			}break;
			case 0x0209:
			{
				memcpy(&P_stgamestatus.rfid_status,nTempData,JUDGE_RFID_STATUS_LENGTH);    //拷贝场地事件数据
			}break;
			case 0x020A:
			{
				memcpy(&P_stgamestatus.dart_client_cmd,nTempData,JUDGE_DART_CMD_LENGTH);    //拷贝场地事件数据**
			}break;
			case 0x020B:
			{
				memcpy(&P_stgamestatus.location,nTempData,JUDGE_LOCATION_LENGTH);
			}break;
			case 0x020C:
			{
				memcpy(&P_stgamestatus.mark_data,nTempData,JUDGE_MARK_LENGTH);
			}break;
			case 0x020D:
			{
				memcpy(&P_stgamestatus.Sentry_Data,nTempData,JUDGE_SENTRY_DATA_LENGTH_AUTOCHOOSE);
			}break;
			case 0x0301:
			{
				memcpy(&P_stgamestatus.robot_interaction,nTempData,JUDGE_ROBOT_DATA_SENDOTHER_LENGTH);
			}break;
			case 0x0303:
			{
				memcpy(&P_stgamestatus.map_command,nTempData,JUDGE_MAP_DATA_LENGTH);
			}break;
			case 0x0304:
			{
				memcpy(&P_stgamestatus.remote_control,nTempData,JUDGE_REMOTE_DATA_LENGTH);
			}break;
			case 0x0305:
			{
				memcpy(&P_stgamestatus.map_robot,nTempData,JUDGE_LIDARMAP_DATA_LENGTH);
			}break;
			default:
			{};break;
		}

	}	
}

bool RM_Judge_FindFrame(struct ArrayList * arrlist)
{
	int HeadIndex=0,length=0;
	if (RM_ArrayList_GetArrayLength(arrlist) == 0)	//长度为零则返回
	{
		return false;
	}
	HeadIndex = findValue(arrlist, 0xA5);	//查找帧头
	if (HeadIndex == -1)	//没找到帧头就删除所有缓冲区所有数据
	{
		deleteAllValue(arrlist);	
		return false;
	}
	else if (HeadIndex != 0)
	{
		if (HeadIndex > 1) //移除帧头前的所有数据
		{
			deleteRangeValue(arrlist, 0, HeadIndex-1);	
		}
	}
	if ((arrlist->total) < 5)	//帧头接收数据不完整，返回
	{
		return false;
	}
    length = RM_Judge_DataLength(arrlist);	//获取裁判系统数据长度 
	if(length == -1)
	{
		deleteAllValue(arrlist);
		return false;
	}
	if(!RM_Judge_CRC8Check((unsigned char *)(arrlist->qarr),5))	//帧头数据校验
	{
		deleteAllValue(arrlist);
		return false;
	}
	if ((arrlist->total) < length)	//数据不完整，可能出现了半包情况所以列表数据不清空，
	{
		return false;
	}
	if(!RM_Judge_CRC16Check((unsigned char *)(arrlist->qarr),length))	//全帧校验  出错可能是因为出现多帧粘包，并且上一帧数据不完整，需剔除
	{
		int lastHeadIndex=HeadIndex;
		HeadIndex=findValue(arrlist+lastHeadIndex,0xA5); //查找下一个帧头
		if (HeadIndex == -1)	//没找到帧头就删除所有缓冲区所有数据
		{
			deleteAllValue(arrlist);	
			return false;
		}
		else if (HeadIndex != 0)
		{
			if (HeadIndex > lastHeadIndex) //移除第一个帧头前的所有数据
			{
				deleteRangeValue(arrlist, lastHeadIndex, HeadIndex-1);	
			}
			
		}
		RM_ArrayList_DeleteAllValue(arrlist);
		return false;	
	}
	return true;
}

int RM_Judge_DataLength(struct ArrayList * arrlist)
{
	uint16_t len=0;
	uint16_t cmd=0;
	cmd=(uint16_t)(arrlist->qarr[6] << 8 | arrlist->qarr[5]);	//获取长度
	len = (uint16_t)(arrlist->qarr[2] << 8 | arrlist->qarr[1]);	//获取长度
    switch (cmd) //第三字节为序号  
	{
		case 0x0001: //比赛机器人状态
		{
			if(len==(JUDGE_GAME_STATE_DATA_LENGTH-9))
			{
				return JUDGE_GAME_STATE_DATA_LENGTH;
			}
		}
		case 0x0002: //伤害数据
		{
			if(len==(JUDGE_GAME_RESULT_LENGTH-9))
			{
				return JUDGE_GAME_RESULT_LENGTH;
			}
		}
		case 0x0003: //实时射击数据
		{
			if(len==(JUDGE_GAME_ROBOT_HP_LENGTH-9))
			{
				return JUDGE_GAME_ROBOT_HP_LENGTH;
			}
		}
		case 0x0004: //实时功率和热量数据
		{
			if(len==(JUDGE_DART_STATUS_LENGTH-9))
			{
				return JUDGE_DART_STATUS_LENGTH;
			}
		}
		case 0x0005: //实时场地交互数据
		{
			if(len==(JUDGE_ICRA_BUFF_DEBUFF_ZONE_STATUS-9))
			{
				return JUDGE_ICRA_BUFF_DEBUFF_ZONE_STATUS;
			}
		}
		case 0x0101: //比赛结果数据 比赛结束时发送一次
		{
			if(len==(JUDGE_EVENT_DATA_LENGTH-9))
			{
				return JUDGE_EVENT_DATA_LENGTH;
			}
		}
		case 0x0102: //获取到Buff数据
		{
			if(len==(JUDGE_SUPPLY_ACTION_LENGTH-9))
			{
				return JUDGE_SUPPLY_ACTION_LENGTH;
			}
		}
		case 0x0104: //机器人位置和枪口朝向数据 
		{
			if(len==(JUDGE_REFEREE_WARNING_LENGTH-9))
			{
				return JUDGE_REFEREE_WARNING_LENGTH;
			}
		}
		case 0x0105: //0x0105飞镖发射口倒计时
		{
			if(len==(JUDGE_DART_REMAINING_TIME_LENGTH-9))
			{
				return JUDGE_DART_REMAINING_TIME_LENGTH;
			}
		}
		case 0x0201: //0x0201比赛机器人状态
		{
			if(len==(JUDGE_ROBOT_STAUS_LENGTH-9))
			{
				return JUDGE_ROBOT_STAUS_LENGTH;
			}
		}
		case 0x0202: //0x0202实时功率热量数据
		{
			if(len==(JUDGE_POWER_DATA_LENGTH-9))
			{
				return JUDGE_POWER_DATA_LENGTH;
			}
		}
		case 0x0203: //0x0203机器人位置数据
		{
			if(len==(JUDGE_ROBOT_POS_LENGTH-9))
			{
				return JUDGE_ROBOT_POS_LENGTH;
			}
		}
		case 0x0204://0x0204机器人增益
		{
			if(len==(JUDGE_ROBOT_BUFF_LENGTH-9))
			{
				return JUDGE_ROBOT_BUFF_LENGTH;
			}
		}
		case 0x0205: //0x0205空中机器人能量状态
		{
			if(len==(JUDGE_AERIAL_ROBOT_ENERGY_LENGTH-9))
			{
				return JUDGE_AERIAL_ROBOT_ENERGY_LENGTH;
			}
		}
		case 0x0206: //0x0206伤害状态
		{
			if(len==(JUDGE_ROBOT_HURT_LENGTH-9))
			{
				return JUDGE_ROBOT_HURT_LENGTH;
			}
		}
		case 0x0207://0x0207实时射击信息
		{
			if(len==(JUDGE_SHOOT_DATA_LENGTH-9))
			{
				return JUDGE_SHOOT_DATA_LENGTH;
			}
		}
		case 0x0208://0x0208子弹剩余发射数
		{
			if(len==(JUDGE_BULLET_REMAINING_LENGTH-9))
			{
				return JUDGE_BULLET_REMAINING_LENGTH;
			}
		}
		case 0x0209: //0x0209机器人RFID状态
		{
			if(len==(JUDGE_RFID_STATUS_LENGTH-9))
			{
				return JUDGE_RFID_STATUS_LENGTH;
			}
		}
		case 0x020A: //0x020A飞镖机器人客户端数据
		{
			if(len==(JUDGE_DART_CMD_LENGTH-9))
			{
				return JUDGE_DART_CMD_LENGTH;
			}
		}
		case 0x020B://0x020B机器人位置数据
		{
			if(len==(JUDGE_LOCATION_LENGTH-9))
			{
				return JUDGE_LOCATION_LENGTH;
			}
		}
		case 0x020C://0x020C敌方机器人被雷达标记进度
		{
			if(len==(JUDGE_MARK_LENGTH-9))
			{
				return JUDGE_MARK_LENGTH;
			}
		}
		case 0x020D://哨兵自主决策信息同步 0x020D
		{
			if(len==(JUDGE_SENTRY_DATA_LENGTH_AUTOCHOOSE-9))
			{
				return JUDGE_SENTRY_DATA_LENGTH_AUTOCHOOSE;
			}
		}
		case 0x020E:
		{
			if(len==(JUDGE_LIDAR_DATA_LENGTH_AUTOCHOOSE-9))
			{
				return JUDGE_LIDAR_DATA_LENGTH_AUTOCHOOSE;
			}
		}
			case 0x0301://0x0301机器人交互数据
		{
			if(len==(JUDGE_ROBOT_DATA_SENDOTHER_LENGTH-9))
			{
				return JUDGE_ROBOT_DATA_SENDOTHER_LENGTH;
			}
		}
			case 0x0302:
		{
			if(len==(JUDGE_REMOTEW_DATA_LENGTH-9))
			{
				return JUDGE_REMOTEW_DATA_LENGTH;
			}
		}
			case 0x0303://0x0303选手端小地图交互数据
		{
			if(len==(JUDGE_MAP_DATA_LENGTH-9))
			{
				return JUDGE_MAP_DATA_LENGTH;
			}
		}
			case 0x0304://0x0304键鼠遥控数据
		{
			if(len==(JUDGE_REMOTE_DATA_LENGTH-9))
			{
				return JUDGE_REMOTE_DATA_LENGTH;
			}
		}				
			case 0x0305://0x0305	选手端小地图接收雷达数据
		{
			if(len==(JUDGE_LIDARMAP_DATA_LENGTH-9))
			{
				return JUDGE_LIDARMAP_DATA_LENGTH;
			}
		}
		default:
			break;
	}
	return -1;
}

void RM_Judge_DataDequeue(u8* buffer, struct ArrayList * array, int offset, int size)
{
	int j = 0;
	for (int i = offset; i < offset + size; i++)	//拷贝数据
	{
		getValue(array,i ,buffer+j);
		j++;
	}
	deleteRangeValue(array, offset, offset+size);	//移除拷贝后的数据
}

void RM_Judge_DataEnqueue(unsigned char* buffer, struct ArrayList * array, int len)
{
	for (int i = 0; i < len; i++)
	{
		appendValue(array, buffer[i]);
	}
}
void Task_JudgeDataSend(void *Parameters)
{
	static u8 t;
	portTickType CurrentControlTick = 0;//当前系统时间	
	
	while(1)
	{			
//		MiniPC_SendLidar.aim_x = (int16_t)(MiniPC_Data_Recv.x*1000);
//		MiniPC_SendLidar.aim_y = (int16_t)(MiniPC_Data_Recv.y*1000);
//		MiniPC_SendLidar.aim_z = (int16_t)(MiniPC_Data_Recv.z*1000);
//		if( MiniPC_Data_Recv.r1 > MiniPC_Data_Recv.r2)
//		MiniPC_SendLidar.radius = (int16_t)(MiniPC_Data_Recv.r1*1000);
//		else if( MiniPC_Data_Recv.r1 < MiniPC_Data_Recv.r2)
//		MiniPC_SendLidar.radius = (int16_t)(MiniPC_Data_Recv.r2*1000);
//		else
//		MiniPC_SendLidar.radius =	MiniPC_SendLidar.radius;
//		Send_Data_Lidar[0] = 0x7b;
//		Send_Data_Lidar[1] = (u8)(MiniPC_SendLidar.aim_x>>8);
//		Send_Data_Lidar[2] = (u8)(MiniPC_SendLidar.aim_x);
//		Send_Data_Lidar[3] = (u8)(MiniPC_SendLidar.aim_y>>8);
//		Send_Data_Lidar[4] = (u8)(MiniPC_SendLidar.aim_y);
//		Send_Data_Lidar[5] = (u8)(MiniPC_SendLidar.aim_z>>8);
//		Send_Data_Lidar[6] = (u8)(MiniPC_SendLidar.aim_z);
//		Send_Data_Lidar[7] = (u8)(MiniPC_SendLidar.radius>>8);
//		Send_Data_Lidar[8] = (u8)(MiniPC_SendLidar.radius);
//		Send_Data_Lidar[9] = 0x7d;
		Send_Data_Lidar[0]=1;
		Send_Data_Lidar[1]=1;
		Send_Data_Lidar[2]=1;

		for(t = 0;t<2;t++)
		{
			USART_SendData(USART3,Send_Data_Lidar[t]);// use the usart to send the pc-data
			while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
		}
		vTaskDelayUntil(&CurrentControlTick, 2/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
}
