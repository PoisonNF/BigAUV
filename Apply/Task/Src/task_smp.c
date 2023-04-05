#include "task_conf.h"

#include "config.h"

tagUplinkData_T Uplink_Data;

uint8_t Shumei_buf[100]; //树莓派串口接收缓冲区
uint8_t Shumei_flag = RESET; //树莓派串口数据接收完成标志

uint8_t Shumei_RecvData[30] ; //树莓派下行数据接收 数据24字节
uint8_t Shumei_SendData_Int[50] ; //int类型树莓派上行数据发送 数据50字节
uint8_t Shumei_SendData_Float[30] ; //float类型树莓派上行数据发送 数据24字节
uint8_t Shumei_SendCmd[5]; //树莓派上行命令发送 数据3字节

void ShumeiCmd_Send(void) //上行命令发送函数，即向树莓派数据应答
{
	memcpy(Shumei_SendCmd, &Shumei_buf[1], 2);
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)"@ACK_", 5);
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)Shumei_SendCmd, 2); 
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)"$", 1);	
}

void ShumeiData_Send(void) //上行数据发送函数，即向树莓派数据定时发送 0.2秒发送一次到树莓派
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
	
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)"@DUP", 4);
	Drv_Uart_Transmit(&tSMP_Uart, Shumei_SendData_Int, 8);
	Drv_Uart_Transmit(&tSMP_Uart, Shumei_SendData_Float, 24);
	Drv_Uart_Transmit(&tSMP_Uart, &Shumei_SendData_Int[8], 10);
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)"$", 1);	
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

				break;
			
			case 'M': //运动控制
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
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
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				break;
			
			case 'B': //浮力调节
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				break;
			
			case 'E': //应急控制
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				break;
			
			case 'T': //时间同步
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				break;
			
			case 'D': //舱门控制 或 树莓派下行数据
				ShumeiCmd_Send();
				switch(Shumei_buf[2])
				{
					case 'T': //舱门控制 测试模式
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
						break;
					
					case 'A': //舱门控制 自动模式
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
						break;
					
//					case 'D': //树莓派下行数据
//						memcpy(Shumei_RecvData, &Shumei_buf[4], 24);
//						break;
				}
				break;
				
			case 'W': //树莓派下行数据
				memcpy(Shumei_RecvData, &Shumei_buf[4], 24);
				break;
			
			default:
			
				break;
		}
		Shumei_flag = RESET;
	}
}

