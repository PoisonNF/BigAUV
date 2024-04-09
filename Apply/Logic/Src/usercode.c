#include "usercode.h"		/* usercode头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

///////////////////////////////////////////////////////////////////////////////

/* 用户变量定义 */

char Timeflag_200MS = RESET; //0.2秒时间标志位
char Timeflag_100MS = RESET; //0.1秒时间标志位
char Timeflag_Count1; //1S定时器中断计数标志位
char Timeflag_Count2; //0.2S定时器中断计数标志位
char Timeflag_500MS = RESET; //0.5秒时间标志位
char Timeflag_800MS = RESET; //0.8秒时间标志位
char Timeflag_1S = RESET; //1秒时间标志位
char Timeflag_2S = RESET; //2秒时间标志位

double LX;
double LY;
double LZ;
double LALL;
double RX;
double RY;
double RZ;
double RALL;

uint8_t ShumeiIsLive = 0;	//判断树莓派存活的计数器
uint8_t ShumeiIsLiveLast = 0;	//判断树莓派存活的计数器的上一帧

/* 用户函数声明 */

void Relay_Control(void); //继电器控制函数
void ShumeiLiveCheck(void);	//树莓派存活检测函数

///////////////////////////////////////////////////////////////////////////////

/* 测试部分 */

void Test_Code(void); //测试程序
uint8_t receive[10] ;
char receive11[20];
int time_rand; //随机数生成种子

///////////////////////////////////////////////////////////////////////////////

/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	Uplink_Data.Altimeter_Data = 98.6;
	Uplink_Data.Depthometer_Data = 252.3;
	Uplink_Data.Manipulator_ErrorState = '0';
	Uplink_Data.Manipulator_TaskType = '0';
	Uplink_Data.Manipulator_WorkState = '0';
	Uplink_Data.Highvoltage_Data[0] = '0';
	Uplink_Data.Highvoltage_Data[0] = '0';
	Uplink_Data.Lowvoltage_Data[0] = '0';
	Uplink_Data.Lowvoltage_Data[0] = '0';
	
	for(int i = 0; i < 18; i++){
		Uplink_Data.Motor_Turning_State[i] = 0x00 ;
	}
	
	Relay_Control();
	while(1)
	{
		Receive_DMA();
		TuikongData_Analysis();
		ShumeiData_Analysis();
		Manipulator_Analysis();

		CH438Q_Analysis(&Uplink_Data.Altimeter_Data, Uplink_Data.Lowvoltage_Data, Uplink_Data.Highvoltage_Data); //CH438Q串口数据获取函数
		Depthometer_Analysis(&Uplink_Data.Depthometer_Data);

		Downlink_Data.Altimeter_Data = Uplink_Data.Altimeter_Data;
		Downlink_Data.Depthometer_Data = Uplink_Data.Depthometer_Data;

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
        
        ShumeiLiveCheck();  //树莓派存活检测函数
        
		if(Timeflag_200MS)
		{
//			ShumeiData_Send();
			Timeflag_200MS = RESET;
			Timeflag_Count2 = RESET;
		}
		if(Timeflag_500MS) 
		{
			TuikongData_Send();
            ShumeiData_Send();
			Timeflag_500MS = RESET;
			Depthometer_Send();
		}
		if(Timeflag_800MS) 
		{
			Timeflag_800MS = RESET;
			Highvoltage_Send();
		}
		if(Timeflag_1S)
		{
			Timeflag_1S = RESET;
			Timeflag_Count1 = RESET;
			Lowvoltage_Send();
		}
	}
	
}

///////////////////////////////////////////////////////////////////////////////

/* 用户函数定义 */
int size = 0;

void Relay_Control() //继电器控制函数
{
	ShengTong_OFF;
	Manipulator_OFF;
	CeSao_OFF;
	BDGPS_ON;
	Camera_ON;
	Inertial_navigation_ON;
	P360_OFF;
	DVL_OFF;
	Altimeter_ON;
	UHF_ON;
	Front_Magnetometer_OFF;
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

uint8_t TKCResponed[50];	//推控舱回复存储数组
uint8_t TKCResponedNum;		//推控舱回复长度
uint8_t StopCMD[6] = "@MAS0$";

void ShumeiLiveCheck(void)
{
	if(Timeflag_2S)
	{
		Timeflag_2S = RESET;

		//上一帧计数器等于本次，说明树莓派断连，给推控舱发停止命令
		if(ShumeiIsLiveLast == ShumeiIsLive)	
		{
			Drv_Timer_Disable(&tTimer6);	//关闭定时器
			while(!TuikongStopFlag)
			{
                
                if(Timeflag_200MS) 
                {
                    printf("sikong\r\n");
                    Drv_Uart_Transmit(&tTKC_Uart,StopCMD, 6);	//向推控舱发送@MAS0$
                    Timeflag_200MS = RESET;
                }
                
                //等待推控舱的回应
                // Receive_DMA();
                // TuikongData_Analysis();

//				TKCResponedNum = Drv_Uart_Receive_DMA(&tTKC_Uart,TKCResponed);
//				if(TKCResponedNum && TKCResponed[0] == '@' && TKCResponed[1] == 'A')
//                //if(TKCResponedNum == 8)
//				{
//                    printf("TKCResponedNum %d\r\n",TKCResponedNum);
//					Drv_Uart_Transmit(&tSMP_Uart, TKCResponed, 8);

//					printf("shoudao!\r\n");
//					TuikongStopFlag = SET;      

//					Drv_Timer_Enable(&tTimer6);
//				
//					//两个计数器设置为相同的值
//					ShumeiIsLiveLast = 0;	
//					ShumeiIsLive = 1;
//					break;        					
//				}

                //说明推控舱停止运转恢复正常
				// if(TuikongStopFlag)
				// {
				// 	TuikongStopFlag = RESET;
				// 	Drv_Timer_Enable(&tTimer6);
					
				// 	//两个计数器设置为相同的值
				// 	ShumeiIsLiveLast = 0;	
				// 	ShumeiIsLive = 0;
				// 	break;
				// }
			}
		}
		else	//连接没有问题，跳过
		{
			ShumeiIsLiveLast = ShumeiIsLive;	//将本次计数值转存
		}
	}
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



