#ifndef __JUDGE_H__
#define __JUDGE_H__

#include "main.h"

#define JUDGE_BUFFER_LENGTH 512 					//Judge���ݻ������鳤��

#define RM_Judge_CRC8Check      Verify_CRC8_Check_Sum     //CRC8У�麯��
#define RM_Judge_CRC16Check     Verify_CRC16_Check_Sum  //CRC16У�麯��
#define RM_Judge_CRC8Append     Append_CRC8_Check_Sum    //CRC8У���븽�Ӻ�������
#define RM_Judge_CRC16Append    Append_CRC16_Check_Sum   //CRC16У���븽�Ӻ�������

#define JUDGE_GAME_STATE_DATA_LENGTH         20 //����״̬��Ϣ
#define JUDGE_GAME_RESULT_LENGTH             10//�����������
#define JUDGE_GAME_ROBOT_HP_LENGTH           41//����������Ѫ������
#define JUDGE_DART_STATUS_LENGTH             12//���ڷ���״̬
#define JUDGE_ICRA_BUFF_DEBUFF_ZONE_STATUS   22//�˹�������ս��״̬�ӳ���ͷ�״̬��1Hz ���ڷ���
#define JUDGE_EVENT_DATA_LENGTH              13//����������Ϣ//�����¼����ݣ��¼��ı����
#define JUDGE_SUPPLY_ACTION_LENGTH           13//����վ������ʶ���ݣ������ı����**
//#define JUDGE_REQUEST_SUPPLY_LENGTH          11//���󲹸�վ�������ݣ��ɲ����ӷ��ͣ����� 10Hz����RM �Կ�����δ���ţ�
#define JUDGE_REFEREE_WARNING_LENGTH         12//����ϵͳ��������
#define JUDGE_DART_REMAINING_TIME_LENGTH     12//���ڷ���ڵ���ʱ
#define JUDGE_ROBOT_STAUS_LENGTH             22//������״̬����
#define JUDGE_POWER_DATA_LENGTH              25//ʵʱ������������**
#define JUDGE_ROBOT_POS_LENGTH               25//������λ������
#define JUDGE_ROBOT_BUFF_LENGTH              15//��������������
#define JUDGE_AERIAL_ROBOT_ENERGY_LENGTH     11//���л���������״̬����**
#define JUDGE_ROBOT_HURT_LENGTH              10//�˺�״̬����
#define JUDGE_SHOOT_DATA_LENGTH              16//ʵʱ�������**
#define JUDGE_BULLET_REMAINING_LENGTH        15//�ӵ�ʣ�෢����
#define JUDGE_RFID_STATUS_LENGTH             13//������RFID״̬
#define JUDGE_DART_CMD_LENGTH                15//���ڻ����˿ͻ���ָ��
#define JUDGE_LOCATION_LENGTH				 49//������λ������
#define JUDGE_MARK_LENGTH					 15//�״��ǽ���
#define JUDGE_SENTRY_DATA_LENGTH_AUTOCHOOSE					 13//�ڱ�����������Ϣͬ��
#define JUDGE_LIDAR_DATA_LENGTH_AUTOCHOOSE			 10//�״�����������Ϣͬ��
#define JUDGE_ROBOT_DATA_SENDOTHER_LENGTH			 136//�����˽�������
#define JUDGE_REMOTEW_DATA_LENGTH			 39//�Զ��������������˽�������
#define JUDGE_MAP_DATA_LENGTH			 24//ѡ�ֶ�С��ͼ��������
#define JUDGE_REMOTE_DATA_LENGTH			 21	//����ң������
#define JUDGE_LIDARMAP_DATA_LENGTH			 19 //ѡ�ֶ�С��ͼ�����״�����
#define JUDGE_REMOTEW_SEND_DATA_LENGTH			 17 //�Զ����������ѡ�ֶ˽�������
#define JUDGE_SENTRY_SEND_DATA_LENGTH			 112 //�Զ����������ѡ�ֶ˽�������
#define JUDGE_MAPRECEIVE_DATA_LENGTH			 43 //ѡ�ֶ�С��ͼ���ջ���������

//����ϵͳ���ݽṹ
typedef __packed struct
{
	uint8_t SOF;          //������ʼ�ֽڣ��̶�Ϊ0xA5          
	uint16_t DataLength;  //���ݳ���
	uint8_t Seq;          //�����
	uint8_t CRC8;         //֡ͷCRCУ��
}tFrameHeader;//֡ͷ

typedef enum 
{
  GAME_STATE_DATA=0X0001,               //0X0001 ����״̬����
	GAME_RESULT_DATA,                     //0x0002 �����������
	ROBOT_HP_DATA,                        //0x0003   
	AOUT_GAME_BUFF_DEBUFF_DATA=0X0005,    //0x0005   
	SITE_EVENT_DATA=0X0101,               //0x0101   
	SITE_GET_DATA,                        //0x0102   
	JUDGE_WARNING_DATA=0X0104,            //0x0104   
	DARTS_SHOOT_DATA,                     //0x0105   
	ROBOT_STATE_DATA=0X0201,              //0x0201   
	REALTIME_POWER_DATA,                  //0x0202   
	ROBOT_STIE_DATA,                      //0x0203      
	ROBOT_BUFF_DATA,                      //0x0204   
	SKY_ROBOT_POWER_DATA,                 //0x0205   
	SHOOT_HURT_DATA,                      //0x0206   
	SHOOT_DATA,                           //0x0207    
	BULLET_DATA,                          //0x0208  
	RFID_DATA,                            //0x0209  
	DARTS_CR_DATA,                        //0x020A     
	ROBOT_TO_ROBOT_DATA=0X0301,           //0X0301   
	ROBOT_TO_PC_DATA,                     //0X0302  
	PC_TO_PC_DATA,                        //0X0303    
	KEY_DATA,                             //0X0304     
	PC_RE_DATA,                           //0X0305    
}tCmdID;

//����״̬���ݣ�0x0001
typedef __packed struct
{
	uint8_t game_type : 4;
  uint8_t game_progress : 4;
  uint16_t stage_remain_time;
  uint64_t SyncTimeStamp;
} ext_game_status_t;

//����������ݣ�0x0002
typedef __packed struct
{
uint8_t winner;
} ext_game_result_t;

//������Ѫ�����ݣ�0x0003��
typedef __packed struct
{
	uint16_t red_1_robot_HP;
	uint16_t red_2_robot_HP; 
	uint16_t red_3_robot_HP; 
	uint16_t red_4_robot_HP; 
	uint16_t red_5_robot_HP; 
	uint16_t red_7_robot_HP; 
	uint16_t red_outpost_HP;
	uint16_t red_base_HP; 
	uint16_t blue_1_robot_HP;
	uint16_t blue_2_robot_HP;
	uint16_t blue_3_robot_HP;
	uint16_t blue_4_robot_HP;
	uint16_t blue_5_robot_HP;
	uint16_t blue_7_robot_HP;
	uint16_t blue_outpost_HP;
	uint16_t blue_base_HP;
}ext_game_robot_HP_t;

//�˹�������ս���ӳ���ͷ���״̬��0x0005��
typedef __packed struct
	{
	uint8_t F1_zone_status:1;
	uint8_t F1_zone_buff_debuff_status:3;
	uint8_t F2_zone_status:1;
	uint8_t F2_zone_buff_debuff_status:3;
	uint8_t F3_zone_status:1;
	uint8_t F3_zone_buff_debuff_status:3;
	uint8_t F4_zone_status:1;
	uint8_t F4_zone_buff_debuff_status:3;
	uint8_t F5_zone_status:1;
	uint8_t F5_zone_buff_debuff_status:3; 
	uint8_t F6_zone_status:1;
	uint8_t F6_zone_buff_debuff_status:3;
	uint16_t red1_bullet_left;
	uint16_t red2_bullet_left;
	uint16_t blue1_bullet_left;
	uint16_t blue2_bullet_left;
	uint8_t lurk_mode;
	uint8_t res;
	}ext_ICRA_buff_debuff_zone_status_t;
    
	//�����¼����ݣ�0x0101
typedef __packed struct
{
	uint32_t event_type;
} 	ext_event_data_t;

//����վ������ʶ��0x0102
typedef __packed struct
{
		uint8_t supply_projectile_id;
		uint8_t supply_robot_id; 
		uint8_t supply_projectile_step;
		uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;

//���о�����Ϣ��cmd_id (0x0104)��
typedef __packed struct
{
		uint8_t level;
		uint8_t offending_robot_id;
		uint8_t count;
} ext_referee_warning_t;

//���ڷ���ڵ���ʱ��cmd_id (0x0105)��
typedef __packed struct
{
		uint8_t dart_remaining_time;
		uint16_t dart_info;
} ext_dart_remaining_time_t;

//����������״̬��0x0201
typedef __packed struct
{
		uint8_t robot_id;
		uint8_t robot_level;
		uint16_t current_HP;
		uint16_t maximum_HP;
		uint16_t shooter_barrel_cooling_value;
		uint16_t shooter_barrel_heat_limit;
		uint16_t chassis_power_limit;
		uint8_t power_management_gimbal_output : 1;
		uint8_t power_management_chassis_output : 1;
		uint8_t power_management_shooter_output : 1;
}ext_game_robot_status_t;

//ʵʱ�����������ݣ�0x0202
typedef __packed struct
{
		uint16_t chassis_volt; 
		uint16_t chassis_current; 
		float chassis_power; 
		uint16_t chassis_power_buffer;
		uint16_t shooter_id1_17mm_cooling_heat;
		uint16_t shooter_id2_17mm_cooling_heat;
		uint16_t shooter_id1_42mm_cooling_heat;
} ext_power_heat_data_t;

//������λ�ã�0x0203��
typedef __packed struct
{
	float x;
	float y;
	float angle;
} ext_game_robot_pos_t;

//���������棺0x0204��
typedef __packed struct
{
	uint8_t recovery_buff;
	uint8_t cooling_buff;
	uint8_t defence_buff;
	uint8_t vulnerability_buff;
	uint16_t attack_buff;
}ext_buff_t;
//���л���������״̬��0x0205

typedef __packed struct
{
	uint8_t airforce_status;
	uint8_t time_remain;
} ext_aerial_robot_energy_t;

//�˺�״̬��0x0206
typedef __packed struct
{
	uint8_t armor_id : 4;
	uint8_t HP_deduction_reason : 4;
}ext_robot_hurt_t;

//ʵʱ�����Ϣ��0x0207
typedef __packed struct
{
	uint8_t bullet_type;
	uint8_t shooter_id;
	uint8_t bullet_freq;
	float bullet_speed;
} ext_shoot_data_t;

//�ӵ�ʣ�෢������0x0208
typedef __packed struct
{
	uint16_t bullet_remaining_num_17mm;
	uint16_t bullet_remaining_num_42mm;
	uint16_t coin_remaining_num;
}ext_bullet_remaining_t;

//������RFID״̬��0x0209
typedef __packed struct
{
	uint32_t rfid_status;
} ext_rfid_status_t;

//���ڻ����˿ͻ���ָ�����ݣ�0x020A��
typedef __packed struct
{
	uint8_t dart_launch_opening_status;
	uint8_t dart_attack_target;
	uint16_t target_change_time;
	uint16_t operate_launch_cmd_time;
} ext_dart_client_cmd_t;

//������λ�����ݣ�0x020B��
typedef __packed struct
{
	float hero_x;
	float hero_y;
	float engineer_x;
	float engineer_y;
	float standard_3_x;
	float standard_3_y;
	float standard_4_x;
	float standard_4_y;
	float standard_5_x;
	float standard_5_y;
} ext_location_t;

//�״��ǵ��˽������ݣ�0x020C��
typedef __packed struct
{
	uint8_t mark_hero_progress;
	uint8_t mark_engineer_progress;
	uint8_t mark_standard_3_progress;
	uint8_t mark_standard_4_progress;
	uint8_t mark_standard_5_progress;
	uint8_t mark_sentry_progress;
}ext_mark_data_t;

//�ڱ�����������Ϣͬ�� 0x020D 
typedef __packed struct
{
uint32_t sentry_info;
} sentry_info_t;
//0x020E�״�����������Ϣͬ��
typedef __packed struct
{
uint8_t radar_info;
} radar_info_t;
//0x0303ѡ�ֶ�С��ͼ��������
typedef __packed struct
{
	float target_position_x;
	float target_position_y;
	uint8_t cmd_keyboard;
	uint8_t target_robot_id;
	uint8_t cmd_source;
}map_command_t;
//0x0301�����˽�������
typedef __packed struct
{
	uint16_t data_cmd_id;
	uint16_t sender_id;
	uint16_t receiver_id;
	uint8_t user_data[112];
}robot_interaction_data_t;
//0x0305	ѡ�ֶ�С��ͼ�����״�����
typedef __packed struct
{
	uint16_t target_robot_id;
	float target_position_x;
	float target_position_y;
}map_robot_data_t;
//0x0307ѡ�ֶ�С��ͼ�����ڱ�����
typedef __packed struct
{
	uint8_t intention;
	uint16_t start_position_x;
	uint16_t start_position_y;
	int8_t delta_x[49];
	int8_t delta_y[49];
	uint16_t sender_id;
}map_data_t;
//0x0304����ң������
typedef __packed struct
{
	int16_t mouse_x;
	int16_t mouse_y;
	int16_t mouse_z;
	int8_t left_button_down;
	int8_t ight_button_down;
	uint16_t keyboard_value;
	uint16_t reserved;
}remote_control_t;
//0x0308ѡ�ֶ�С��ͼ���ջ���������
typedef __packed struct
{
	uint16_t sender_id;
	uint16_t receiver_id;
	uint8_t user_data[30];
} custom_info_t;
//0x0001����״̬����
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_game_status_t game_status;
}fn_game_status_t;

//0x0002�����������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_game_result_t game_result;
}fn_game_result_t;

//0x0003������Ѫ������	
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_game_robot_HP_t game_robot_HP;
}fn_game_robot_HP_t;

//0x0005
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_ICRA_buff_debuff_zone_status_t ICRA_buff_debuff_zone_status;
}fn_ICRA_buff_debuff_zone_status_t;

//0x0101�����¼�����
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_event_data_t event_data;
}fn_event_data_t;

//0x0102����վ������ʶ����
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_supply_projectile_action_t supply_projectile_action;
}fn_supply_projectile_action_t;

//0x0104���о�������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_referee_warning_t referee_warning;
}fn_referee_warning_t;

//0x0105���ڷ����������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_dart_remaining_time_t dart_remaining_time;
}fn_dart_remaining_time_t;

//0x0201������������ϵ����
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_game_robot_status_t game_robot_status;
}fn_game_robot_status_t;

//0x0202ʵʱ���̹��ʺ�ǹ����������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_power_heat_data_t power_heat_data;
}fn_power_heat_data_t;

//0x0203������λ������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_game_robot_pos_t game_robot_pos;
}fn_game_robot_pos_t;

//0x0204��������������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_buff_t buff;
}fn_buff_t;

//0x0205����֧Ԯʱ������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_aerial_robot_energy_t aerial_robot_energy;
}fn_aerial_robot_energy_t;

//0x0206�˺�״̬����
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_robot_hurt_t robot_hurt;
}fn_robot_hurt_t;

//0x0207ʵʱ�������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_shoot_data_t shoot_data;
}fn_shoot_data_t;

//0x0208��������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_bullet_remaining_t bullet_remaining;
}fn_bullet_remaining_t;

//0x0209������ RFID ģ��״̬
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_rfid_status_t rfid_status;
}fn_rfid_status_t;

//0x020A����ѡ�ֶ�ָ������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_dart_client_cmd_t dart_client_cmd;
}fn_dart_client_cmd_t;

//0x020B���������λ������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_location_t location;
}fn_location_t;

//0x020C�״��ǽ�������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_mark_data_t mark_data;
}fn_mark_data_t;
//�ڱ�����������Ϣͬ�� 0x020D 
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	sentry_info_t Sentry_Data;
}fn_Sentry_Data_t;
//0x0303ѡ�ֶ�С��ͼ��������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	map_command_t map_command;
}fn_map_command_t;
//0x0301�����˽�������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	robot_interaction_data_t robot_interaction;
}fn_robot_interaction_data_t;
//0x0305	ѡ�ֶ�С��ͼ�����״�����
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	map_robot_data_t map_robot;
}fn_map_robot_data_t;
//0x0307ѡ�ֶ�С��ͼ�����ڱ�����
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	map_data_t map_data;
}fn_map_data_t;
//0x0304����ң������
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	remote_control_t remote_control;
}fn_remote_control_t;
//ȫ���ݴ洢����
typedef __packed struct
{
	fn_game_status_t game_status;//0x0001����״̬����
	fn_game_result_t game_result;//0x0002�����������
	fn_game_robot_HP_t game_robot_HP;//0x0003������Ѫ������
	fn_ICRA_buff_debuff_zone_status_t ICRA_buff_debuff_zone_status;//0x0005�˹�������ս��
	fn_event_data_t event_data;//0x0101�����¼�����
	fn_supply_projectile_action_t supply_projectile_action;//0x0102����վ������־
	fn_referee_warning_t referee_warning;//0x0104���о�����Ϣ
	fn_dart_remaining_time_t dart_remaining_time;//0x0105���ڷ���ڵ���ʱ
	fn_game_robot_status_t game_robot_status;//0x0201����������״̬
	fn_power_heat_data_t power_heat_data;//0x0202ʵʱ������������
	fn_game_robot_pos_t game_robot_pos;//0x0203������λ������
	fn_buff_t buff;//0x0204����������
	fn_aerial_robot_energy_t aerial_robot_energy;//0x0205���л���������״̬
	fn_robot_hurt_t robot_hurt;//0x0206�˺�״̬
	fn_shoot_data_t shoot_data;//0x0207ʵʱ�����Ϣ
	fn_bullet_remaining_t bullet_remaining;//0x0208�ӵ�ʣ�෢����
	fn_rfid_status_t rfid_status;//0x0209������RFID״̬
	fn_dart_client_cmd_t dart_client_cmd;//0x020A���ڻ����˿ͻ�������
	fn_location_t location;//0x020B������λ������
	fn_mark_data_t mark_data;//0x020C�з������˱��״��ǽ���
	fn_Sentry_Data_t Sentry_Data;//�ڱ�����������Ϣͬ�� 0x020D 
	fn_map_robot_data_t map_robot;//0x0305	ѡ�ֶ�С��ͼ�����״�����
	fn_map_data_t map_data;//0x0307ѡ�ֶ�С��ͼ�����ڱ�����
	fn_remote_control_t remote_control;//0x0304����ң������
	fn_robot_interaction_data_t robot_interaction;//0x0301�����˽�������
	fn_map_command_t map_command;//0x0303ѡ�ֶ�С��ͼ��������
}fn_P_stgamestatus;

extern fn_P_stgamestatus P_stgamestatus;
extern uint8_t P_ucJudgeDataBuffer[JUDGE_BUFFER_LENGTH];  
//extern SemaphoreHandle_t JudgeDataDecode_Binary;
extern struct ArrayList P_stJudgeDataArrayListBuff;//����ϵͳ���ڽ������ݻ��� //���ڽ��ճ�������������
void Task_JudgeDataSend(void *Parameters);
//void Task_JudgeDataDecode(void *Parameters);
void RM_Judge_DataDecodeByBuff(uint8_t *pDecodeData);
bool RM_Judge_FindFrame(struct ArrayList * arrlist);
int RM_Judge_DataLength(struct ArrayList * arrlist);
void RM_Judge_DataDequeue(u8* buffer, struct ArrayList * array, int offset, int size);
void RM_Judge_DataEnqueue(unsigned char* buffer, struct ArrayList * array, int len);


#endif
