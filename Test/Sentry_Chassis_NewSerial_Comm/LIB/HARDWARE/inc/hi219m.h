#ifndef __HI219M_H__
#define __HI219M_H__

#include "main.h"

#define HI219M_RX_BUF_LEN 128

typedef struct Hi219m_TypeDef
{
	float Yaw;
	float Pitch;
	float Roll;
	
	float Yaw_Gyo;
	float Pitch_Gyo;
	float Roll_Gyo;
	
	float Last_Yaw;
	float Last_Pitch;
	
	float Continuous_Yaw;
	float Continuous_Pitch;
	
	int32_t Round_Yaw;
	int32_t Round_Pitch;
}Hi219m_TypeDef;

extern uint8_t P_uintH219MDataBuffer[HI219M_RX_BUF_LEN];//H219���ݻ������� 
extern uint16_t P_uintH219BuffLength;
extern Hi219m_TypeDef P_stHi219m;
extern float geomagnetism;
void configHi219m_ParaInit(void);
void fnHi219m_DataDecode(Hi219m_TypeDef* st_data);

#endif
