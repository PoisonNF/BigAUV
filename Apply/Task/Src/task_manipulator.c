#include "task_conf.h"

#include "config.h"

#define Manipulator_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[1]); //机械手485接收模式
#define Manipulator_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[1]); //机械手485发送模式 

uint8_t Manipulator_flag = RESET; //机械手工作标志位
uint8_t Manipulator_Recvflag = RESET; //机械手串口数据接收完成标志
uint8_t Manipulator_buf[20]; //机械手串口接收缓冲区
uint8_t Manipulator_Uptask = 100; //上行命令机械手任务类型
uint8_t Manipulator_HistoryUptask = 100; //上行命令历史机械手任务类型，用于任务重启

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
uint8_t Manipulator_SendCmd[8] = {'@', 'C', '0', '0', '0', '0', '$'}; //机械手命令发送

void Manipulator_SendDate()//机械手指令发送函数
{
	Manipulator_RS485_Send;
	Drv_Delay_Ms(2);
	Drv_Uart_Transmit(&tManipulator_Uart, Manipulator_SendCmd, 8);
	Drv_Delay_Ms(2);	
	Manipulator_RS485_Recive;
}

void Manipulator_Analysis(void)//机械手数据分析函数
{
	if((Manipulator_Recvflag == SET) && (Manipulator_flag == SET))
	{
		switch(Manipulator_Uptask)
		{
			case 'A':
			case 'B':
				switch(Manipulator_buf[3])
				{
					case Notask:
						if(Manipulator_Uptask == 'A' || Manipulator_Uptask == 'B' )
						{
							Manipulator_HistoryUptask == Manipulator_Uptask;
							Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"@DA", 3); 
							Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"O0", 2); 
							Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"$", 1);	
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
							Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"@DA", 3);
							Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"C0", 2); 
							Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"$", 1);	
						}
						if(!Hatchdoor_flag)
						{
							Manipulator_SendCmd[2] = 'E';
							Manipulator_SendDate();
							Manipulator_Uptask =100;
							Manipulator_HistoryUptask = 100;
							Manipulator_flag = RESET;
						}
						break;
					case Back:
						if(Manipulator_buf[2] == Accomplish_State)
						{
							Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"@DA", 3);
							Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"C0", 2); 
							Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"$", 1);	
						}
						if(!Hatchdoor_flag)
						{
							Manipulator_SendCmd[2] = 'E';
							Manipulator_SendDate();
							Manipulator_Uptask =100;
							Manipulator_HistoryUptask = 100;
							Manipulator_flag = RESET;
						}
						break;
					default:
						break;
				}
				break;
			
			case 'C': //复位回收细节需敲定
				if((Manipulator_buf[3] == Reset) || (Manipulator_buf[3] == Back))
				{
					Manipulator_Uptask = Manipulator_HistoryUptask;
				}
				else
				{
					Manipulator_SendCmd[2] = 'C';
					Manipulator_SendDate();
					Manipulator_SendCmd[2] = 100;
				} 
				break;

			case 'D': //重启细节需敲定
				// if(Manipulator_buf[3] == Notask)
				// {

				// }
				// Manipulator_SendCmd[2] = 'F';
				// Manipulator_SendDate();
				// Manipulator_Uptask = Manipulator_HistoryUptask;
				break;

			default:
				break;
		}

		Manipulator_Recvflag = RESET;
	}
}




