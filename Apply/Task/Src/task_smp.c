#include "task_conf.h"

#include "config.h"

tagUplinkData_T Uplink_Data;

uint8_t Shumei_buf[100]; //树莓派串口接收缓冲区
uint8_t Shumei_flag = RESET; //树莓派串口数据接收完成标志

uint8_t Shumei_RecvData[40] ; //树莓派下行数据接收 数据33字节
uint8_t Shumei_SendData[100] ; //int类型树莓派上行数据发送 数据50字节或68字节
uint8_t Shumei_SendCmd[10]; //树莓派上行命令发送 数据8字节

uint8_t Shumei_PID_Flag = RESET; //测试模式PID调试

void ShumeiCmd_Send(void) //上行命令发送函数，即向树莓派数据应答
{
//	memcpy(Shumei_SendCmd, (uint8_t *)"@ACK_", 5);
	memcpy(Shumei_SendCmd, (uint8_t *)"@APP_", 5);
	memcpy(&Shumei_SendCmd[5], &Shumei_buf[1], 2);
	Shumei_SendCmd[7] = '$';
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)Shumei_SendCmd, 8); 
}

void ShumeiData_Send(void) //上行数据发送函数，即向树莓派数据定时发送 0.2秒发送一次到树莓派
{
	memcpy(&Shumei_SendData[0], (uint8_t *)"@DUP", 4);
	
	Shumei_SendData[4] = (uint8_t)(Uplink_Data.Depthometer_Data*100) % 256; //深度计数据
	Shumei_SendData[5] = Uplink_Data.Depthometer_Data*10 / 256;
	Shumei_SendData[6] = (uint8_t)(Uplink_Data.Altimeter_Data*100) % 256; //高度计数据
	Shumei_SendData[7] = Uplink_Data.Altimeter_Data*100 / 256;	
	Shumei_SendData[8] = 0x31;
	Shumei_SendData[9] = 0x31;
	Shumei_SendData[10] = 0x31;
	Shumei_SendData[11] = 0x31;

	memcpy(&Shumei_SendData[12], &Uplink_Data.Magnetometer_L.X.byte, 4);
	memcpy(&Shumei_SendData[16], &Uplink_Data.Magnetometer_L.Y.byte, 4);
	memcpy(&Shumei_SendData[20], &Uplink_Data.Magnetometer_L.Z.byte, 4);
	memcpy(&Shumei_SendData[24], &Uplink_Data.Magnetometer_R.X.byte, 4);
	memcpy(&Shumei_SendData[28], &Uplink_Data.Magnetometer_R.Y.byte, 4);
	memcpy(&Shumei_SendData[32], &Uplink_Data.Magnetometer_R.Z.byte, 4);

	Shumei_SendData[36] = 0x31;
	Shumei_SendData[37] = 0x31;
	Shumei_SendData[38] = 0x31;
	Shumei_SendData[39] = 0x31;
	Shumei_SendData[40] = Uplink_Data.Motor_Status[0]; //9号推进器状态
	Shumei_SendData[41] = Uplink_Data.Motor_Status[1]; //1-8号推进器状态'
	Shumei_SendData[42] = 0x31;
	Shumei_SendData[43] = 0x31;
	Shumei_SendData[44] = 0x31;
	Shumei_SendData[45] = 0x31;
	Shumei_SendData[46] = Uplink_Data.Manipulator_WorkState; //机械手工作状态
	Shumei_SendData[47] = Uplink_Data.Manipulator_TaskType; //机械手任务类型
	Shumei_SendData[48] = Uplink_Data.Manipulator_ErrorState; //机械手错误状态
//	Shumei_SendData[49] = '$';
	memcpy(&Shumei_SendData[49], Uplink_Data.Motor_Turning_State, 18);
	Shumei_SendData[67] = '$';
//	Shumei_SendData[29] = '$';
	
//	uint8_t i = 0;
//	
//	memcpy(&Shumei_SendData[0], (uint8_t *)"@DUP", 4);
//	
//	for(i = 4; i < 63; i++)
//	{
//		Shumei_SendData[i] = 0x31; 
//	}
//	Shumei_SendData[63] = '$';

//	if(RESET == Shumei_PID_Flag) 
//		Drv_Uart_Transmit(&tSMP_Uart, Shumei_SendData, 50);
//	else  if (SET == Shumei_PID_Flag)
	Drv_Uart_Transmit(&tSMP_Uart, Shumei_SendData, 68);
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
					case 'S': 
						switch(Shumei_buf[3]) //继电器编号
						{
							case 'A': 
								if(Shumei_buf[4] == '0') //声通机电源关闭
									ShengTong_OFF; 
								else if(Shumei_buf[4] == '1') //声通机电源开启
									ShengTong_ON;
								break;
							
							case 'B': 
								if(Shumei_buf[4] == '0') //前置磁力仪电源关闭
									Front_Magnetometer_OFF;
								else if(Shumei_buf[4] == '1') //前置磁力仪电源开启
									Front_Magnetometer_ON;
								break;
							
							case 'C': 
								if(Shumei_buf[4] == '0') //机械手电源关闭
									Manipulator_OFF;
								else if(Shumei_buf[4] == '1') //机械手电源开启
									Manipulator_ON;
								break;
							
							case 'D': 
								if(Shumei_buf[4] == '0') //侧扫声呐电源关闭
									CeSao_OFF;
								else if(Shumei_buf[4] == '1') //侧扫声呐电源开启
									CeSao_ON;
								break;
							
							case 'E': 
								if(Shumei_buf[4] == '0') //双目摄像电源关闭
									Camera_OFF;
								else if(Shumei_buf[4] == '1') //双目摄像电源开启
									Camera_ON;
								break;
								
							case 'F': 
								if(Shumei_buf[4] == '0') //BD/GPS电源关闭
									BDGPS_OFF;
								else if(Shumei_buf[4] == '1') //BD/GPS电源开启
									BDGPS_ON;
								break;
							
							case 'G': 
								if(Shumei_buf[4] == '0') //光纤惯导电源关闭
									Inertial_navigation_OFF;
								else if(Shumei_buf[4] == '1') //光纤惯导电源开启
									Inertial_navigation_ON;
								break;
							
							case 'H': 
								if(Shumei_buf[4] == '0') //UHF电源关闭
									UHF_OFF;
								else if(Shumei_buf[4] == '1') //UHF电源开启
									UHF_ON;
								break;
							
							case 'I': 
								if(Shumei_buf[4] == '0') //P360电源关闭
									P360_OFF;
								else if(Shumei_buf[4] == '1') //P360电源开启
									P360_ON;
								break;
							
							case 'J': 
								if(Shumei_buf[4] == '0') //DVL电源关闭
									DVL_OFF;
								else if(Shumei_buf[4] == '1') //DVL电源开启
									DVL_ON;
								break;
								
							case 'K': 
								if(Shumei_buf[4] == '0') //高度计电源关闭
									Altimeter_OFF;
								else if(Shumei_buf[4] == '1') //高度计电源开启
									Altimeter_ON;
								break;
							
							case 'L': 
								if(Shumei_buf[4] == '0') //备用12V电源关闭
									Beiyong12V_OFF;
								else if(Shumei_buf[4] == '1') //备用12V电源开启
									Beiyong12V_ON;
								break;
						}
						break;
					
					case 'A': 
						if(Shumei_buf[3] == '0') //所有设备停止工作
						{
							ShengTong_OFF;
							Manipulator_OFF;
							CeSao_OFF;
							BDGPS_OFF;
							Camera_OFF;
							Inertial_navigation_OFF;
							P360_OFF;
							DVL_OFF;
							Altimeter_OFF;
							UHF_OFF;
							Front_Magnetometer_OFF;
							Beiyong12V_OFF;
						}
						else if(Shumei_buf[3] == '1') //所有设备开始工作
						{
							ShengTong_ON;
							Manipulator_ON;
							CeSao_ON;
							BDGPS_ON;
							Camera_ON;
							Inertial_navigation_ON;
							P360_ON;
							DVL_ON;
							Altimeter_ON;
							UHF_ON;
							Front_Magnetometer_ON;
							Beiyong12V_ON;
						}
						break;
				}
			break;
			
			case 'J': //机械手控制
				ShumeiCmd_Send();
				Manipulator_flag = SET;
				Manipulator_Uptask = Shumei_buf[3];
				break;
			
			case 'M': 
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				switch(Shumei_buf[2])
				{
					case 'T': //运动控制
						
						break;
					
					case 'P': //平动控制
						
						break;
					
					case 'R': //转动控制
						
						break;
					
					case 'A': //闭环控制
						
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
				switch(Shumei_buf[2])
				{
					case 'S': //时间同步
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 18);
						break;
					
					case 'P': //PID控制
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 11);
						Shumei_PID_Flag = SET;
						break;
				}
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
				}
				break;
				
			case 'W': //树莓派下行数据
				memcpy(Shumei_RecvData, Shumei_buf, 40);
				break;
			
			default:
			
				break;
		}
		Shumei_flag = RESET;
	}
}

