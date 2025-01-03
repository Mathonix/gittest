#ifndef __MOTOR_H__
#define __MOTOR_H__
#include <stdio.h>
#include "stdbool.h"
#include "stm32f4xx.h"
#include "pid.h"
#include "rm_remote.h"

#define MOTOR_3508_REDUCTIONRATE 19.f //3508电机减速比为19：1
#define MOTOR_C620_REDUCTIONRATE 19.f //3508电机减速比为19：1

#define MOTOR_CANSEND_IDENTIFIER1_4 0x200 // 电调ID 1~4使用此标识符
#define MOTOR_CANSEND_IDENTIFIER5_8 0x1ff // 电调ID 5~8使用此标识符

#define MOTOR_CHASSIS_F_CAN_ID 0x201 //底盘左前轮电机CAN口ID
#define MOTOR_CHASSIS_B_CAN_ID 0x202 //底盘右后轮电机CAN口ID

#define MOTOR_RUDDER_F_CAN_ID 0x205  //底盘左前舵向轮电机CAN口ID
#define MOTOR_RUDDER_B_CAN_ID 0x206  //底盘右后舵向轮电机CAN口ID

#define MOTOR_GIMBAL_YAWL_CAN_ID 0x205 //云台大Yaw轴电机CAN口ID
#define MOTOR_GIMBAL_YAWH_CAN_ID 0x206 //云台小Yaw轴电机CAN口ID
#define MOTOR_GIMBAL_PITCH_CAN_ID 0x207 //云台Pitch轴电机CAN口ID

#define ROTATE_SPEEDBUF_LEN  6 //速度滤波数组缓存长度

typedef struct 
{
  uint8_t     CANx;               //CAN编号     1 CAN1      2 CAN2
  CanTxMsg    SendCanTxMsg;       //发送数据
}CanSend_Type;



//3508电机原始数据处理结构体
typedef struct M3508_Data_TypeDef
{
	//原始数据
	int16_t Encoder_Val;//编码器值
	int16_t Rotate_Speed;//转子速度
	int16_t Armature_Current;//电枢电流
	int8_t Motor_Temperature; //电机温度
	
	//速度滤波
	int16_t Rotate_FliterSpeed;//滤波后的速度
	int16_t Rotate_SpeedBuf[ROTATE_SPEEDBUF_LEN];
	int16_t Rotate_BufCount;//数组数据计数

}M3508_DataRecv_TypeDef;

//3508电机数据结构体
typedef struct M3508_TypeDef
{
	int8_t CAN_ID;//CAN ID号
	uint8_t Reduction_Rate;//电机减速比
	M3508_DataRecv_TypeDef RecvData;//电机数据储存
	PID_InitTypeDef SpeedPID;//速度环PID控制数据
}M3508_TypeDef;

//6020电机原始数据处理结构体
typedef struct M6020_Data_TypeDef
{
	//原始数据
	int16_t Encoder_Val;//编码器值
	int16_t Rotate_Speed;//转子速度
	int16_t Armature_Current;//电枢电流
	int8_t Motor_Temperature; //电机温度
	
	int16_t Last_Encoder_Val;//上一次编码器值
	int32_t Number_Of_Turns;//电机旋转圈数
    float Custom_Angle_Zero;    //电机自定义角度预设零点值，单位为度，以Raw_Angle计算

	float Raw_Angle;//电机转度 0-360度
	float Shaft_Angle;//电机转过的角度
	float Custom_Angle;//电机自定义角度
	//速度滤波
	int16_t Rotate_FliterSpeed;//滤波后的速度
	int16_t Rotate_SpeedBuf[ROTATE_SPEEDBUF_LEN];
	int16_t Rotate_BufCount;//数组数据计数

}M6020_DataRecv_TypeDef;

//6020数据结构体
typedef struct M6020_TypeDef
{
	int8_t CAN_ID;//CAN ID号
	M6020_DataRecv_TypeDef RecvData;//电机数据储存

	PID_InitTypeDef SpeedPID;//速度环PID控制数据
	PID_InitTypeDef AnglePID;//角度环PID控制数据
}M6020_TypeDef;



extern M3508_TypeDef P_stMotor_ChassisF;//底盘左前电机
extern M3508_TypeDef P_stMotor_ChassisB;//底盘左后电机
extern M6020_TypeDef P_stMotor_RudderF;  //底盘左前舵电机
extern M6020_TypeDef P_stMotor_RudderB;  //底盘右后舵电机

extern M6020_TypeDef P_stMotor_Gimbal_Yaw;//云台Yaw轴电机

void configMotor_ParaInit(void);

void fnMotor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg);
void fnMotor_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i);

void fnM3508_SpeedCotrol( M3508_TypeDef* st_data,float target_speed);

void fnM6020_Cotrol( M6020_TypeDef* st_data,float target_angle,float feedback_angle,float feedback_speed);

static void s_fnMotor_CANSend(CAN_TypeDef *CANx, CanTxMsg *stMotorSendData);
static void s_fnM3508_RawDataDecode(M3508_TypeDef* st_data,CanRxMsg * msg);
static void s_fnM6020_RawDataDecode(M6020_TypeDef* st_data,CanRxMsg * msg);

#endif
