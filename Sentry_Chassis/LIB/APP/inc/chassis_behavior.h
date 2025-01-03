#ifndef __CHASSIS_BEHAVIOR_H__
#define __CHASSIS_BEHAVIOR_H__
#include "main.h"

#include "motor.h"
#include "pid.h"
#include "arm_math.h"

/*近似值*/
#define SIN45 0.707107f
#define COS45 0.707107f
typedef enum
{
	Chassis_BlackOut,//底盘断电
	Chassis_Working//运动状态
}e_Chassis_State;//底盘状态

typedef enum
{
    /*----------*/
    Chassis_NoFollow,//底盘不跟随状态
    Chassis_AI,//串口控制状态
    Chassis_Navigator,//导航测试模式
    /*----------*/
    
	Chassis_Follow,//底盘跟随状态
	Chassis_Twist,//扭腰状态
	Chassis_Spin,//小陀螺状态
	Chassis_Spin_Finish,//小陀螺复位状态
    Chassis_Fix,//底盘前进方向固定状态

}e_ChassisMotion_State;//底盘运动状态

typedef struct Chassis_Speed_TypeDef
{
	float vx;//左右平移速度
	float vy;//前后平移速度
	float vw;//旋转速度
	
}Chassis_Speed_TypeDef;//底盘速度结构体


typedef struct {       //舵轮速度结构体
	float32_t v;//m/s
	float32_t angle;//degree
}Chassis_WhlVct_Typedef;      //速度向量结构体

typedef struct Chassis_RstPara_Typedef
{
    float Initial_Yaw;              //初始Yaw值
    float Initial_Encoder;           //编码器初始值
    float Initial_Gyro;             //陀螺仪初始值
    float Pos_Diff;             //上电后编码器值 与 正方向编码器值 的差值
    float Converted_GyroYaw;        //加上差值后陀螺仪的前进初始方向
    
}Chassis_RstPara_Typedef;


typedef struct Chassis_Cali_TypeDef
{
	bool Cali_Finish_Flag;
	
	float Cali_Yaw_180; //云台Yaw校准值
	float Cali_Yaw_360; //云台Yaw校准值

}Chassis_Cali_TypeDef;


typedef struct Chassis_TypeDef
{
	//底盘状态
	e_Chassis_State State;
	e_ChassisMotion_State Mode;
	 
	bool Spin_Reset_Flag;
    
	//底盘速度参数
	Chassis_Speed_TypeDef Para;	
    Chassis_RstPara_Typedef RstPara;    //底盘正方向重置参数
    Chassis_Cali_TypeDef Cali;
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
