#include "task_conf.h"

#include "config.h"

#define Lowvoltage_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[2]); //低压监测485接收模式
#define Lowvoltage_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[2]); //低压监测485发送模式
#define Highvoltage_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[3]); //高压监测485接收模式
#define Highvoltage_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[3]); //高压监测485发送模式

uint8_t CH438Q_buf[50]; //CH438Q串口数据接收缓冲区
uint8_t CH438Q_flag = RESET; //CH438Q串口数据接收完成标志
uint8_t CH438Q_NUM = 10; //CH438Q串口号

uint8_t Lowvoltage_Instruction[7] = {0xDD, 0xA5, 0x03, 0x00, 0xFF, 0xFD, 0x77}; //低压数据获取指令
uint8_t Highvoltage_Instruction[8] = {0x01, 0x03, 0x00, 0x01, 0x00, 0x02, 0x95, 0xCB}; //高压数据获取指令

int CH438Q_Analysis(float* _Altimeter_Data, uint8_t* _Lowvoltage_Data, uint8_t* Highvoltage_Data) //CH438Q串口数据获取函数
{
	if(CH438Q_flag == SET)
	{
		switch(CH438Q_NUM)
		{
			case 0: //高度计
				*_Altimeter_Data = (CH438Q_buf[0] - 48)*100 + (CH438Q_buf[1] - 48)*10 + (CH438Q_buf[2] - 48) + (CH438Q_buf[4] - 48)*0.1 + (CH438Q_buf[5] - 48)*0.01;
				break; 
			case 1: //低压监测
				_Lowvoltage_Data[0] = (CH438Q_buf[4]*256 + CH438Q_buf[5])*10; //单位V
				_Lowvoltage_Data[1] = (CH438Q_buf[6]*256 + CH438Q_buf[7])*10; //单位A
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
    return 0;
}

void Lowvoltage_Send() //低压监测指令发送函数
{
	Lowvoltage_RS485_Send;
	Drv_Delay_Ms(2);
	OCD_CH438Q_SendDatas(&tCH438Q, 1, Lowvoltage_Instruction, 7);
	Drv_Delay_Ms(2);
	Lowvoltage_RS485_Recive;
}

void Highvoltage_Send() //高压监测指令发送函数
{
	Highvoltage_RS485_Send;
	Drv_Delay_Ms(2);
	OCD_CH438Q_SendDatas(&tCH438Q, 2, Highvoltage_Instruction, 8);
	Drv_Delay_Ms(2);
	Highvoltage_RS485_Recive;
}

