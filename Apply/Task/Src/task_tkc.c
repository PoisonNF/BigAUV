#include "task_conf.h"

#include "config.h"

tagDownlinkData_T Downlink_Data;

uint8_t Tuikong_buf[50]; //推控舱串口接收缓冲区
uint8_t Tuikong_SendData[50]; //推控舱下行数据发送 数据28字节

uint8_t Tuikong_flag = RESET; //推控舱串口数据接收完成标志
uint8_t Hatchdoor_flag = RESET; //舱门开关标志位

// int Motor_Speed[10]; //推进器速度
int MotorStatus_Analysis(uint8_t* _Motor_Status) //推进器状态获取函数
{
	int Motor_Speed[10]; //推进器速度
	uint8_t i = 0;
	for(i = 0; i<9; i++)
	{
		Motor_Speed[i] = Tuikong_buf[i*2+3]*256 +Tuikong_buf[i*2+4];
		if(i<8)
		{
			if(Motor_Speed[i] < 5000 && Motor_Speed[i] > 500)
				_Motor_Status[1] |= (1 << i);
			else
				_Motor_Status[1] &= ~(1 << i);
		}
		else
		{
			if(Motor_Speed[i] < 5000 && Motor_Speed[i] > 500) 
				_Motor_Status[0] |= (1 << (i-8));
			else
				_Motor_Status[0] &= ~(1 << (i-8));
		}	
	}
	return 0;
}

void TuikongData_Analysis(void) //推控舱数据解析
{
	if(Tuikong_flag == SET)
	{
		switch(Tuikong_buf[1])
		{
			//应答
			case 'A': //推控舱应答
				Drv_Uart_Transmit(&tSMP_Uart, Tuikong_buf, 8);
				break;
			//状态
			case 'S': //推控舱上行数据
				if(Tuikong_buf[26] == 0xF0)
				{
					Hatchdoor_flag = SET;
				}
				else if(Tuikong_buf[26] == 0x00)
				{
					Hatchdoor_flag = RESET;
				}
				MotorStatus_Analysis(Uplink_Data.Motor_Status);
				memcpy(Uplink_Data.Motor_Turning_State, &Tuikong_buf[3], 18);	//将推进器状态拷贝到上行数据中
				memcpy(Uplink_Data.TKC_Test_Data,&Tuikong_buf[24],12);			//将推进舱测试数据拷贝到上行数据中
				break;
			
			default:
				
				break;
		}
		Tuikong_flag = RESET;
	}
}

void TuikongData_Send(void) //下行数据发送函数，即向推控舱数据定时发送 0.2秒发送一次到推控舱
{
	memcpy(&Tuikong_SendData[0], (uint8_t *)"@TT", 3);
	memcpy(&Tuikong_SendData[3], Downlink_Data.Pose_Velocity_Data, 24);
	Tuikong_SendData[27] = Downlink_Data.Depthometer_Data*100 / 256; //深度计数据
	Tuikong_SendData[28] = (int)(Downlink_Data.Depthometer_Data*100) % 256;
	Tuikong_SendData[29] = Downlink_Data.Altimeter_Data*100 / 256; //高度计数据
	Tuikong_SendData[30]= (int)(Downlink_Data.Altimeter_Data*100) % 256;
	memcpy(&Tuikong_SendData[31], Downlink_Data.Cursor_Coordinate, 4);
	Tuikong_SendData[35] = '$';

	Drv_Uart_Transmit(&tTKC_Uart, Tuikong_SendData, 36);
}

