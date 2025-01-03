#ifndef __CHASSIS_BEHAVIOR_H__
#define __CHASSIS_BEHAVIOR_H__
#include "main.h"
#include "motor.h"
#include "pid.h"
typedef enum
{
	Chassis_BlackOut,//底盘断电
	Chassis_Working//运动状态
}e_Chassis_State;//底盘状态

typedef enum
{
	Chassis_Follow,//底盘跟随状态
    Chassis_NoFollow,//底盘不跟随状态
	Chassis_Twist,//扭腰状态(早期RM无滑环时，类似小陀螺的模式)
	Chassis_Spin,//小陀螺状态
	Chassis_Spin_Finish,//小陀螺复位状态
    Chassis_Fix,//底盘前进方向固定状态
	Chassis_AI,//串口控制状态
}e_ChassisMotion_State;//底盘运动状态

typedef struct Chassis_Speed_TypeDef
{
	float vx;//左右平移速度
	float vy;//前后平移速度
	float vw;//旋转速度
	
}Chassis_Speed_TypeDef;//底盘速度结构体

typedef struct Chassis_Direction_TypeDef
{
    float Encoder_Direction;//初始编码器方向
    float Gyro_Direction;//初始陀螺仪方向
	
}Chassis_Direction_TypeDef;//底盘速度结构体

typedef enum
{
	Chassis_Spin_speed_high,//小陀螺状态
	Chassis_Spin_speed_low,
}e_Chassis_Spin_State;//底盘运动状态

typedef struct {
	float32_t v;//m/s
	float32_t yaw;//rad
}Chassis_Vector_Typedef;      //速度向量结构体

       //舵轮速度结构体

typedef struct Chassis_TypeDef
{
	//底盘状态
	e_Chassis_State State;
	e_ChassisMotion_State Mode;
  e_Chassis_Spin_State Spin_State;
	 
	bool Spin_Reset_Flag;
	//底盘速度参数
    Chassis_Direction_TypeDef Init_Direction; //初始方向
	Chassis_Speed_TypeDef Para;	
	PID_InitTypeDef Follow_PID;
	PID_InitTypeDef Twist_PID;
  PID_InitTypeDef Spin_Finish_PID;
	PID_InitTypeDef AI_PID;
}Chassis_TypeDef;//底盘结构体

/******************函数声明*********************/
void Task_ChassisCtrl(void);
void Chassis_Control(float vx,float vy,float vw);
void configChassis_ParaInit(void);
static void Chassis_SetMode(Chassis_TypeDef *st_data,e_ChassisMotion_State mode);
#endif
