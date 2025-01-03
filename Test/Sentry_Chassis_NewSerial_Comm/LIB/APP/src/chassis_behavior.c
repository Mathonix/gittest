#include "chassis_behavior.h"
#include "arm_math.h"

/************************�����趨************************/
#define CHASSIS_DISABLE 0
#define CHASSIS_SPEED_MAX_X 12//����X��������ٶ�3
#define CHASSIS_SPEED_MAX_Y 12 //����Y��������ٶ�3
#define CHASSIS_SPEED_MAX_W 0.009f //����Y��������ٶ�

//���̲�������
#define CHASSIS_LENGTH 254      //���̳���һ��
#define CHASSIS_WIDTH 254       //���̿��һ��
#define WHEEL_PERIMETER 960       //�����ܳ�
#define CHASSIS_DECELE_RATIO  19 //���̼��ٱ�

/***********************��������***********************/
float Gimbal_Gyro_Continuous_Yaw; //��̨����������Yaw�Ƕ�
float Gimbal_Gyro_Initial_Yaw; //��̨�����ǳ�ʼYaw�Ƕ�
extern bool TeamColor;
extern M6020_TypeDef P_stMotor_Gimbal_YawL; //��̨��yaw�����ṹ��
extern M6020_TypeDef P_stMotor_Gimbal_YawH; //��̨Сyaw�����ṹ��

Chassis_TypeDef P_stChassis ={Chassis_BlackOut};//���̲����ṹ��
/**
 * @name    ���̿�������
 * @brief   ͨ��ң������λ���Ƶ���ģʽ
 * @param   ��
 * @retval  ��
 */
float vx,vy,vw; 
float vx_1,vy_1,vw_1;
float Reset_Gyro_Angle;
float Reset_Encoder_Angle;
float a,b; 
void Task_ChassisCtrl(void)
{
    portTickType CurrentControlTick = 0;
    
    u16 countT  = 0; //���ڼ�¼����ʱ�Ķ�Ӧʱ��
    while(1)
    {
        switch(P_stRemoteData_Recv.Switch_B)//��ȡң������λ
        {
            case Down:  // ȫ���µ�
            {
                P_stChassis.State = Chassis_BlackOut;
                Reset_Gyro_Angle = 0; //���������Ǹ�λ�Ƕ�
                Reset_Encoder_Angle = 0; //���ñ�������λ�Ƕ�
                Chassis_SetMode(&P_stChassis,Chassis_Follow);//�˶�ģʽ����Ϊ���̸���

                vx_1 = 0;
                vy_1 = 0;
                vw_1 = 0;
                countT = 0;
                
                
                
            }break;

            case Middle:   //��������̨����Ϊ�������ƶ�             //Switch_BΪ�м䵲λʱ������Switch_C��ֵ�����ж�
            {
                switch(P_stRemoteData_Recv.Switch_C)
                {
                    case Down:  //ң��ģʽ
                    {
                        if(countT ++ < 1000)
                        {

                            P_stChassis.Init_Direction.Gyro_Direction = P_stHi219m.Continuous_Yaw; //��¼��λ����ʱ�ĵ��������ǽǶ�	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //��¼��λ����ʱ�Ĵ�Yaw�������Ƕ�
							P_stChassis.State = Chassis_BlackOut;
                        }
                        else
                        {
                            countT = 2600;
                            P_stChassis.State = Chassis_Working;
                            if(P_stRemoteData_Recv.Switch_D == Down)
                            Chassis_SetMode(&P_stChassis,Chassis_Follow);//�˶�ģʽ����Ϊ���̸����ƶ�
                            else if(P_stRemoteData_Recv.Switch_D == Up)
                            Chassis_SetMode(&P_stChassis,Chassis_Spin);//�˶�ģʽ����ΪС����
                        }

                    }break;

                    case Middle: //ң��ģʽ��Switch_D�Ķ�����������̨ʵ��
                    {
                        if(countT ++ < 1000)
                        {
                            P_stChassis.Init_Direction.Gyro_Direction = P_stHi219m.Continuous_Yaw; //��¼��λ����ʱ�������ǽǶ�	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //��¼��λ����ʱ�Ĵ�Yaw�������Ƕ�	
							P_stChassis.State = Chassis_BlackOut;
                        }
                        else
                        {
                            countT = 2600;
                            P_stChassis.State = Chassis_Working;
                            Chassis_SetMode(&P_stChassis,Chassis_NoFollow);//�˶�ģʽ����Ϊ���̲�����
                            //Switch_D�Ĺ�������̨ʵ��
                        }
                    }break;

                    case Up:    //����ģʽ
                    {
                        if(countT++ < 1000)
						{									
							P_stChassis.Init_Direction.Gyro_Direction = P_stHi219m.Continuous_Yaw; //��¼��λ����ʱ�������ǽǶ�	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //��¼��λ����ʱ�Ĵ�Yaw�������Ƕ�	
							P_stChassis.State = Chassis_BlackOut;
						}
						else
						{
							countT = 2600;
							P_stChassis.State = Chassis_Working;
							Chassis_SetMode(&P_stChassis,Chassis_Spin);//�˶�ģʽ����Ϊ���̸���
						}
                    }break;
                }
            }break;   

            case Up: //�����Գ�ʼ��̨��λ����̨����Ϊ�������ƶ�              //Switch_BΪ�ϵ�λʱ������Switch_C��ֵ�����ж�
            {
                switch(P_stRemoteData_Recv.Switch_C)
                {
                    case Down:  //ң��ģʽ
                    {
                        if(countT++ < 1000)
				        {		
							P_stChassis.Init_Direction.Gyro_Direction = P_stHi219m.Continuous_Yaw; //��¼��λ����ʱ�������ǽǶ�	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //��¼��λ����ʱ�Ĵ�Yaw�������Ƕ�	
							P_stChassis.State = Chassis_BlackOut;				        
                        }
				        else
				        {
					        countT = 2600;
					        P_stChassis.State = Chassis_Working;
					        Chassis_SetMode(&P_stChassis,Chassis_Spin);//�˶�ģʽ����Ϊ������ת
				        }
                    }break;

                    case Middle://��������ģʽ
                    {
                        if(countT++ < 1000)
				        {		
							P_stChassis.Init_Direction.Gyro_Direction = Gimbal_Gyro_Continuous_Yaw; //��¼��λ����ʱ�������ǽǶ�	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //��¼��λ����ʱ�Ĵ�Yaw�������Ƕ�	
							P_stChassis.State = Chassis_BlackOut;				        
                        }
				        else
				        {
					        countT = 2600;
					        P_stChassis.State = Chassis_Working;
					        Chassis_SetMode(&P_stChassis,Chassis_AI);//�˶�ģʽ����ΪAIģʽ
				        }
                    }break;

                    case Up:    //AIģʽ���ձ�������������
                    {
                        if(countT++ < 1000)
				        {		
							P_stChassis.Init_Direction.Gyro_Direction = Gimbal_Gyro_Continuous_Yaw; //��¼��λ����ʱ�������ǽǶ�	
                            P_stChassis.Init_Direction.Encoder_Direction = P_stMotor_Gimbal_YawL.RecvData.Raw_Angle; //��¼��λ����ʱ�Ĵ�Yaw�������Ƕ�	
							P_stChassis.State = Chassis_BlackOut;				        
                        }
				        else
				        {
					        countT = 2600;
					        P_stChassis.State = Chassis_Working;
					        Chassis_SetMode(&P_stChassis,Chassis_AI);//�˶�ģʽ����ΪAIģʽ
				        }
                    }break;
                }
            }break;
        }
        Chassis_Control(vx,vy,vw);
        vTaskDelayUntil(&CurrentControlTick, 1/portTICK_RATE_MS);
    }
}

/**
 * @name    ���̿��ƺ���
 * @brief   ���Ƶ����˶�,ͨ�������ٶ�ʵ�����������Ƶ����Ͷ�ǵĵ���
 * @param   vx:x���ٶ� vy:y���ٶ� vw:��ת�ٶ�
 * @retval  ��
 */
void Chassis_Control(float vx,float vy,float vw)
{

    
}

/**
 * @name ���̲�����ʼ��
 * @brief   ��ʼ�����̲���
 * @param   ��
 * @retval  ��
 */
void configChassis_ParaInit(void)
{


}
/**
 * @name    ���̹���״̬����
 * @brief   ���õ��̹���״̬
 * @param   st_data:���̲����ṹ�� state:����״̬
 * @retval  ��
 */
void Chassis_SetWorkState(Chassis_TypeDef* st_data,e_Chassis_State state)
{
	st_data->State = state;
}

/**
 * @name    �����˶�ģʽ����
 * @brief   ���õ����˶�ģʽ
 * @param   st_data:���̲����ṹ�� mode:�˶�ģʽ
 * @retval  ��
 */
static void Chassis_SetMode(Chassis_TypeDef *st_data,e_ChassisMotion_State mode)
{
    st_data->Mode = mode;

    switch(st_data->Mode)
    {
        case Chassis_Fix:
        {
            vx=vx_1;
			vy=vy_1;
			vw = vw_1;
                
			limit(vx,-CHASSIS_SPEED_MAX_X,CHASSIS_SPEED_MAX_X);
			limit(vy,-CHASSIS_SPEED_MAX_Y,CHASSIS_SPEED_MAX_Y);
        }break;
        case Chassis_Follow:
        {
            
        }break;
        case Chassis_NoFollow:
        {
            
        }break;
        case Chassis_Spin:
        {
            
        }break;
        case Chassis_AI:
        {

        }break;

        default:
        break;

    }
}
