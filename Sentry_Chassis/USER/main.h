#ifndef __MAIN_H__
#define __MAIN_H__
#include "stm32f4xx.h"

//Local
#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include <math.h>
#include <string.h>
#include <stdarg.h>

//FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"  
#include "croutine.h"

//BSP
#include "io.h"
#include "can.h"
#include "dma.h"
#include "nvic.h"
#include "uart.h"
#include "tim.h"

//APPLICATION
#include "chassis_behavior.h"
#include "minipc.h"
#include "offline_detection.h"
#include "user_task.h"

//HARDWARE
#include "motor.h"
#include "rm_remote.h"
#include "hi219m.h"
#include "imu_data_decode.h"
#include "packet.h"
#include "vofa.h"

//TCA
#include "pid.h"
#include "kalman.h"
#include "crc_check.h"

//Judge
#include "judge.h"
#include "Arraylist.h"

//DSP arm_math
#include "arm_math.h"
#include "arm_common_tables.h"
/**
 * @name 宏定义部分
 */
//#define PI (3.14159265f) arm_math中已定义

/**
 * @name 宏定义函数
 */
#define abs(x) ((x)>0?(x):-(x))

#define limit(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\

/*-----------------弧度角度互转-------------------*/
#define DEG2R(x) ((x)*PI /180.0f)
#define R2DEG(x) ((x)*180.0f /PI)

#endif
