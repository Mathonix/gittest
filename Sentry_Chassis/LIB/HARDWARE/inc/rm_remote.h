#ifndef __RM_REMOTE_H__
#define __RM_REMOTE_H__
#include "main.h"

#define REMOTE_DATA_RX_LEN 50u
#define REMOTE_DATAFRAME_LEN 25u //����֡����

extern uint8_t P_uintRemote_Data_Buf[2][REMOTE_DATA_RX_LEN];


#define Switch_A ch5 
#define Switch_B ch6 
#define Switch_C ch7 
#define Switch_D ch8 

typedef struct Remote_TypeDef{
    int16_t ch1;         //��ҡ��X��,��Χ��-670~670
    int16_t ch2;         //��ҡ��Y��,��Χ��-670~670
    int16_t ch3;         //��ҡ��X��,��Χ��-670~670
    int16_t ch4;         //��ҡ��Y��,��Χ��-670~670
    int16_t ch5;    //ҡ��SA Hex�� �ϣ�0x161 �У�0x400 �£�0x69E ҡ�������м��ͣ��
    int16_t ch6;    //ҡ��SB Hex�� �ϣ�0x161 �У�0x400 �£�0x69E ҡ������
    int16_t ch7;    //ҡ��SC Hex�� �ϣ�0x161 �У�0x400 �£�0x69E ҡ������
    int16_t ch8;    //ҡ��SD Hex�� �ϣ�0x161 �У�0x400 �£�0x69E ҡ�������м��ͣ��
}Remote_TypeDef;

typedef enum{
     Up   = 0x161,
   Middle = 0x400,
    Down  = 0x69E      
}SBUS_Switch_Value; //����ֵö��

void fnRemote_RawDataDecode(Remote_TypeDef *st_data,uint8_t *sz_recvdata);
extern Remote_TypeDef P_stRemoteData_Recv;
extern Remote_TypeDef P_stRemoteData_Recv_Last;
#endif
