#include "judge.h"

uint8_t P_ucJudgeDataBuffer[JUDGE_BUFFER_LENGTH];  					//Judge���ݻ�������
struct ArrayList P_stJudgeDataArrayListBuff;//����ϵͳ���ڽ������ݻ��� //���ڽ��ճ�������������
u8 Send_Data_Lidar[3];
fn_P_stgamestatus P_stgamestatus;

fn_game_robot_pos_t fn_game_robot_pos;
//SemaphoreHandle_t JudgeDataDecode_Binary;
u16 x_c;
///*************************************************************************
//*  �������ƣ�Task_JudgeDataDecode
//*  ����˵����Judge����ϵͳ������������
//*  ����˵����void *Parameters
//*  �������أ���
//*  ��    ע��
//*************************************************************************/
//void Task_JudgeDataDecode(void *Parameters)
//{
//    BaseType_t stError=pdFALSE;
//	while(1)
//	{
//		if(JudgeDataDecode_Binary!=NULL)
//		{
//			stError=xSemaphoreTake(JudgeDataDecode_Binary,portMAX_DELAY);	//��ȡ�ź���
//			if(stError==pdTRUE)												//��ȡ�ź����ɹ�
//			{
//				RM_Judge_DataDecodeByBuff(P_ucJudgeDataBuffer);	//�������ݽ������������ݷ�ʽ��
//			}
//		}
//		else if(stError==pdFALSE)
//		{
//			vTaskDelay(10);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
//		}
//	}
//}

void RM_Judge_DataDecodeByBuff(uint8_t *pDecodeData)
{
	u8 nTempData[150] = { 0 };
	
	while(RM_Judge_FindFrame(&P_stJudgeDataArrayListBuff))	//������������֡
	{
		int nDataLenth=RM_Judge_DataLength(&P_stJudgeDataArrayListBuff);  //��ȡ����֡���ݳ���
		RM_Judge_DataDequeue(nTempData,&P_stJudgeDataArrayListBuff,0,nDataLenth);
		x_c=(uint16_t)(nTempData[6]<<8|nTempData[5]);

		switch(x_c)//
		{
			case 0x0001:
			{
				memcpy(&P_stgamestatus.game_status,nTempData,JUDGE_GAME_STATE_DATA_LENGTH);    //��������״̬����
			};break;
			case 0x0002:
			{
				memcpy(&P_stgamestatus.game_result,nTempData,JUDGE_GAME_RESULT_LENGTH);    //���������������**
			};break;
			case 0x0003:
			{
				memcpy(&P_stgamestatus.game_robot_HP,nTempData,JUDGE_GAME_ROBOT_HP_LENGTH);    //����ʵʱ������Ѫ������
			}break;
			case 0x0005:
			{
				memcpy(&P_stgamestatus.ICRA_buff_debuff_zone_status,nTempData,JUDGE_ICRA_BUFF_DEBUFF_ZONE_STATUS);    //����ICRA����**
			}break;
			case 0x0101:
			{
				memcpy(&P_stgamestatus.event_data,nTempData,JUDGE_EVENT_DATA_LENGTH);    //���������¼�����
			}break;
			case 0x0102:
			{
				memcpy(&P_stgamestatus.supply_projectile_action,nTempData,JUDGE_SUPPLY_ACTION_LENGTH);    //���������¼�����**
			}break;

			case 0x0104:
			{
				memcpy(&P_stgamestatus.referee_warning,nTempData,JUDGE_REFEREE_WARNING_LENGTH);    //���������¼�����**
			}break;
			case 0x0105:
			{
				memcpy(&P_stgamestatus.dart_remaining_time,nTempData,JUDGE_DART_REMAINING_TIME_LENGTH);    //���������¼�����
			}break;
			case 0x0201:
			{
				memcpy(&P_stgamestatus.game_robot_status,nTempData,JUDGE_ROBOT_STAUS_LENGTH);    //���������¼�����
			}break;
			case 0x0202:
			{
				memcpy(&P_stgamestatus.power_heat_data,nTempData,JUDGE_POWER_DATA_LENGTH);    //���������¼�����
			}break;
			case 0x0203:
			{
				memcpy(&P_stgamestatus.game_robot_pos,nTempData,JUDGE_ROBOT_POS_LENGTH);    //���������¼�����
			}break;
			case 0x0204:
			{
				memcpy(&P_stgamestatus.buff,nTempData,JUDGE_ROBOT_BUFF_LENGTH);    //���������¼�����
			}break;
			case 0x0205:
			{
				memcpy(&P_stgamestatus.aerial_robot_energy,nTempData,JUDGE_AERIAL_ROBOT_ENERGY_LENGTH);    //���������¼�����**
			}break;
			case 0x0206:
			{
				memcpy(&P_stgamestatus.robot_hurt,nTempData,JUDGE_ROBOT_HURT_LENGTH);    //���������¼�����**
			}break;
			case 0x0207:
			{
				memcpy(&P_stgamestatus.shoot_data,nTempData,JUDGE_SHOOT_DATA_LENGTH);    //���������¼�����**
			}break;
			case 0x0208:
			{
				memcpy(&P_stgamestatus.bullet_remaining,nTempData,JUDGE_BULLET_REMAINING_LENGTH);    //���������¼�����
			}break;
			case 0x0209:
			{
				memcpy(&P_stgamestatus.rfid_status,nTempData,JUDGE_RFID_STATUS_LENGTH);    //���������¼�����
			}break;
			case 0x020A:
			{
				memcpy(&P_stgamestatus.dart_client_cmd,nTempData,JUDGE_DART_CMD_LENGTH);    //���������¼�����**
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
	if (RM_ArrayList_GetArrayLength(arrlist) == 0)	//����Ϊ���򷵻�
	{
		return false;
	}
	HeadIndex = findValue(arrlist, 0xA5);	//����֡ͷ
	if (HeadIndex == -1)	//û�ҵ�֡ͷ��ɾ�����л�������������
	{
		deleteAllValue(arrlist);	
		return false;
	}
	else if (HeadIndex != 0)
	{
		if (HeadIndex > 1) //�Ƴ�֡ͷǰ����������
		{
			deleteRangeValue(arrlist, 0, HeadIndex-1);	
		}
	}
	if ((arrlist->total) < 5)	//֡ͷ�������ݲ�����������
	{
		return false;
	}
    length = RM_Judge_DataLength(arrlist);	//��ȡ����ϵͳ���ݳ��� 
	if(length == -1)
	{
		deleteAllValue(arrlist);
		return false;
	}
	if(!RM_Judge_CRC8Check((unsigned char *)(arrlist->qarr),5))	//֡ͷ����У��
	{
		deleteAllValue(arrlist);
		return false;
	}
	if ((arrlist->total) < length)	//���ݲ����������ܳ����˰����������б����ݲ���գ�
	{
		return false;
	}
	if(!RM_Judge_CRC16Check((unsigned char *)(arrlist->qarr),length))	//ȫ֡У��  �����������Ϊ���ֶ�֡ճ����������һ֡���ݲ����������޳�
	{
		int lastHeadIndex=HeadIndex;
		HeadIndex=findValue(arrlist+lastHeadIndex,0xA5); //������һ��֡ͷ
		if (HeadIndex == -1)	//û�ҵ�֡ͷ��ɾ�����л�������������
		{
			deleteAllValue(arrlist);	
			return false;
		}
		else if (HeadIndex != 0)
		{
			if (HeadIndex > lastHeadIndex) //�Ƴ���һ��֡ͷǰ����������
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
	cmd=(uint16_t)(arrlist->qarr[6] << 8 | arrlist->qarr[5]);	//��ȡ����
	len = (uint16_t)(arrlist->qarr[2] << 8 | arrlist->qarr[1]);	//��ȡ����
    switch (cmd) //�����ֽ�Ϊ���  
	{
		case 0x0001: //����������״̬
		{
			if(len==(JUDGE_GAME_STATE_DATA_LENGTH-9))
			{
				return JUDGE_GAME_STATE_DATA_LENGTH;
			}
		}
		case 0x0002: //�˺�����
		{
			if(len==(JUDGE_GAME_RESULT_LENGTH-9))
			{
				return JUDGE_GAME_RESULT_LENGTH;
			}
		}
		case 0x0003: //ʵʱ�������
		{
			if(len==(JUDGE_GAME_ROBOT_HP_LENGTH-9))
			{
				return JUDGE_GAME_ROBOT_HP_LENGTH;
			}
		}
		case 0x0004: //ʵʱ���ʺ���������
		{
			if(len==(JUDGE_DART_STATUS_LENGTH-9))
			{
				return JUDGE_DART_STATUS_LENGTH;
			}
		}
		case 0x0005: //ʵʱ���ؽ�������
		{
			if(len==(JUDGE_ICRA_BUFF_DEBUFF_ZONE_STATUS-9))
			{
				return JUDGE_ICRA_BUFF_DEBUFF_ZONE_STATUS;
			}
		}
		case 0x0101: //����������� ��������ʱ����һ��
		{
			if(len==(JUDGE_EVENT_DATA_LENGTH-9))
			{
				return JUDGE_EVENT_DATA_LENGTH;
			}
		}
		case 0x0102: //��ȡ��Buff����
		{
			if(len==(JUDGE_SUPPLY_ACTION_LENGTH-9))
			{
				return JUDGE_SUPPLY_ACTION_LENGTH;
			}
		}
		case 0x0104: //������λ�ú�ǹ�ڳ������� 
		{
			if(len==(JUDGE_REFEREE_WARNING_LENGTH-9))
			{
				return JUDGE_REFEREE_WARNING_LENGTH;
			}
		}
		case 0x0105: //0x0105���ڷ���ڵ���ʱ
		{
			if(len==(JUDGE_DART_REMAINING_TIME_LENGTH-9))
			{
				return JUDGE_DART_REMAINING_TIME_LENGTH;
			}
		}
		case 0x0201: //0x0201����������״̬
		{
			if(len==(JUDGE_ROBOT_STAUS_LENGTH-9))
			{
				return JUDGE_ROBOT_STAUS_LENGTH;
			}
		}
		case 0x0202: //0x0202ʵʱ������������
		{
			if(len==(JUDGE_POWER_DATA_LENGTH-9))
			{
				return JUDGE_POWER_DATA_LENGTH;
			}
		}
		case 0x0203: //0x0203������λ������
		{
			if(len==(JUDGE_ROBOT_POS_LENGTH-9))
			{
				return JUDGE_ROBOT_POS_LENGTH;
			}
		}
		case 0x0204://0x0204����������
		{
			if(len==(JUDGE_ROBOT_BUFF_LENGTH-9))
			{
				return JUDGE_ROBOT_BUFF_LENGTH;
			}
		}
		case 0x0205: //0x0205���л���������״̬
		{
			if(len==(JUDGE_AERIAL_ROBOT_ENERGY_LENGTH-9))
			{
				return JUDGE_AERIAL_ROBOT_ENERGY_LENGTH;
			}
		}
		case 0x0206: //0x0206�˺�״̬
		{
			if(len==(JUDGE_ROBOT_HURT_LENGTH-9))
			{
				return JUDGE_ROBOT_HURT_LENGTH;
			}
		}
		case 0x0207://0x0207ʵʱ�����Ϣ
		{
			if(len==(JUDGE_SHOOT_DATA_LENGTH-9))
			{
				return JUDGE_SHOOT_DATA_LENGTH;
			}
		}
		case 0x0208://0x0208�ӵ�ʣ�෢����
		{
			if(len==(JUDGE_BULLET_REMAINING_LENGTH-9))
			{
				return JUDGE_BULLET_REMAINING_LENGTH;
			}
		}
		case 0x0209: //0x0209������RFID״̬
		{
			if(len==(JUDGE_RFID_STATUS_LENGTH-9))
			{
				return JUDGE_RFID_STATUS_LENGTH;
			}
		}
		case 0x020A: //0x020A���ڻ����˿ͻ�������
		{
			if(len==(JUDGE_DART_CMD_LENGTH-9))
			{
				return JUDGE_DART_CMD_LENGTH;
			}
		}
		case 0x020B://0x020B������λ������
		{
			if(len==(JUDGE_LOCATION_LENGTH-9))
			{
				return JUDGE_LOCATION_LENGTH;
			}
		}
		case 0x020C://0x020C�з������˱��״��ǽ���
		{
			if(len==(JUDGE_MARK_LENGTH-9))
			{
				return JUDGE_MARK_LENGTH;
			}
		}
		case 0x020D://�ڱ�����������Ϣͬ�� 0x020D
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
			case 0x0301://0x0301�����˽�������
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
			case 0x0303://0x0303ѡ�ֶ�С��ͼ��������
		{
			if(len==(JUDGE_MAP_DATA_LENGTH-9))
			{
				return JUDGE_MAP_DATA_LENGTH;
			}
		}
			case 0x0304://0x0304����ң������
		{
			if(len==(JUDGE_REMOTE_DATA_LENGTH-9))
			{
				return JUDGE_REMOTE_DATA_LENGTH;
			}
		}				
			case 0x0305://0x0305	ѡ�ֶ�С��ͼ�����״�����
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
	for (int i = offset; i < offset + size; i++)	//��������
	{
		getValue(array,i ,buffer+j);
		j++;
	}
	deleteRangeValue(array, offset, offset+size);	//�Ƴ������������
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
	portTickType CurrentControlTick = 0;//��ǰϵͳʱ��	
	
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
		vTaskDelayUntil(&CurrentControlTick, 2/ portTICK_RATE_MS); //����������������  1ms����һ��
	}
}
