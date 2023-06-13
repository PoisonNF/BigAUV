#include "task_conf.h"

#include "config.h"

#define Depthometer_RS485_Recive 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)//Drv_GPIO_Reset(&RS485_GPIO[0]); //深度计485接收模式
#define Depthometer_RS485_Send 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)//Drv_GPIO_Set(&RS485_GPIO[0]); //深度计485发送模式

uint8_t Depthometer_buf[20]; //深度计串口接收缓冲区
uint8_t Depthometer_flag = RESET; //深度计串口数据接收完成标志
uint8_t Depthometer_Instruction1[8] = {0x01, 0x03, 0x00, 0x04, 0x00, 0x01, 0xC5, 0xCB}; //深度计指令1 读取压力数据
uint8_t Depthometer_Instruction2[8] = {0x01, 0x03, 0x00, 0x03, 0x00, 0x01, 0x74, 0x0A}; //深度计指令2 读取小数位数

int Depthometer_Analysis(float* _Depthometer_Data)//深度计数据获取函数
{
	if(Depthometer_flag == SET)
	{
		if(Depthometer_buf[0] == 0x01 && Depthometer_buf[1] == 0x03 && Depthometer_buf[2] == 0x02)
		{
			*_Depthometer_Data = (Depthometer_buf[3]*256 + Depthometer_buf[4] - 10)*0.1;
		}
		Depthometer_flag = RESET;
	}
    return 0;
}

void Depthometer_Send(void) //深度计指令发送函数
{
	Depthometer_RS485_Send;
	Drv_Delay_Ms(2);
	Drv_Uart_Transmit(&tDepthometer_Uart, Depthometer_Instruction1, 8);
	Drv_Delay_Ms(1);
	Depthometer_RS485_Recive;
}
