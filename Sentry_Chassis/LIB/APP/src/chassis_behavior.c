#include "chassis_behavior.h"
#include "arm_math.h"

/************************�����趨************************/
#define CHASSIS_DISABLE 0
#define CHASSIS_SPEED_MAX_X 12//����X��������ٶ�3
#define CHASSIS_SPEED_MAX_Y 12 //����Y��������ٶ�3
#define CHASSIS_SPEED_MAX_W 0.009f //������ת���ٶ�����ٶ�

//���̲�������
#define CHASSIS_LENGTH 254      //���̳���һ��
#define CHASSIS_WIDTH 254       //���̿��һ��
#define WHEEL_PERIMETER 960       //�����ܳ�
#define CHASSIS_DECELE_RATIO  19 //������ٱ�
#define CHASSIS_CALI_ANGLE 0.f

//�궨�庯��
#define LIMIT_ANGLE(angle) ((angle) < 0 ? fmod((angle), 360) + 360 : fmod((angle), 360))
#define limit(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\

/***********************��������***********************/
Chassis_WhlVct_Typedef Vector_F;  //����
Chassis_WhlVct_Typedef Vector_B;  //����

extern bool TeamColor;
extern M6020_TypeDef P_stMotor_Gimbal_YawL; //��̨��yaw�����ṹ��
extern M6020_TypeDef P_stMotor_Gimbal_YawH; //��̨Сyaw�����ṹ��

Chassis_TypeDef P_stChassis = {Chassis_BlackOut};//���̲����ṹ��
/**
 * @name    ���̿�������
 * @brief   ͨ��ң������λ���Ƶ���ģʽ
 * @param   ��
 * @retval  ��
*/

float vx,vy,vw;         //�����ٶ�
float vx_1,vy_1,vw_1;   //����Ԥ�����ٶ�
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
                Chassis_SetMode(&P_stChassis,Chassis_NoFollow);//�˶�ģʽ����Ϊ���̸���

                vx = 0;
                vy = 0;
                vw = 0;
                countT = 0;
                
                    P_stChassis.RstPara.Initial_Yaw = 0;
                    P_stChassis.RstPara.Initial_Encoder = 0;  //��¼��ʼ������
                    P_stChassis.RstPara.Initial_Gyro = 0;       //��¼��ǰ������Yaw������
                    P_stChassis.RstPara.Pos_Diff = 0;        //��¼��ǰ��̨�����ǰ�����ĵĲ�ֵ
                    P_stChassis.RstPara.Converted_GyroYaw = 0;
                
            }break;

            case Middle:   //��������̨����Ϊ�������ƶ�             //Switch_BΪ�м䵲λʱ������Switch_C��ֵ�����ж�
            {
                switch(P_stRemoteData_Recv.Switch_C)
                {
                    case Down:  //ң��ģʽ
                    {
                        if(countT ++ < 1000)
                        {         
//                            P_stChassis.RstPara.Initial_Encoder = P_stMotor_Gimbal_Yaw.RecvData.Raw_Angle;  //��¼��ʼ������
//                            P_stChassis.RstPara.Initial_Gyro = P_stHi219m.Continuous_Yaw;       //��¼��ǰ������Yaw������
//                            P_stChassis.RstPara.Pos_Diff = P_stChassis.Cali.Cali_Yaw_180;        //��¼��ǰ��̨�����ǰ�����ĵĲ�ֵ
//                            
//                            P_stChassis.RstPara.Converted_GyroYaw = 
//                                            LIMIT_ANGLE(P_stChassis.RstPara.Initial_Gyro + P_stChassis.Cali.Cali_Yaw_180);
//                                                        //�����Ǽ��� ��ǰ��̨�����ǰ�����ĵĲ�ֵ Ϊ��ǰ��̨���� �ԽǶ�ֵȡģ
//                            P_stChassis.RstPara.Initial_Yaw = P_stChassis.RstPara.Converted_GyroYaw ;
                        P_stChassis.State = Chassis_BlackOut;
                        }
                        else
                        {
                            countT = 2600;
                            P_stChassis.State = Chassis_Working;
                            Chassis_SetMode(&P_stChassis,Chassis_Fix);//�˶�ģʽ����Ϊ���̲������ƶ�
                        }

                    }break;

                    case Middle: //����׼��������Ħ����
                    {
                        if(countT ++ < 1000)
                        {
//                            P_stChassis.RstPara.Initial_Encoder = P_stMotor_Gimbal_Yaw.RecvData.Raw_Angle;  //��¼��ʼ������
//                            P_stChassis.RstPara.Initial_Gyro = P_stHi219m.Continuous_Yaw;       //��¼��ǰ������Yaw������
//                            P_stChassis.RstPara.Pos_Diff = P_stChassis.Cali.Cali_Yaw_180;        //��¼��ǰ��̨�����ǰ�����ĵĲ�ֵ
//                            
//                            P_stChassis.RstPara.Converted_GyroYaw = 
//                                            LIMIT_ANGLE(P_stChassis.RstPara.Initial_Gyro + P_stChassis.Cali.Cali_Yaw_180);
//                                                        //�����Ǽ��� ��ǰ��̨�����ǰ�����ĵĲ�ֵ Ϊ��ǰ��̨���� �ԽǶ�ֵȡģ
//                            P_stChassis.RstPara.Initial_Yaw = P_stChassis.RstPara.Converted_GyroYaw ;

						P_stChassis.State = Chassis_BlackOut;
                        }
                        else
                        {
                            countT = 2600;
                            P_stChassis.State = Chassis_Working;
                            Chassis_SetMode(&P_stChassis,Chassis_Navigator);//�˶�ģʽ����Ϊ���̲�����
                        }
                    }break;

                    case Up:    //����ģʽ
                    {
                        if(countT++ < 1000)
						{									
//                            P_stChassis.RstPara.Initial_Encoder = P_stMotor_Gimbal_Yaw.RecvData.Raw_Angle;  //��¼��ʼ������
//                            P_stChassis.RstPara.Initial_Gyro = P_stHi219m.Continuous_Yaw;       //��¼��ǰ������Yaw������
//                            P_stChassis.RstPara.Pos_Diff = P_stChassis.Cali.Cali_Yaw_180;        //��¼��ǰ��̨�����ǰ�����ĵĲ�ֵ
//                            
//                            P_stChassis.RstPara.Converted_GyroYaw = 
//                                            LIMIT_ANGLE(P_stChassis.RstPara.Initial_Gyro + P_stChassis.Cali.Cali_Yaw_180);
//                                                        //�����Ǽ��� ��ǰ��̨�����ǰ�����ĵĲ�ֵ Ϊ��ǰ��̨���� �ԽǶ�ֵȡģ
//                            P_stChassis.RstPara.Initial_Yaw = P_stChassis.RstPara.Converted_GyroYaw ;
						P_stChassis.State = Chassis_BlackOut;
						}
						else
						{
							countT = 2600;
							P_stChassis.State = Chassis_Working;
							Chassis_SetMode(&P_stChassis,Chassis_Navigator);//�˶�ģʽ����Ϊ���̸���
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
//                    P_stChassis.RstPara.Initial_Yaw = 0;
//                    P_stChassis.RstPara.Initial_Encoder = 0;  //��¼��ʼ������
//                    P_stChassis.RstPara.Initial_Gyro = 0;       //��¼��ǰ������Yaw������
//                    P_stChassis.RstPara.Pos_Diff = 0;        //��¼��ǰ��̨�����ǰ�����ĵĲ�ֵ
//                    P_stChassis.RstPara.Converted_GyroYaw = 0;    
                            
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
//                    P_stChassis.RstPara.Initial_Yaw = 0;
//                    P_stChassis.RstPara.Initial_Encoder = 0;  //��¼��ʼ������
//                    P_stChassis.RstPara.Initial_Gyro = 0;       //��¼��ǰ������Yaw������
//                    P_stChassis.RstPara.Pos_Diff = 0;        //��¼��ǰ��̨�����ǰ�����ĵĲ�ֵ
//                    P_stChassis.RstPara.Converted_GyroYaw = 0;

							P_stChassis.State = Chassis_BlackOut;				        
                        }
				        else
				        {
					        countT = 2600;
					        P_stChassis.State = Chassis_Working;
					        Chassis_SetMode(&P_stChassis,Chassis_AI);//�˶�ģʽ����ΪAIģʽ
				        }
                    }break;

                    case Up:    //AIģʽ
                    {
                        if(countT++ < 1000)
				        {		
//                    P_stChassis.RstPara.Initial_Yaw = 0;
//                    P_stChassis.RstPara.Initial_Encoder = 0;  //��¼��ʼ������
//                    P_stChassis.RstPara.Initial_Gyro = 0;       //��¼��ǰ������Yaw������
//                    P_stChassis.RstPara.Pos_Diff = 0;        //��¼��ǰ��̨�����ǰ�����ĵĲ�ֵ
//                    P_stChassis.RstPara.Converted_GyroYaw = 0;

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
    static float32_t chassis_rudder_angle[2];       //������Ŀ��Ƕ�
    static float32_t chassis_rudder_crtangle[2];    //�����ֵ�ǰ�Ƕ�
    static float32_t chassis_rudder_cvtangle[2];    //�����־ͽ�ת��Ŀ��Ƕ�
    /*��¼��ǰ�������Ƕ�*/
    chassis_rudder_crtangle[0] = P_stMotor_RudderF.RecvData.Custom_Angle;
    chassis_rudder_crtangle[1] = P_stMotor_RudderB.RecvData.Custom_Angle;

    /*6020������Ŀ��Ƕȼ��� if((vy - vw * SIN45 != 0) && (vy + vw * COS45 != 0))*/
    if(vx != 0  && vy != 0 && vw != 0)     //��֤������Ϊ��
    {
        chassis_rudder_angle[0] = atan2(vx + vw * SIN45,vy + vw * COS45);
        chassis_rudder_angle[1] = atan2(vx - vw * COS45,vy - vw * SIN45);
    }
    else    //�����ֽǶ�Ĭ�ϳ������ҷ�
    {
        chassis_rudder_angle[0] = 0;
        chassis_rudder_angle[1] = 0;
    }
    /*3508������Ŀ���ٶȼ���*/
    
}

/**
 * @name ���̲�����ʼ��
 * @brief   ��ʼ�����̲���
 * @param   ��
 * @retval  ��
 */
void configChassis_ParaInit(void)
{
    /*�������Զ������ֵ����*/
    P_stMotor_RudderF.RecvData.Custom_Angle_Zero = 165.62f;//��ǰ
    P_stMotor_RudderB.RecvData.Custom_Angle_Zero = 0.f;//�Һ�
    /*���̽ṹ�������ʼ��*/
    
    /*���̶����֡�������pid������ʼ��*/
    
    
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
            vx = vx_1;
			vy = vy_1;
			vw = vw_1;
                
			limit(vx,-CHASSIS_SPEED_MAX_X,CHASSIS_SPEED_MAX_X);
			limit(vy,-CHASSIS_SPEED_MAX_Y,CHASSIS_SPEED_MAX_Y);
            limit(vw,-CHASSIS_SPEED_MAX_W,CHASSIS_SPEED_MAX_W);
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


static void Chassis_Cali_Calc(Chassis_TypeDef* st_data)   //���̾�����ֵУ׼����
{
//        P_stChassis.Cali.Cali_Yaw_180 = (float)(((P_stMotor_Gimbal_Yaw.RecvData.Raw_Angle - CHASSIS_CALI_ANGLE) / 360.0f) * 360.0);
    
        if (P_stChassis.Cali.Cali_Yaw_180 > 180)    P_stChassis.Cali.Cali_Yaw_180 -= 360;  //����Χ������-180~+180��
}
