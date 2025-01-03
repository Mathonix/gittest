#include "hi219m.h"
//#define PI 3.1415926f
uint8_t P_uintH219MDataBuffer[HI219M_RX_BUF_LEN];				//H219数据缓存数组 
uint16_t P_uintH219BuffLength; //数据长度

Hi219m_TypeDef P_stHi219m;

void configHi219m_ParaInit(void)
{
	imu_data_decode_init();
}
int16_t mag[3];
float mage[3];
float geomagnetism;
//陀螺仪角度处理
void fnHi219m_DataDecode(Hi219m_TypeDef* st_data)
{
	float Eular[3];
	int16_t Gyo[3];
	
	get_raw_gyo(Gyo);
	get_eular(Eular);
	get_raw_mag(mag);
	mage[0] = mag[0]/10.f;
	mage[1] = mag[1]/10.f;
	mage[2] = mag[2]/10.f;
	if(mage[0]<0)
	geomagnetism = atan(mage[1]/mage[0])+PI;
	else
	geomagnetism = atan(mage[1]/mage[0]);
	st_data->Last_Yaw = st_data->Yaw;
	st_data->Last_Pitch= st_data->Pitch;
	
	st_data->Roll = Eular[1];
	st_data->Yaw = 360 +Eular[2];
	st_data->Pitch =  Eular[0];
	
	st_data->Yaw_Gyo = Gyo[2]/10.f;
	st_data->Pitch_Gyo = Gyo[1]/10.f;
	st_data->Roll_Gyo = Gyo[0]/10.f;
	
	if(st_data->Yaw - st_data->Last_Yaw >= 330)
	{
		st_data->Round_Yaw --;
	}
	else if(st_data->Yaw - st_data->Last_Yaw <= -330)
	{
		st_data->Round_Yaw ++;
	}
	
	if(st_data->Pitch - st_data->Last_Pitch >= 330)
	{
		st_data->Round_Pitch --;
	}
	else if(st_data->Pitch - st_data->Last_Pitch<= -330)
	{
		st_data->Round_Pitch ++;
	}
	
	st_data->Continuous_Yaw = st_data->Yaw + st_data->Round_Yaw *360;
	st_data->Continuous_Pitch = st_data->Pitch + st_data->Round_Pitch *360;
}
