#include "kalman.h"

void Filter_Init(user_filter *pass,float Q,float R)
{
	pass->Q=Q;
	pass->R=R;
	
	pass->X=0;
	pass->P=1;
}

float Filter_Calc(user_filter *pass,float value)
{
	//先验估计
	pass->X=pass->X;
	pass->P=pass->P+pass->Q;
	
	//计算卡尔曼增益
	pass->K=pass->P/(pass->P+pass->R);
	
	//数据更新
	pass->X=pass->X+pass->K*(value-pass->X);
	pass->P=(1-pass->K)*pass->P;
	
	return pass->X;
}


void kalman_init(Kalman_TypeDef *Kalman,float Q_0,float Q_1,float R_0,float R_1)
{
	 Kalman->x_t[0]=0;
	 Kalman->x_t[1]=1;
	
	 Kalman->P[0][0]=1;
	 Kalman->P[0][1]=0;
	 Kalman->P[1][0]=0;
	 Kalman->P[1][1]=1;
	
	 Kalman->Q[0][0]=Q_0;
	 Kalman->Q[0][1]=0;
	 Kalman->Q[1][0]=0;
	 Kalman->Q[1][1]=Q_1;
	
	 Kalman->R[0][0]=R_0;
	 Kalman->R[0][1]=0;
	 Kalman->R[1][0]=0;
	 Kalman->R[1][1]=R_1;
	
}

void kalman_calc(Kalman_TypeDef *Kalman,float angle,float speed)//speed单位为PRM
{
	float inv_PR[2][2],det_PR,//用于计算卡尔曼增益
		change=0.06;//1r/min=0.06°/ms
	
	Kalman->z_t[0]=angle;
	Kalman->z_t[1]=change*speed;
	//先验证估计
	Kalman->x_hat_t[0]=Kalman->x_t[0]+Kalman->x_t[1];
	Kalman->x_hat_t[1]=Kalman->x_t[1];
	
	Kalman->P[0][0]=Kalman->P[0][0]+Kalman->P[0][1]+Kalman->P[1][0]+Kalman->P[1][1]+Kalman->Q[0][0];
	Kalman->P[0][1]=Kalman->P[0][1]+Kalman->P[1][1];
	Kalman->P[1][0]=Kalman->P[1][0]+Kalman->P[1][1];
	Kalman->P[1][1]=Kalman->P[1][1]+Kalman->Q[1][1];
	
	//计算卡尔曼增益
	inv_PR[0][0]=Kalman->P[0][0]+Kalman->R[0][0];
	inv_PR[1][1]=Kalman->P[1][1]+Kalman->R[1][1];
	det_PR=inv_PR[0][0]*inv_PR[1][1]-inv_PR[0][1]*inv_PR[1][0];
	
	inv_PR[0][0] = inv_PR[1][1]/det_PR;
	inv_PR[0][1] =-inv_PR[0][1]/det_PR;
	inv_PR[1][0] =-inv_PR[1][0]/det_PR;
	inv_PR[1][1] = inv_PR[0][0]/det_PR;
	
	Kalman->K[0][0]=Kalman->P[0][0]*inv_PR[0][0]+Kalman->P[0][1]*inv_PR[1][0];
	Kalman->K[0][1]=Kalman->P[0][0]*inv_PR[0][1]+Kalman->P[0][1]*inv_PR[1][1];
	Kalman->K[1][1]=Kalman->P[1][0]*inv_PR[0][0]+Kalman->P[1][1]*inv_PR[1][0];
	Kalman->K[1][0]=Kalman->P[1][0]*inv_PR[0][1]+Kalman->P[1][1]*inv_PR[1][1];
	
	//更新
	
	//获取最优估计值
	Kalman->x_t[0]=Kalman->x_hat_t[0]+(Kalman->K[0][0]*(Kalman->z_t[0]-Kalman->x_hat_t[0])+Kalman->K[0][1]*(Kalman->z_t[1]-Kalman->x_hat_t[1]));
	Kalman->x_t[1]=Kalman->x_hat_t[1]+(Kalman->K[1][0]*(Kalman->z_t[0]-Kalman->x_hat_t[0])+Kalman->K[1][1]*(Kalman->z_t[1]-Kalman->x_hat_t[1]));
	
	//更新后验证协方差
	Kalman->P[0][0]=(1-Kalman->K[0][0])*Kalman->P[0][0]+(1-Kalman->K[0][1])*Kalman->P[1][0];
	Kalman->P[0][1]=(1-Kalman->K[0][0])*Kalman->P[0][1]+(1-Kalman->K[0][1])*Kalman->P[1][1];
	Kalman->P[1][0]=(1-Kalman->K[1][0])*Kalman->P[0][0]+(1-Kalman->K[1][1])*Kalman->P[1][0];
	Kalman->P[1][1]=(1-Kalman->K[1][0])*Kalman->P[0][1]+(1-Kalman->K[1][1])*Kalman->P[1][1];
	
	//输出
	Kalman->angle_out_t=Kalman->x_t[0];
	Kalman->speed_out_t=Kalman->x_t[1]/change;
	
}
