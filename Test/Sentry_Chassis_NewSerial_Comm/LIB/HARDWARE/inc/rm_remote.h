#ifndef __RM_REMOTE_H__
#define __RM_REMOTE_H__
#include "main.h"

#define REMOTE_DATA_RX_LEN 50u
#define REMOTE_DATAFRAME_LEN 25u //数据帧长度

extern uint8_t P_uintRemote_Data_Buf[2][REMOTE_DATA_RX_LEN];


#define Switch_A ch5 
#define Switch_B ch6 
#define Switch_C ch7 
#define Switch_D ch8 

typedef struct Remote_TypeDef{
    int16_t ch1;         //左摇杆X轴,范围：-670~670
    int16_t ch2;         //左摇杆Y轴,范围：-670~670
    int16_t ch3;         //右摇杆X轴,范围：-670~670
    int16_t ch4;         //右摇杆Y轴,范围：-670~670
    int16_t ch5;    //摇杆SA Hex码 上：0x161 中：0x400 下：0x69E 摇杆两档中间可停留
    int16_t ch6;    //摇杆SB Hex码 上：0x161 中：0x400 下：0x69E 摇杆三档
    int16_t ch7;    //摇杆SC Hex码 上：0x161 中：0x400 下：0x69E 摇杆三档
    int16_t ch8;    //摇杆SD Hex码 上：0x161 中：0x400 下：0x69E 摇杆两档中间可停留
}Remote_TypeDef;

typedef enum{
     Up   = 0x161,
   Middle = 0x400,
    Down  = 0x69E      
}SBUS_Switch_Value; //按键值枚举

void fnRemote_RawDataDecode(Remote_TypeDef *st_data,uint8_t *sz_recvdata);
extern Remote_TypeDef P_stRemoteData_Recv;
extern Remote_TypeDef P_stRemoteData_Recv_Last;
#endif
