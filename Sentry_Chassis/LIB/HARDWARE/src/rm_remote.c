#include "rm_remote.h"


uint8_t SBUS_First_Connected = 0;   //遥控器初次连接到接收端的标志位
uint8_t P_uintRemote_Data_Buf[2][REMOTE_DATA_RX_LEN];//遥控器缓存数组

Remote_TypeDef P_stRemoteData_Recv;
Remote_TypeDef P_stRemoteData_Recv_Last;

void fnRemote_RawDataDecode(Remote_TypeDef *st_data,uint8_t *sz_recvdata)
{
    P_stRemoteData_Recv_Last = P_stRemoteData_Recv;//记录上一次遥控器数据，用于做跳变检测

    st_data->ch1 = ((sz_recvdata[1] | sz_recvdata[2]<<8) & 0x7ff) - 1024;
	st_data->ch2 = ((sz_recvdata[2]>>3 | sz_recvdata[3]<<5) & 0x7ff) - 1024;
	st_data->ch3 = ((sz_recvdata[3]>>6 | sz_recvdata[4]<<2 | sz_recvdata[5]<<10) & 0x7ff) - 1024;
	st_data->ch4 = ((sz_recvdata[5]>>1 | sz_recvdata[6]<<7) & 0x7ff) - 1024;
	st_data->ch5 = ((sz_recvdata[6]>>4 | sz_recvdata[7]<<4) & 0x7ff);
	st_data->ch6 = ((sz_recvdata[7]>>7 | sz_recvdata[8]<<1 | sz_recvdata[9]<<9) & 0x7ff);
	st_data->ch7 = ((sz_recvdata[9]>>2 | sz_recvdata[10]<<6) & 0x7ff);
	st_data->ch8 = ((sz_recvdata[10]>>5 | sz_recvdata[11]<<3) & 0x7ff);

    //SBUS初次上电检测，如果检测到发送机遥控器没有开机过，则将所有的遥控器数据清零
    if(st_data->ch5 == 0x400 && st_data->ch6 == 0x400 && st_data->ch7 == 0x400 && st_data->ch8 == 0x400 && 
        st_data->ch1 ==0 &&st_data->ch2==0&&st_data->ch3==0&&st_data->ch4==0 && SBUS_First_Connected == 0)
    {
        st_data->ch5 = 0;
        st_data->ch6 = 0;
        st_data->ch7 = 0;
        st_data->ch8 = 0;
    }
    else SBUS_First_Connected = 1;

}

