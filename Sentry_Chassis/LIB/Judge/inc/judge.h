#ifndef __JUDGE_H__
#define __JUDGE_H__

#include "main.h"

#define JUDGE_BUFFER_LENGTH 512 					//Judge数据缓存数组长度

#define RM_Judge_CRC8Check      Verify_CRC8_Check_Sum     //CRC8校验函数
#define RM_Judge_CRC16Check     Verify_CRC16_Check_Sum  //CRC16校验函数
#define RM_Judge_CRC8Append     Append_CRC8_Check_Sum    //CRC8校验码附加函数函数
#define RM_Judge_CRC16Append    Append_CRC16_Check_Sum   //CRC16校验码附加函数函数

#define JUDGE_GAME_STATE_DATA_LENGTH         20 //比赛状态信息
#define JUDGE_GAME_RESULT_LENGTH             10//比赛结果数据
#define JUDGE_GAME_ROBOT_HP_LENGTH           41//比赛机器人血量数据
#define JUDGE_DART_STATUS_LENGTH             12//飞镖发射状态
#define JUDGE_ICRA_BUFF_DEBUFF_ZONE_STATUS   22//人工智能挑战赛状态加成与惩罚状态，1Hz 周期发送
#define JUDGE_EVENT_DATA_LENGTH              13//比赛场地信息//场地事件数据，事件改编后发送
#define JUDGE_SUPPLY_ACTION_LENGTH           13//补给站动作标识数据，动作改变后发送**
//#define JUDGE_REQUEST_SUPPLY_LENGTH          11//请求补给站补弹数据，由参赛队发送，上限 10Hz。（RM 对抗赛尚未开放）
#define JUDGE_REFEREE_WARNING_LENGTH         12//裁判系统警告数据
#define JUDGE_DART_REMAINING_TIME_LENGTH     12//飞镖发射口倒计时
#define JUDGE_ROBOT_STAUS_LENGTH             22//机器人状态数据
#define JUDGE_POWER_DATA_LENGTH              25//实时功率热量数据**
#define JUDGE_ROBOT_POS_LENGTH               25//机器人位置数据
#define JUDGE_ROBOT_BUFF_LENGTH              15//机器人增益数据
#define JUDGE_AERIAL_ROBOT_ENERGY_LENGTH     11//空中机器人能量状态数据**
#define JUDGE_ROBOT_HURT_LENGTH              10//伤害状态数据
#define JUDGE_SHOOT_DATA_LENGTH              16//实时射击数据**
#define JUDGE_BULLET_REMAINING_LENGTH        15//子弹剩余发射数
#define JUDGE_RFID_STATUS_LENGTH             13//机器人RFID状态
#define JUDGE_DART_CMD_LENGTH                15//飞镖机器人客户端指令
#define JUDGE_LOCATION_LENGTH				 49//机器人位置数据
#define JUDGE_MARK_LENGTH					 15//雷达标记进度
#define JUDGE_SENTRY_DATA_LENGTH_AUTOCHOOSE					 13//哨兵自主决策信息同步
#define JUDGE_LIDAR_DATA_LENGTH_AUTOCHOOSE			 10//雷达自主决策信息同步
#define JUDGE_ROBOT_DATA_SENDOTHER_LENGTH			 136//机器人交互数据
#define JUDGE_REMOTEW_DATA_LENGTH			 39//自定义控制器与机器人交互数据
#define JUDGE_MAP_DATA_LENGTH			 24//选手端小地图交互数据
#define JUDGE_REMOTE_DATA_LENGTH			 21	//键鼠遥控数据
#define JUDGE_LIDARMAP_DATA_LENGTH			 19 //选手端小地图接收雷达数据
#define JUDGE_REMOTEW_SEND_DATA_LENGTH			 17 //自定义控制器与选手端交互数据
#define JUDGE_SENTRY_SEND_DATA_LENGTH			 112 //自定义控制器与选手端交互数据
#define JUDGE_MAPRECEIVE_DATA_LENGTH			 43 //选手端小地图接收机器人数据

//裁判系统数据结构
typedef __packed struct
{
	uint8_t SOF;          //数据起始字节，固定为0xA5          
	uint16_t DataLength;  //数据长度
	uint8_t Seq;          //包序号
	uint8_t CRC8;         //帧头CRC校验
}tFrameHeader;//帧头

typedef enum 
{
  GAME_STATE_DATA=0X0001,               //0X0001 比赛状态数据
	GAME_RESULT_DATA,                     //0x0002 比赛结果数据
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

//比赛状态数据：0x0001
typedef __packed struct
{
	uint8_t game_type : 4;
  uint8_t game_progress : 4;
  uint16_t stage_remain_time;
  uint64_t SyncTimeStamp;
} ext_game_status_t;

//比赛结果数据：0x0002
typedef __packed struct
{
uint8_t winner;
} ext_game_result_t;

//机器人血量数据：0x0003。
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

//人工智能挑战赛加成与惩罚区状态：0x0005。
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
    
	//场地事件数据：0x0101
typedef __packed struct
{
	uint32_t event_type;
} 	ext_event_data_t;

//补给站动作标识：0x0102
typedef __packed struct
{
		uint8_t supply_projectile_id;
		uint8_t supply_robot_id; 
		uint8_t supply_projectile_step;
		uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;

//裁判警告信息：cmd_id (0x0104)。
typedef __packed struct
{
		uint8_t level;
		uint8_t offending_robot_id;
		uint8_t count;
} ext_referee_warning_t;

//飞镖发射口倒计时：cmd_id (0x0105)。
typedef __packed struct
{
		uint8_t dart_remaining_time;
		uint16_t dart_info;
} ext_dart_remaining_time_t;

//比赛机器人状态：0x0201
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

//实时功率热量数据：0x0202
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

//机器人位置：0x0203。
typedef __packed struct
{
	float x;
	float y;
	float angle;
} ext_game_robot_pos_t;

//机器人增益：0x0204。
typedef __packed struct
{
	uint8_t recovery_buff;
	uint8_t cooling_buff;
	uint8_t defence_buff;
	uint8_t vulnerability_buff;
	uint16_t attack_buff;
}ext_buff_t;
//空中机器人能量状态：0x0205

typedef __packed struct
{
	uint8_t airforce_status;
	uint8_t time_remain;
} ext_aerial_robot_energy_t;

//伤害状态：0x0206
typedef __packed struct
{
	uint8_t armor_id : 4;
	uint8_t HP_deduction_reason : 4;
}ext_robot_hurt_t;

//实时射击信息：0x0207
typedef __packed struct
{
	uint8_t bullet_type;
	uint8_t shooter_id;
	uint8_t bullet_freq;
	float bullet_speed;
} ext_shoot_data_t;

//子弹剩余发射数：0x0208
typedef __packed struct
{
	uint16_t bullet_remaining_num_17mm;
	uint16_t bullet_remaining_num_42mm;
	uint16_t coin_remaining_num;
}ext_bullet_remaining_t;

//机器人RFID状态：0x0209
typedef __packed struct
{
	uint32_t rfid_status;
} ext_rfid_status_t;

//飞镖机器人客户端指令数据：0x020A。
typedef __packed struct
{
	uint8_t dart_launch_opening_status;
	uint8_t dart_attack_target;
	uint16_t target_change_time;
	uint16_t operate_launch_cmd_time;
} ext_dart_client_cmd_t;

//机器人位置数据：0x020B。
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

//雷达标记敌人进度数据：0x020C。
typedef __packed struct
{
	uint8_t mark_hero_progress;
	uint8_t mark_engineer_progress;
	uint8_t mark_standard_3_progress;
	uint8_t mark_standard_4_progress;
	uint8_t mark_standard_5_progress;
	uint8_t mark_sentry_progress;
}ext_mark_data_t;

//哨兵自主决策信息同步 0x020D 
typedef __packed struct
{
uint32_t sentry_info;
} sentry_info_t;
//0x020E雷达自主决策信息同步
typedef __packed struct
{
uint8_t radar_info;
} radar_info_t;
//0x0303选手端小地图交互数据
typedef __packed struct
{
	float target_position_x;
	float target_position_y;
	uint8_t cmd_keyboard;
	uint8_t target_robot_id;
	uint8_t cmd_source;
}map_command_t;
//0x0301机器人交互数据
typedef __packed struct
{
	uint16_t data_cmd_id;
	uint16_t sender_id;
	uint16_t receiver_id;
	uint8_t user_data[112];
}robot_interaction_data_t;
//0x0305	选手端小地图接收雷达数据
typedef __packed struct
{
	uint16_t target_robot_id;
	float target_position_x;
	float target_position_y;
}map_robot_data_t;
//0x0307选手端小地图接收哨兵数据
typedef __packed struct
{
	uint8_t intention;
	uint16_t start_position_x;
	uint16_t start_position_y;
	int8_t delta_x[49];
	int8_t delta_y[49];
	uint16_t sender_id;
}map_data_t;
//0x0304键鼠遥控数据
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
//0x0308选手端小地图接收机器人数据
typedef __packed struct
{
	uint16_t sender_id;
	uint16_t receiver_id;
	uint8_t user_data[30];
} custom_info_t;
//0x0001比赛状态数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_game_status_t game_status;
}fn_game_status_t;

//0x0002比赛结果数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_game_result_t game_result;
}fn_game_result_t;

//0x0003机器人血量数据	
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

//0x0101场地事件数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_event_data_t event_data;
}fn_event_data_t;

//0x0102补给站动作标识数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_supply_projectile_action_t supply_projectile_action;
}fn_supply_projectile_action_t;

//0x0104裁判警告数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_referee_warning_t referee_warning;
}fn_referee_warning_t;

//0x0105飞镖发射相关数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_dart_remaining_time_t dart_remaining_time;
}fn_dart_remaining_time_t;

//0x0201机器人性能体系数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_game_robot_status_t game_robot_status;
}fn_game_robot_status_t;

//0x0202实时底盘功率和枪口热量数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_power_heat_data_t power_heat_data;
}fn_power_heat_data_t;

//0x0203机器人位置数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_game_robot_pos_t game_robot_pos;
}fn_game_robot_pos_t;

//0x0204机器人增益数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_buff_t buff;
}fn_buff_t;

//0x0205空中支援时间数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_aerial_robot_energy_t aerial_robot_energy;
}fn_aerial_robot_energy_t;

//0x0206伤害状态数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_robot_hurt_t robot_hurt;
}fn_robot_hurt_t;

//0x0207实时射击数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_shoot_data_t shoot_data;
}fn_shoot_data_t;

//0x0208允许发弹量
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_bullet_remaining_t bullet_remaining;
}fn_bullet_remaining_t;

//0x0209机器人 RFID 模块状态
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_rfid_status_t rfid_status;
}fn_rfid_status_t;

//0x020A飞镖选手端指令数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_dart_client_cmd_t dart_client_cmd;
}fn_dart_client_cmd_t;

//0x020B地面机器人位置数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_location_t location;
}fn_location_t;

//0x020C雷达标记进度数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	ext_mark_data_t mark_data;
}fn_mark_data_t;
//哨兵自主决策信息同步 0x020D 
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	sentry_info_t Sentry_Data;
}fn_Sentry_Data_t;
//0x0303选手端小地图交互数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	map_command_t map_command;
}fn_map_command_t;
//0x0301机器人交互数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	robot_interaction_data_t robot_interaction;
}fn_robot_interaction_data_t;
//0x0305	选手端小地图接收雷达数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	map_robot_data_t map_robot;
}fn_map_robot_data_t;
//0x0307选手端小地图接收哨兵数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	map_data_t map_data;
}fn_map_data_t;
//0x0304键鼠遥控数据
typedef __packed struct
{
	tFrameHeader FrameHeader;
	uint16_t cmd_id;
	remote_control_t remote_control;
}fn_remote_control_t;
//全数据存储数组
typedef __packed struct
{
	fn_game_status_t game_status;//0x0001比赛状态数据
	fn_game_result_t game_result;//0x0002比赛结果数据
	fn_game_robot_HP_t game_robot_HP;//0x0003机器人血量数据
	fn_ICRA_buff_debuff_zone_status_t ICRA_buff_debuff_zone_status;//0x0005人工智能挑战赛
	fn_event_data_t event_data;//0x0101场地事件数据
	fn_supply_projectile_action_t supply_projectile_action;//0x0102补给站动作标志
	fn_referee_warning_t referee_warning;//0x0104裁判警告信息
	fn_dart_remaining_time_t dart_remaining_time;//0x0105飞镖发射口倒计时
	fn_game_robot_status_t game_robot_status;//0x0201比赛机器人状态
	fn_power_heat_data_t power_heat_data;//0x0202实时功率热量数据
	fn_game_robot_pos_t game_robot_pos;//0x0203机器人位置数据
	fn_buff_t buff;//0x0204机器人增益
	fn_aerial_robot_energy_t aerial_robot_energy;//0x0205空中机器人能量状态
	fn_robot_hurt_t robot_hurt;//0x0206伤害状态
	fn_shoot_data_t shoot_data;//0x0207实时射击信息
	fn_bullet_remaining_t bullet_remaining;//0x0208子弹剩余发射数
	fn_rfid_status_t rfid_status;//0x0209机器人RFID状态
	fn_dart_client_cmd_t dart_client_cmd;//0x020A飞镖机器人客户端数据
	fn_location_t location;//0x020B机器人位置数据
	fn_mark_data_t mark_data;//0x020C敌方机器人被雷达标记进度
	fn_Sentry_Data_t Sentry_Data;//哨兵自主决策信息同步 0x020D 
	fn_map_robot_data_t map_robot;//0x0305	选手端小地图接收雷达数据
	fn_map_data_t map_data;//0x0307选手端小地图接收哨兵数据
	fn_remote_control_t remote_control;//0x0304键鼠遥控数据
	fn_robot_interaction_data_t robot_interaction;//0x0301机器人交互数据
	fn_map_command_t map_command;//0x0303选手端小地图交互数据
}fn_P_stgamestatus;

extern fn_P_stgamestatus P_stgamestatus;
extern uint8_t P_ucJudgeDataBuffer[JUDGE_BUFFER_LENGTH];  
//extern SemaphoreHandle_t JudgeDataDecode_Binary;
extern struct ArrayList P_stJudgeDataArrayListBuff;//裁判系统串口接受数据缓冲 //用于解决粘包，半包等问题
void Task_JudgeDataSend(void *Parameters);
//void Task_JudgeDataDecode(void *Parameters);
void RM_Judge_DataDecodeByBuff(uint8_t *pDecodeData);
bool RM_Judge_FindFrame(struct ArrayList * arrlist);
int RM_Judge_DataLength(struct ArrayList * arrlist);
void RM_Judge_DataDequeue(u8* buffer, struct ArrayList * array, int offset, int size);
void RM_Judge_DataEnqueue(unsigned char* buffer, struct ArrayList * array, int len);


#endif
