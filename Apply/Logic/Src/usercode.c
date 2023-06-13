#include "usercode.h"		/* usercodeͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */

///////////////////////////////////////////////////////////////////////////////

/* �û��������� */

char Timeflag_200MS = RESET; //0.2��ʱ���־λ
char Timeflag_100MS = RESET; //0.1��ʱ���־λ
char Timeflag_Count1; //1S��ʱ���жϼ�����־λ
char Timeflag_Count2; //0.2S��ʱ���жϼ�����־λ
char Timeflag_500MS = RESET; //0.5��ʱ���־λ
char Timeflag_1S = RESET; //1��ʱ���־λ

double LX;
double LY;
double LZ;
double LALL;
double RX;
double RY;
double RZ;
double RALL;

/* �û��������� */

void Relay_Control(void); //�̵������ƺ���
void Receive_DMA(void);

///////////////////////////////////////////////////////////////////////////////

/* ���Բ��� */

void Test_Code(void); //���Գ���
uint8_t receive[10] ;
char receive11[20];
int time_rand; //�������������

///////////////////////////////////////////////////////////////////////////////

/* �û��߼����� */
void UserLogic_Code(void)
{
	Uplink_Data.Altimeter_Data = 98.6;
	Uplink_Data.Depthometer_Data = 252.3;
	
	Relay_Control();
	while(1)
	{
		Receive_DMA();
		TuikongData_Analysis();
		ShumeiData_Analysis();
		Manipulator_Analysis();

		CH438Q_Analysis(&Uplink_Data.Altimeter_Data, Uplink_Data.Lowvoltage_Data, Uplink_Data.Highvoltage_Data); //CH438Q�������ݻ�ȡ����
		Depthometer_Analysis(&Uplink_Data.Depthometer_Data);

		Downlink_Data.Altimeter_Data = Uplink_Data.Altimeter_Data;
		Downlink_Data.Depthometer_Data = Uplink_Data.Depthometer_Data;
		memcpy(Downlink_Data.Pose_Velocity_Data, &Shumei_buf[4], 24);
		memcpy(Downlink_Data.Cursor_Coordinate, &Shumei_buf[28], 4);

		if(Timeflag_100MS)
		{
			Mag_data_getL(&LX, &LY, &LZ, &LALL, &RX, &RY, &RZ, &RALL); 
			Uplink_Data.Magnetometer_L.X.f_data = LX;
			Uplink_Data.Magnetometer_L.Y.f_data = LY;
			Uplink_Data.Magnetometer_L.Z.f_data = LZ;
			Uplink_Data.Magnetometer_L.all.f_data = LALL;
			Uplink_Data.Magnetometer_R.X.f_data = RX;
			Uplink_Data.Magnetometer_R.Y.f_data = RY;
			Uplink_Data.Magnetometer_R.Z.f_data = RZ;
			Uplink_Data.Magnetometer_R.all.f_data = RALL;
			Timeflag_100MS = RESET;
		}
		if(Timeflag_200MS)
		{
			ShumeiData_Send();
			Timeflag_200MS = RESET;
			Timeflag_Count2 = RESET;
		}
		if(Timeflag_500MS) 
		{
			TuikongData_Send();
			Timeflag_500MS = RESET;
		}
		if(Timeflag_1S)
		{
			Timeflag_1S = RESET;
			Timeflag_Count1 = RESET;
			Highvoltage_Send();
			Depthometer_Send();
			Lowvoltage_Send();
			Manipulator_SendDate();
		}
	}
	
}

///////////////////////////////////////////////////////////////////////////////

/* �û��������� */
int size = 0;

void Relay_Control() //�̵������ƺ���
{
	ShengTong_OFF;
	Manipulator_OFF;
	CeSao_OFF;
	BDGPS_ON;
	Camera_OFF;
	Inertial_navigation_ON;
	P360_OFF;
	DVL_ON;
	Altimeter_OFF;
	UHF_ON;
	Front_Magnetometer_ON;
	Beiyong12V_OFF;
	
//	ShengTong_ON;
//	Manipulator_ON;
//	CeSao_ON;
//	BDGPS_ON;
//	Camera_ON;
//	Inertial_navigation_ON;
//	P360_ON;
//	DVL_ON;
//	Altimeter_ON;
//	UHF_ON;
//	Front_Magnetometer_ON;
//	Beiyong12V_ON;
	
//	ShengTong_OFF;
//	Manipulator_OFF;
//	CeSao_OFF;
//	BDGPS_OFF;
//	Camera_OFF;
//	Inertial_navigation_OFF;
//	P360_OFF;
//	DVL_OFF;
//	Altimeter_OFF;
//	UHF_OFF;
//	Front_Magnetometer_OFF;
//	Beiyong12V_OFF;
}

void Test_Code(void) 
{
//	//	printf("123");
//		
//	CH438_RecvDatas(CHIP1, 0, &receive11);
//	receive1=receive+1; 
//	Usart_SendString(&demoUart1, &receive11);	  
//	CH438_SendDatas(CHIP1, 0, &s_ucRxUart1_test, 1);
//	CH438_SendDatas(CHIP1, 0, (uint8_t*)&receive11, 1);
//			
//	Drv_Delay_Ms(1000);
//			
//	Mag_data_getL(&LX, &LY, &LZ, &allX, &RX, &RY, &RZ, &allY);
}



