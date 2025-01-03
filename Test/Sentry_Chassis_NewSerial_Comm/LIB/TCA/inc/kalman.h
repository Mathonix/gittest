#ifndef __KALMAN_H
#define __KALMAN_H
#include "stm32f4xx.h"
/*************************************
状态空间方程：X(k)=X(k-1)+W(k-1)
观测方程：		 Z(k)=X(k)+V(k)
X:数值
Z:测量值
用于电机速度滤波
*************************************/
typedef struct
{
	float Q,//先验误差
				R,//观测误差
				K,//卡尔曼增益
				P,//协方差
				X;//估计值
}user_filter;

/*************************************
状态空间方程：X(k)=AX(k-1)+W(k-1)
观测方程：		 Z(k)=HX(k)+V(k)

设置采样时间为1ms
X=|X1|   H=| 1  0 |		A=|	1  1 |
	|X2|		 | 0  1 |			| 0  1 |
X1:角度			X2:速度
用于角度和速度都具有较大的白噪声情况
*************************************/
typedef struct {
	float x_t[2],
				x_hat_t[2],
				z_t[2],
				K[2][2],
				P[2][2],
				Q[2][2],
				R[2][2],
	
				angle_out_t,//输出
				speed_out_t;
}Kalman_TypeDef;

void kalman_init(Kalman_TypeDef *Kalman,float Q_0,float Q_1,float R_0,float R_1);
void kalman_calc(Kalman_TypeDef *Kalman,float angle,float speed);

//滤波
void Filter_Init(user_filter *pass,float Q,float R);
float Filter_Calc(user_filter *pass,float value);
#endif 


/*************************************************
数学模型：
X1:位置    X2:速度
设采样时间t为1ms
X1=X1_Last+X2_Last+W

观测方程

z=Hz_last+v

H=| 1  0 |
	| 0  1 |


A=|	1  1 |
	| 0  1 |
	
	
改代码为测试代码
***************************************************/
