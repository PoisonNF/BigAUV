#include "task_conf.h"

//USART1串口接收缓冲区
/* 接收一级缓冲 */
#define Rx1_BUFFER_SIZE 	1
static uint8_t s_ucRxBufferUart1[Rx1_BUFFER_SIZE] = {0};
/* 二级缓冲 */
#define Rx1_DATA_LENTH 		100
static uint8_t s_ucRxUart1[Rx1_DATA_LENTH] = {0};
static uint16_t s_ucCntUart1 = 0;	/* 缓冲区计数器 */

//USART2串口接收缓冲区
/* 接收一级缓冲 */
#define Rx2_BUFFER_SIZE 	1
static uint8_t s_ucRxBufferUart2[Rx2_BUFFER_SIZE] = {0};
/* 二级缓冲 */
#define Rx2_DATA_LENTH 		100
static uint8_t s_ucRxUart2[Rx2_DATA_LENTH] = {0};
static uint16_t s_ucCntUart2 = 0;	/* 缓冲区计数器 */

//USART3串口接收缓冲区
/* 接收一级缓冲 */
#define Rx3_BUFFER_SIZE 	1
static uint8_t s_ucRxBufferUart3[Rx3_BUFFER_SIZE] = {0};
/* 二级缓冲 */
#define Rx3_DATA_LENTH 		100
static uint8_t s_ucRxUart3[Rx3_DATA_LENTH] = {0};
static uint16_t s_ucCntUart3 = 0;	/* 缓冲区计数器 */

//USART4串口接收缓冲区
/* 接收一级缓冲 */
#define Rx4_BUFFER_SIZE 	1
static uint8_t s_ucRxBufferUart4[Rx4_BUFFER_SIZE] = {0};
/* 二级缓冲 */
#define Rx4_DATA_LENTH 		20
static uint8_t s_ucRxUart4[Rx4_DATA_LENTH] = {0};
static uint16_t s_ucCntUart4 = 0;	/* 缓冲区计数器 */

//USART5串口接收缓冲区
/* 接收一级缓冲 */
#define Rx5_BUFFER_SIZE 	1
static uint8_t s_ucRxBufferUart5[Rx5_BUFFER_SIZE] = {0};
/* 二级缓冲 */
#define Rx5_DATA_LENTH 		20
static uint8_t s_ucRxUart5[Rx5_DATA_LENTH] = {0};
static uint16_t s_ucCntUart5 = 0;	/* 缓冲区计数器 */

//串口1接收数据处理标志位
int RecHead_flag1 = RESET; //帧头接收标志位
int RecTail_flag1 = RESET; //帧尾接收标志位
int Rec_finish1 = RESET; //接收完成标志位
int Data_length1 = 30; //接收数据长度

//串口2接收数据处理标志位
int RecHead_flag2 = RESET; //帧头接收标志位
int RecTail_flag2 = RESET; //帧尾接收标志位
int Rec_finish2 = RESET; //接收完成标志位
int Data_length2 = 30; //接收数据长度

//串口4接收数据处理标志位
int RecHead_flag4 = RESET; //帧头接收标志位
int Rec_finish4 = RESET; //接收完成标志位
int Data_length4 = 30; //接收数据长度

extern uint8_t Tuikong_buf[50]; //推控舱串口接收缓冲区
extern uint8_t Tuikong_flag; //推控舱串口数据接收完成标志
extern uint8_t Shumei_buf[50]; //树莓派串口接收缓冲区
extern uint8_t Shumei_flag; //树莓派串口数据接收完成标志
extern uint8_t Manipulator_buf[15]; //机械手串口接收缓冲区
extern uint8_t Manipulator_flag; //机械手串口数据接收完成标志
extern uint8_t Depthometer_buf[15]; //深度计串口接收缓冲区
extern uint8_t Depthometer_flag; //深度计串口数据接收完成标志

//extern Uplink_Data

uint8_t MA_flag = RESET; //MA命令标志位

void Task_PCUart_Enable(void) //接收中断使能
{
	Drv_Uart_ReceIT_Enable(&demoUart1, s_ucRxBufferUart1, Rx1_BUFFER_SIZE);
	Drv_Uart_ReceIT_Enable(&demoUart2, s_ucRxBufferUart2, Rx2_BUFFER_SIZE);
	Drv_Uart_ReceIT_Enable(&demoUart3, s_ucRxBufferUart3, Rx3_BUFFER_SIZE);
	Drv_Uart_ReceIT_Enable(&demoUart4, s_ucRxBufferUart4, Rx4_BUFFER_SIZE);
	Drv_Uart_ReceIT_Enable(&demoUart5, s_ucRxBufferUart5, Rx5_BUFFER_SIZE);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) //中断回调函数
{
	//串口1中断处理部分 树莓派
	if(UartHandle->Instance == USART1)
	{
		if(s_ucRxBufferUart1[0] == '@' && RecHead_flag1 == RESET)  //第一个帧头判断
		{	
			RecHead_flag1 = SET;
			s_ucCntUart1 = 0;
		}
		if(RecHead_flag1)  //成功接收到帧头，开始命令接收
		{	
			s_ucRxUart1[s_ucCntUart1++] = s_ucRxBufferUart1[0];
			
			if(s_ucCntUart1 == 2 && s_ucRxBufferUart1[0] == 'D') //树莓派下行数据，接收29个字节
			{
				Data_length1 = 29;
			}
			else if(s_ucCntUart1 == 2 && s_ucRxBufferUart1[0] == 'T') //时间信息，接收19个字节
			{
				Data_length1 = 19;
			}
			else if(s_ucCntUart1 == 2)//其他命令，接收6个字节
			{
				Data_length1 = 6;
				if(s_ucRxBufferUart1[0] == 'M')//MA命令，接收7个字节
				{
					MA_flag = SET;
				}
			}
			
			if(s_ucCntUart1 == 3 && s_ucRxBufferUart1[0] == 'A' && MA_flag == SET) //MA命令，接收7个字节
			{
				Data_length1 = 7;
			}
			
			if(s_ucRxBufferUart1[0] == '$' && s_ucCntUart1 == Data_length1)
			{
				MA_flag = RESET;
				RecHead_flag1 = RESET;
				RecTail_flag1 = RESET;
				Rec_finish1 = SET;
				s_ucCntUart1 = 0;
				memcpy(Shumei_buf, s_ucRxUart1, 50);
				memset(s_ucRxUart1, 0, Rx1_DATA_LENTH);
				Shumei_flag = Rec_finish1;
			}
			else if(s_ucRxBufferUart1[0] != '$' && s_ucCntUart1 == Data_length1)
			{
				MA_flag = RESET;
				s_ucCntUart1 = 0;
				RecHead_flag1 = RESET;
				memset(s_ucRxUart1, 0, Rx1_DATA_LENTH);
			}
		}
		if(s_ucCntUart1 > Rx1_DATA_LENTH)
		{
			MA_flag = RESET;
			s_ucCntUart1 = 0;
			RecHead_flag1 = RESET;
		}
		Drv_Uart_ReceIT_Enable(&demoUart1, s_ucRxBufferUart1, Rx1_BUFFER_SIZE);
	}
	//串口2中断处理部分 推控舱
	else if(UartHandle->Instance == USART2)
	{		
		if(s_ucRxBufferUart2[0] == '@' && RecHead_flag2 == RESET)  //第一个帧头判断
		{	
			RecHead_flag2 = SET;
			s_ucCntUart2 = 0;
		}
		if(RecHead_flag2)  //成功接收到帧头，开始命令接收
		{	
			s_ucRxUart2[s_ucCntUart2++] = s_ucRxBufferUart2[0];
			
			if(s_ucCntUart2 == 2 && s_ucRxBufferUart2[0] == 'S') //推控舱上行数据，接收25个字节
			{
				Data_length2 = 25;
			}
			else if(s_ucCntUart2 == 2 && s_ucRxBufferUart2[0] == 'A') //推控舱上行应答，接收8个字节
			{
				Data_length2 = 8;
			}
			
			if(s_ucRxBufferUart2[0] == '$' && s_ucCntUart2 == Data_length2)
			{
				RecHead_flag2 = RESET;
				RecTail_flag2 = RESET;
				Rec_finish2 = SET;
				s_ucCntUart2 = 0;
				memcpy(Tuikong_buf, s_ucRxUart2, 50);
				memset(s_ucRxUart2, 0, Rx2_DATA_LENTH);
				Tuikong_flag = Rec_finish2;
			}
			else if(s_ucRxBufferUart2[0] != '$' && s_ucCntUart2 == Data_length2)
			{
				s_ucCntUart2 = 0;
				RecHead_flag2 = RESET;
				memset(s_ucRxUart2, 0, Rx2_DATA_LENTH);
			}
		}
		if(s_ucCntUart2 > Rx2_DATA_LENTH)
		{
			s_ucCntUart2 = 0;
			RecHead_flag2 = RESET;
			memset(s_ucRxUart2, 0, Rx2_DATA_LENTH);
		}
		Drv_Uart_ReceIT_Enable(&demoUart2, s_ucRxBufferUart2, Rx2_BUFFER_SIZE);
	}
	
	//串口3中断处理部分 机械手
	else if(UartHandle->Instance == USART3)
	{		
		s_ucRxUart3[s_ucCntUart3] = s_ucRxBufferUart3[0];
		s_ucCntUart3++;
	
		if(s_ucCntUart3 > Rx3_DATA_LENTH)
		{
			s_ucCntUart3 = 0;
			Usart_SendString(&demoUart3, s_ucRxUart3);
		}
		
		Drv_Uart_ReceIT_Enable(&demoUart3, s_ucRxBufferUart3, Rx3_BUFFER_SIZE);
	}
	//串口4中断处理部分 深度计
	else if(UartHandle->Instance == UART4)
	{		
		if(s_ucRxBufferUart4[0] == 0x01 && RecHead_flag4 == RESET)  //第一个帧头判断
		{	
			RecHead_flag4 = SET;
			s_ucCntUart4 = 0;
		}
		if(RecHead_flag4)  //成功接收到帧头，开始命令接收
		{
			s_ucRxUart4[s_ucCntUart4++] = s_ucRxBufferUart4[0];
			
			if(s_ucCntUart4 == 7)
			{
				RecHead_flag4 = RESET;
				Rec_finish4 = SET;
				s_ucCntUart4 = 0;
				memcpy(Depthometer_buf, s_ucRxUart4, 10);
				memset(s_ucRxUart4, 0, Rx4_DATA_LENTH);
				Depthometer_flag = Rec_finish4;
			}
		}
	
		if(s_ucCntUart4 > Rx4_DATA_LENTH)
		{
			s_ucCntUart4 = 0;
			RecHead_flag4 = RESET;
			memset(s_ucRxUart4, 0, Rx4_DATA_LENTH);
		}
		
		
		Drv_Uart_ReceIT_Enable(&demoUart4, s_ucRxBufferUart4, Rx4_BUFFER_SIZE);
	}
	//串口5中断处理部分
	else if(UartHandle->Instance == UART5)
	{		
		s_ucRxUart5[s_ucCntUart5] = s_ucRxBufferUart5[0];
		s_ucCntUart5++;
	
		if(s_ucCntUart5 > Rx5_DATA_LENTH)
		{
			s_ucCntUart5 = 0;
			Usart_SendString(&demoUart5, s_ucRxUart5);
		}
		
		Drv_Uart_ReceIT_Enable(&demoUart5, s_ucRxBufferUart5, Rx5_BUFFER_SIZE);
	}
}

//static uint8_t s_ucpPCData[Rx1_DATA_LENTH] = {0};
//#define FRAME_HEARD		'@'
//#define FRAME_END		"\r\n"

//static void S_Task_PCUart_Clear(void)
//{
//	s_ucCntUart1 = 0;
//	memset(s_ucRxBufferUart1, 0, Rx1_BUFFER_SIZE);
//	memset(s_ucRxUart1, 0, Rx1_DATA_LENTH);
//}

//static void S_Task_ConfOutput(void)
//{
//	printf("Alarm Freq Conf	->%d\r\n", Task_AlarmFreqRead());
//}

//static uint8_t S_Task_DataProcess(uint8_t _ucIndex)
//{
//	switch(s_ucpPCData[_ucIndex + 1])
//	{
//		case 'A':		/* 读系统信息，系统配置 */
//			Task_SysInfoOutput();
//			S_Task_ConfOutput();
//		return 'A';
//		
//		case 'C':		/* 数据问询 */
////			printf("@C*");
////			printf("*\r\n");
//		return 'C';
//		
//		case 'D':		/* 写系统时间 */
//			Task_SysTimeConfig(s_ucpPCData);
//			printf("@D**\r\n");
//		return 'D';
//		
//		case 'F':		/* 数据通信频率配置 */
//			Task_AlarmFreqSet(atoi((const char*)s_ucpPCData + 2));
////			printf("@F**\r\n");
//		return 'F';
//		
//		case 'G':
//			
//		return 'G';
//		
//		case 'H':		/* 心跳 */
//			printf("@H**\r\n");
//		return 'H';
//		
//		case 'g':		/* 读文件列表 */
//			Task_FATFSReadDir();
//			printf("@i**\r\n");
//		return 'g';
//		
//		case 'j':
//			Task_FATFSSendFile(s_ucpPCData);
//			printf("@l**\r\n");
//		return 'j';
//		
//		default:		/* CMD错误 */
//			Task_Led_RedOn();
//#ifdef DEBUG_ENABLE
//			printf("CMD Error!!!\r\n");
//#endif
//		return 0;
//	}
//}

//uint8_t Task_PCListen(void)
//{
//	uint8_t ucRes = 0;
//	uint8_t index;
//	int8_t ucFrameHead,ucFrameEnd = 0;
//	
//	do
//	{
//		if(s_ucCntUart1 == 0)
//			break;
//		
//		memcpy(s_ucpPCData, s_ucRxUart1, Rx1_DATA_LENTH);
//		
//		/* 协议解析 */
//		for(index = 0; index < Rx1_DATA_LENTH; index++)
//		{
//			/* 寻找帧头 */
//			if(s_ucpPCData[index] == FRAME_HEARD)
//			{
//				ucFrameHead = index;
//				continue;
//			}
//			
//			do
//			{
//				if(s_ucpPCData[index] != FRAME_END[0])
//					break;
//				if(s_ucpPCData[index + 1] != FRAME_END[1])
//					break;
//				ucFrameEnd = index;
//				
//				if((ucFrameEnd - ucFrameHead) < 0)
//					break;
//				
//				ucRes = S_Task_DataProcess(ucFrameHead);
//				if(ucRes == 0)	/* 数据处理 */
//				{
//					/* CMD错误 */
//					S_Task_PCUart_Clear();	/* 清缓冲区 */
//					return 0;
//				}
//				
//				S_Task_PCUart_Clear();
//				memset(s_ucpPCData, 0, Rx1_DATA_LENTH);
//				
//				return ucRes;	/* 协议解析正确 */
//			}while(0);
//		}
//	}while(0);
//	
//	return 0;
//}

//uint8_t *Task_GetPCUart(void)
//{
//	return s_ucpPCData;
//}
