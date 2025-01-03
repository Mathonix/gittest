#ifndef __MAIN_H__
#define __MAIN_H__
#include "stm32f4xx.h"
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
#include "uart.h"
#include "it.h"
#include "can.h"
#include "dma.h"
#include "nvic.h"

//APPLICATION
#include "chassis_behavior.h"
#include "offline_detection.h"
#include "user_task.h"
#include "minipc.h"


#endif
