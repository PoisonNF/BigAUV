#include "usercode.h"
#include "drv_hal_conf.h"
#include "task_conf.h"
#include "bsp_io.h"

///////////////////////////////////////////////////////////////////////////////

/* 用户变量定义 */

union float_data //发送float类型数据 4字节
{
    float f_data;
    uint8_t byte[4];
};

typedef struct{
	union float_data X; //磁力仪X值
	union float_data Y; //磁力仪Y值
	union float_data Z; //磁力仪Z值
	union float_data all; //磁力仪总场
}Magnetometer_Data;

struct {
	float Depthometer_Data; //深度计数据
	float Altimeter_Data; //高度计数据
	uint8_t Manipulator_Data[7]; //机械手数据
	Magnetometer_Data Magnetometer_L; //左梯度磁力仪数据
	Magnetometer_Data Magnetometer_R; //右梯度磁力仪数据
	uint8_t Lowvoltage_Data[2]; //电池低压数据
	uint8_t Highvoltage_Data[2]; //电池高压数据
	uint8_t Motor_Status[2]; //推进器状态
	uint8_t Other_Status[2]; //其他状态，即重心/浮心/舱门/漏水状态
	uint8_t Relay_Status[2]; //继电器状态
}Uplink_Data; //上行数据内容，发送至树莓派

uint8_t Tuikong_buf[50]; //推控舱串口接收缓冲区
uint8_t Tuikong_flag = RESET; //推控舱串口数据接收完成标志
uint8_t Shumei_buf[50]; //树莓派串口接收缓冲区
uint8_t Shumei_flag = RESET; //树莓派串口数据接收完成标志
uint8_t Depthometer_buf[15]; //深度计串口接收缓冲区
uint8_t Depthometer_flag = RESET; //深度计串口数据接收完成标志
uint8_t CH438Q_buf[50]; //CH438Q串口数据接收缓冲区
uint8_t CH438Q_flag = RESET; //CH438Q串口数据接收完成标志
uint8_t CH438Q_NUM = 10; //CH438Q串口号
uint8_t Manipulator_flag = RESET; //机械手工作标志位
uint8_t Manipulator_Recvflag = RESET; //机械手串口数据接收完成标志
uint8_t Manipulator_buf[15]; //机械手串口接收缓冲区
uint8_t Hatchdoor_flag = RESET; //舱门开关标志位

char Timeflag_200MS = RESET; //0.2秒时间标志位
char Timeflag_100MS = RESET; //0.1秒时间标志位
char Timeflag_Count1; //1S定时器中断计数标志位
char Timeflag_Count2; //0.2S定时器中断计数标志位
char Timeflag_500MS = RESET; //0.5秒时间标志位
char Timeflag_1S = RESET; //1秒时间标志位

/* 需要发送的数组长度定义需大于字节数，因为Usart_SendString通过识别空字符结束 */
uint8_t Tuikong_SendData[30]; //推控舱下行数据发送 数据28字节
uint8_t Shumei_RecvData[30] ; //树莓派下行数据接收 数据24字节
uint8_t Shumei_SendData_Int[50] ; //树莓派上行数据发送 数据50字节
uint8_t Shumei_SendData_Float[30] ; //树莓派上行数据发送 数据24字节
uint8_t Shumei_SendCmd[5]; //树莓派上行命令发送 数据3字节
uint8_t Manipulator_SendCmd[8] = {'@', 'C', '0', '0', '0', '0', '$'}; //机械手命令发送
uint8_t Depthometer_Instruction1[8] = {0x01, 0x03, 0x00, 0x04, 0x00, 0x01, 0xC5, 0xCB}; //深度计指令1 读取压力数据
uint8_t Depthometer_Instruction2[8] = {0x01, 0x03, 0x00, 0x03, 0x00, 0x01, 0x74, 0x0A}; //深度计指令2 读取小数位数
uint8_t Lowvoltage_Instruction[7] = {0xDD, 0xA5, 0x03, 0x00, 0xFF, 0xFD, 0x77}; //低压数据获取指令
uint8_t Highvoltage_Instruction[8] = {0x01, 0x03, 0x00, 0x01, 0x00, 0x02, 0x95, 0xCB}; //高压数据获取指令

enum{
	Notask_State = 'A', //无任务
	Progress_State, //任务进行中
	Accomplish_State, //任务完成
	Abnormal_State, //任务执行异常
}; //机械手工作状态

enum{
	Notask = 'A', //无任务
	Extend, //伸出
	Release, //设备释放
	Grab, //视觉自主抓取
	Reset, //复位
	Back, //收回
}; //机械手任务类型

uint8_t Manipulator_Task = Notask; //机械手当前任务类型
uint8_t Manipulator_Uptask=100; //上行命令机械手任务类型

///////////////////////////////////////////////////////////////////////////////

/* 用户函数声明 */

void TuikongData_Analysis(void); //推控舱数据解析
void ShumeiData_Analysis(void); //树莓派数据解析
void TuikongData_Send(void); //下行数据发送函数，即向推控舱数据定时发送 0.5秒发送一次到推控舱
void ShumeiData_Send(void); //上行数据发送函数，即向树莓派数据定时发送 1秒发送一次到树莓派
void ShumeiCmd_Send(void); //上行命令发送函数，即向树莓派数据应答
void MotorStatus_Analysis(void); //推进器状态分析函数
void Depthometer_Analysis(void); //深度计数据分析函数
void Depthometer_Send(void); //深度计指令发送函数
void Altimeter_Analysis(void); //高度计数据分析函数
void CH438Q_Analysis(void); //CH438Q串口数据分析函数
void Highvoltage_Send(void); //高压监测指令发送函数
void Lowvoltage_Send(void); //低压监测指令发送函数
void Relay_Control(void); //继电器控制函数
void Manipulator_SendDate(void); //机械手指令发送函数
void Manipulator_Analysis(void); //机械手数据分析函数

///////////////////////////////////////////////////////////////////////////////

/* 测试部分 */

void Test_Code(void); //测试程序
uint8_t receive[10] ;
char receive11[20];
int time_rand; //随机数生成种子
double LX;
double LY;
double LZ;
double LALL;
double RX;
double RY;
double RZ;
double RALL;

///////////////////////////////////////////////////////////////////////////////

/* 用户逻辑代码 */

void UserLogic_Code(void)
{
//	srand(time_rand);	
	int i;
//	for(i=0; i<24; i++)
//	{
//		Shumei_SendData_Int[i] = 0x31;
////		Shumei_SendData[i] = rand()%(40-30) + 30;
//	}
	
	for(i=0; i<24; i++)
	{
		Shumei_RecvData[i] = 0x31;
	}
	
//	Uplink_Data.Magnetometer_L.X.f_data = 35523.5;
//	Uplink_Data.Magnetometer_L.Y.f_data = 56675.8;
//	Uplink_Data.Magnetometer_L.Z.f_data = 43545.7;
//	Uplink_Data.Magnetometer_R.X.f_data = 45334.8;
//	Uplink_Data.Magnetometer_R.Y.f_data = 64435.4;
//	Uplink_Data.Magnetometer_R.Z.f_data = 56684.1;
//	Uplink_Data.Depthometer_Data = 254.7;
	Manipulator_Uptask = 'A';
	Uplink_Data.Altimeter_Data = 0;
	
	Relay_Control();
	
	while(1)
	{
		TuikongData_Analysis();
		ShumeiData_Analysis();
		Depthometer_Analysis();
		CH438Q_Analysis();
		Manipulator_Analysis();
		
		if(Timeflag_100MS)
		{
//			Mag_data_getL((double *)&Uplink_Data.Magnetometer_L.X.f_data, (double *)&Uplink_Data.Magnetometer_L.Y.f_data, (double *)&Uplink_Data.Magnetometer_L.Z.f_data, (double *)&Uplink_Data.Magnetometer_L.all.f_data, 
//				(double *)&Uplink_Data.Magnetometer_R.X.f_data, (double *)&Uplink_Data.Magnetometer_R.Y.f_data, (double *)&Uplink_Data.Magnetometer_R.Z.f_data, (double *)&Uplink_Data.Magnetometer_R.all.f_data); //0.1秒获取一次左右梯度磁力仪数据
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
//			TuikongData_Send();
			Timeflag_500MS = RESET;
		}
		if(Timeflag_1S)
		{
			Timeflag_1S = RESET;
			Timeflag_Count1 = RESET;
			Highvoltage_Send();
			Depthometer_Send();
			Lowvoltage_Send();
		}
	}
}	

///////////////////////////////////////////////////////////////////////////////

/* 用户函数定义 */

void TuikongData_Send(void) //下行数据发送函数，即向推控舱数据定时发送 0.5秒发送一次到推控舱
{
	Tuikong_SendData[24] = Uplink_Data.Depthometer_Data*10 / 256; //深度计数据
	Tuikong_SendData[25] = (int)(Uplink_Data.Depthometer_Data*10) % 256;
	Tuikong_SendData[26] = Uplink_Data.Altimeter_Data*100 / 256; //高度计数据
	Tuikong_SendData[27] = (int)(Uplink_Data.Altimeter_Data*100) % 256;
	Tuikong_SendData[28] = 0x45;
	memcpy(Tuikong_SendData, Shumei_RecvData, 24);
	Usart_SendString(&demoUart2, (uint8_t *)"@DD");
	Drv_Uart_Transmit(&demoUart2, Tuikong_SendData, 29);
	Usart_SendString(&demoUart2, (uint8_t *)"$");
}

void ShumeiData_Send(void) //上行数据发送函数，即向树莓派数据定时发送 1秒发送一次到树莓派
{
	Shumei_SendData_Int[0] = Uplink_Data.Depthometer_Data*10 / 256; //深度计数据
	Shumei_SendData_Int[1] = (int)(Uplink_Data.Depthometer_Data*10) % 256;
	Shumei_SendData_Int[2] = Uplink_Data.Altimeter_Data*100 / 256; //高度计数据
	Shumei_SendData_Int[3] = (int)(Uplink_Data.Altimeter_Data*100) % 256;
	Shumei_SendData_Int[12] = Uplink_Data.Motor_Status[0]; //9号推进器状态
	Shumei_SendData_Int[13] = Uplink_Data.Motor_Status[1]; //1-8号推进器状态
	
	memcpy(&Shumei_SendData_Float[0], &Uplink_Data.Magnetometer_L.X.byte, 4);
	memcpy(&Shumei_SendData_Float[4], &Uplink_Data.Magnetometer_L.Y.byte, 4);
	memcpy(&Shumei_SendData_Float[8], &Uplink_Data.Magnetometer_L.Z.byte, 4);
	memcpy(&Shumei_SendData_Float[12], &Uplink_Data.Magnetometer_R.X.byte, 4);
	memcpy(&Shumei_SendData_Float[16], &Uplink_Data.Magnetometer_R.Y.byte, 4);
	memcpy(&Shumei_SendData_Float[20], &Uplink_Data.Magnetometer_R.Z.byte, 4);
	
	Usart_SendString(&demoUart1, (uint8_t *)"@DUP");
	Drv_Uart_Transmit(&demoUart1, Shumei_SendData_Int, 8);
	Drv_Uart_Transmit(&demoUart1, Shumei_SendData_Float, 24);
	Drv_Uart_Transmit(&demoUart1, &Shumei_SendData_Int[8], 10);
	Usart_SendString(&demoUart1, (uint8_t *)"$");	
	
//	Usart_SendString(&demoUart2, (uint8_t *)"@DUP");
//	Drv_Uart_Transmit(&demoUart2, Shumei_SendData_Int, 8);
//	Drv_Uart_Transmit(&demoUart2, Shumei_SendData_Float, 24);
//	Drv_Uart_Transmit(&demoUart2, &Shumei_SendData_Int[8], 10);
//	Usart_SendString(&demoUart2, (uint8_t *)"$");	
}

void ShumeiCmd_Send(void) //上行命令发送函数，即向树莓派数据应答
{
	memcpy(Shumei_SendCmd, &Shumei_buf[1], 3);
	Usart_SendString(&demoUart1, (uint8_t *)"@ACK");
	Usart_SendString(&demoUart1, (uint8_t *)Shumei_SendCmd); 
	Usart_SendString(&demoUart1, (uint8_t *)"$");	
}

void TuikongData_Analysis(void) //推控舱数据解析
{
	if(Tuikong_flag == SET)
	{
		switch(Tuikong_buf[1])
		{
			//应答
			case 'A': //推控舱应答
				Usart_SendString(&demoUart1, Tuikong_buf);
				break;
			//状态
			case 'S': //推控舱上行数据
				if(Tuikong_buf[23] == 0xF0)
				{
					Hatchdoor_flag = SET;
				}
				else if(Tuikong_buf[23] == 0x00)
				{
					Hatchdoor_flag = RESET;
				}
				MotorStatus_Analysis();
//				Usart_SendString(&demoUart2, Uplink_Data.Motor_Status); 
				break;
			
			default:
				
				break;
		}
//		Usart_SendString(&demoUart2, Tuikong_buf); 
		Tuikong_flag = RESET;
	}
}
	
void ShumeiData_Analysis(void) //树莓派数据解析
{
	if(Shumei_flag == SET)
	{
		switch(Shumei_buf[1])
		{
			//应答
			case 'R': //电源控制
				ShumeiCmd_Send();
				switch(Shumei_buf[2])
				{
					case 'S': //单一模式
						
						break;
					
					case 'A': //整体模式
						
						break;
				}
			break;
			//状态
				case 'J': //机械手控制
				ShumeiCmd_Send();
				Manipulator_flag = SET;
				Manipulator_Uptask = Shumei_buf[3];
//				switch(Shumei_buf[3])
//				{
//					
//					case 'A':
//						
//						break;
//					
//					case 'B':
//						
//						break;
//					
//					case 'C':
//						
//						break;
//					
//					case 'D':
//						
//						break;
//					
//					case 'E':
//						
//						break;
//					
//					case 'F':
//						
//						break;
//					
//					default:
//				
//						break;
//					
//				}
				break;
			
			case 'M': //运动控制
				ShumeiCmd_Send();
				Usart_SendString(&demoUart2, Shumei_buf);
				switch(Shumei_buf[2])
				{
					case 'T': //测试模式
						
						break;
					
					case 'P': //平动模式
						
						break;
					
					case 'R': //转动模式
						
						break;
					
					case 'A': //自动模式
						
						break;
					
					case 'Y': //摇杆模式
						
						break;
				}
			break;
			
			case 'G': //重心调节
				ShumeiCmd_Send();
				Usart_SendString(&demoUart2, Shumei_buf);
				break;
			
			case 'B': //浮力调节
				ShumeiCmd_Send();
				Usart_SendString(&demoUart2, Shumei_buf);
				break;
			
			case 'E': //应急控制
				ShumeiCmd_Send();
				Usart_SendString(&demoUart2, Shumei_buf);
				break;
				
			case 'T': //时间同步
				ShumeiCmd_Send();
				Usart_SendString(&demoUart2, Shumei_buf);
				break;
			
			case 'D': //舱门控制 或 树莓派下行数据
				switch(Shumei_buf[2])
				{
					case 'T': //舱门控制 测试模式
						ShumeiCmd_Send();
						Usart_SendString(&demoUart2, Shumei_buf);
						break;
					
					case 'A': //舱门控制 自动模式
						ShumeiCmd_Send();
						Usart_SendString(&demoUart2, Shumei_buf);
						break;
					
					case 'D': //树莓派下行数据
						memcpy(Shumei_RecvData, &Shumei_buf[4], 24);
						break;
				}
				break;
			
			default:
				
				break;
		}
//		Usart_SendString(&demoUart2, Shumei_buf);
		Shumei_flag = RESET;
	}
}

//int Motor_Speed[10]; //推进器速度
void MotorStatus_Analysis(void) //推进器状态分析函数
{
	int Motor_Speed[10]; //推进器速度
	uint8_t i = 0;
	for(i = 0; i<9; i++)
	{
		Motor_Speed[i] = Tuikong_buf[i*2+3]*256 +Tuikong_buf[i*2+4];
		if(i<8)
		{
			if(Motor_Speed[i] < 5000 && Motor_Speed[i] > 500)
				Uplink_Data.Motor_Status[1] |= (1 << i);
			else
				Uplink_Data.Motor_Status[1] &= ~(1 << i);
		}
		else
		{
			if(Motor_Speed[i] < 5000 && Motor_Speed[i] > 500) 
				Uplink_Data.Motor_Status[0] |= (1 << (i-8));
			else
				Uplink_Data.Motor_Status[0] &= ~(1 << (i-8));
		}	
	}
}

void Manipulator_Analysis(void)//机械手数据分析函数
{
	if(Manipulator_Recvflag == SET)
	{
		switch(Manipulator_buf[3])
		{
			case Notask:
				if(Manipulator_Uptask == 'A' || Manipulator_Uptask == 'B' )
				{
					Usart_SendString(&demoUart2, (uint8_t *)"@HD");
					Usart_SendString(&demoUart2, (uint8_t *)"1"); 
					Usart_SendString(&demoUart2, (uint8_t *)"0"); 
					Usart_SendString(&demoUart2, (uint8_t *)"$");	
				}
				if(Hatchdoor_flag)
				{
					Manipulator_SendCmd[2] = 'D'; //舱门已开（可以作业/收回手）
					Manipulator_SendDate();
				}
				break;
			case Extend:
				if(Manipulator_Uptask == 'A' && Manipulator_buf[2] == Accomplish_State)
				{
					Manipulator_SendCmd[2] = 'A';
					Manipulator_SendDate();
				}
				else if(Manipulator_Uptask == 'B' && Manipulator_buf[2] == Accomplish_State)
				{
					Manipulator_SendCmd[2] = 'B';
					Manipulator_SendDate();
				}
				break;
			case Release:
				if(Manipulator_buf[2] == Accomplish_State)
				{
					Manipulator_SendCmd[2] = 'C';
					Manipulator_SendDate();
				}
				break;
			case Grab:
				if(Manipulator_buf[2] == Accomplish_State)
				{
					Manipulator_SendCmd[2] = 'C';
					Manipulator_SendDate();
				}
				break;
			case Reset:
				if(Manipulator_buf[2] == Accomplish_State)
				{
					Usart_SendString(&demoUart2, (uint8_t *)"@HD");
					Usart_SendString(&demoUart2, (uint8_t *)"0"); 
					Usart_SendString(&demoUart2, (uint8_t *)"0"); 
					Usart_SendString(&demoUart2, (uint8_t *)"$");
				}
				if(!Hatchdoor_flag)
				{
					Manipulator_SendCmd[2] = 'E';
					Manipulator_SendDate();
					Manipulator_Uptask =100;
				}
				break;
			case Back:
				if(Manipulator_buf[2] == Accomplish_State)
				{
					Usart_SendString(&demoUart1, (uint8_t *)"@HD");
					Usart_SendString(&demoUart1, (uint8_t *)"0"); 
					Usart_SendString(&demoUart1, (uint8_t *)"0"); 
					Usart_SendString(&demoUart1, (uint8_t *)"$");
				}
				if(!Hatchdoor_flag)
				{
					Manipulator_SendCmd[2] = 'E';
					Manipulator_SendDate();
					Manipulator_Uptask =100;
				}
				break;
			default:
				break;
		}
		Manipulator_Recvflag = RESET;
	}
}

void Depthometer_Analysis() //深度计数据分析函数
{
	if(Depthometer_flag == SET)
	{
		if(Depthometer_buf[0] == 0x01 && Depthometer_buf[1] == 0x03 && Depthometer_buf[2] == 0x02)
		{
			Uplink_Data.Depthometer_Data = (Depthometer_buf[3]*256 + Depthometer_buf[4] - 10)*0.1;
		}
		Depthometer_flag = RESET;
	}
}

void CH438Q_Analysis() //CH438Q串口数据分析函数
{
	if(CH438Q_flag == SET)
	{
		switch(CH438Q_NUM)
		{
			case 0: //高度计
				Uplink_Data.Altimeter_Data = (CH438Q_buf[0] - 48)*100 + (CH438Q_buf[1] - 48)*10 + (CH438Q_buf[2] - 48) + (CH438Q_buf[4] - 48)*0.1 + (CH438Q_buf[5] - 48)*0.01;
				break; 
			case 1: //低压监测
				Uplink_Data.Lowvoltage_Data[0] = (CH438Q_buf[4]*256 + CH438Q_buf[5])*10; //单位V
				Uplink_Data.Lowvoltage_Data[1] = (CH438Q_buf[6]*256 + CH438Q_buf[7])*10; //单位A
				break;
			case 2: //高压监测
//				Uplink_Data.Highvoltage_Data[0] = 
//				Uplink_Data.Highvoltage_Data[1] = 
				break;
			default:
				
				break;
		}
		CH438Q_flag = RESET;
	}
}

void Depthometer_Send() //深度计指令发送函数
{
	Depthometer_RS485_Send;
	Drv_Delay_Ms(2);
	Drv_Uart_Transmit(&demoUart4, Depthometer_Instruction1, 8);
	Drv_Delay_Ms(1);
	Depthometer_RS485_Recive;
}

void Lowvoltage_Send() //低压监测指令发送函数
{
	Lowvoltage_RS485_Send;
	Drv_Delay_Ms(2);
	CH438_SendDatas(CHIP1, 1, Lowvoltage_Instruction, 7);
	Drv_Delay_Ms(2);
	Lowvoltage_RS485_Recive;
}

void Highvoltage_Send() //高压监测指令发送函数
{
	Highvoltage_RS485_Send;
	Drv_Delay_Ms(2);
	CH438_SendDatas(CHIP1, 2, Highvoltage_Instruction, 8);
	Drv_Delay_Ms(2);
	Highvoltage_RS485_Recive;
}

void Manipulator_SendDate()//机械手指令发送函数
{
	Manipulator_RS485_Send;
	Drv_Delay_Ms(2);
	Drv_Uart_Transmit(&demoUart3, Manipulator_SendCmd, 8);
	Drv_Delay_Ms(2);	
	Manipulator_RS485_Recive;
}

void Relay_Control() //继电器控制函数
{
	ShengTong_OFF;
	Manipulator_OFF;
	CeSao_ON;
	BDGPS_ON;
	Camera_OFF;
	Inertial_navigation_ON;
	P360_OFF;
	DVL_ON;
	Altimeter_OFF;
	UHF_OFF;
	Beiyong24V_OFF;
	Beiyong12V_OFF;
	
	
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
//	Beiyong24V_OFF;
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


