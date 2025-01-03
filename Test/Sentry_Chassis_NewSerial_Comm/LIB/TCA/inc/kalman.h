#ifndef __KALMAN_H
#define __KALMAN_H
#include "stm32f4xx.h"
/*************************************
״̬�ռ䷽�̣�X(k)=X(k-1)+W(k-1)
�۲ⷽ�̣�		 Z(k)=X(k)+V(k)
X:��ֵ
Z:����ֵ
���ڵ���ٶ��˲�
*************************************/
typedef struct
{
	float Q,//�������
				R,//�۲����
				K,//����������
				P,//Э����
				X;//����ֵ
}user_filter;

/*************************************
״̬�ռ䷽�̣�X(k)=AX(k-1)+W(k-1)
�۲ⷽ�̣�		 Z(k)=HX(k)+V(k)

���ò���ʱ��Ϊ1ms
X=|X1|   H=| 1  0 |		A=|	1  1 |
	|X2|		 | 0  1 |			| 0  1 |
X1:�Ƕ�			X2:�ٶ�
���ڽǶȺ��ٶȶ����нϴ�İ��������
*************************************/
typedef struct {
	float x_t[2],
				x_hat_t[2],
				z_t[2],
				K[2][2],
				P[2][2],
				Q[2][2],
				R[2][2],
	
				angle_out_t,//���
				speed_out_t;
}Kalman_TypeDef;

void kalman_init(Kalman_TypeDef *Kalman,float Q_0,float Q_1,float R_0,float R_1);
void kalman_calc(Kalman_TypeDef *Kalman,float angle,float speed);

//�˲�
void Filter_Init(user_filter *pass,float Q,float R);
float Filter_Calc(user_filter *pass,float value);
#endif 


/*************************************************
��ѧģ�ͣ�
X1:λ��    X2:�ٶ�
�����ʱ��tΪ1ms
X1=X1_Last+X2_Last+W

�۲ⷽ��

z=Hz_last+v

H=| 1  0 |
	| 0  1 |


A=|	1  1 |
	| 0  1 |
	
	
�Ĵ���Ϊ���Դ���
***************************************************/
