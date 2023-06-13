#include "task_conf.h"

#include "config.h"

tagUplinkData_T Uplink_Data;

uint8_t Shumei_buf[100]; //��ݮ�ɴ��ڽ��ջ�����
uint8_t Shumei_flag = RESET; //��ݮ�ɴ������ݽ�����ɱ�־

uint8_t Shumei_RecvData[40] ; //��ݮ���������ݽ��� ����33�ֽ�
uint8_t Shumei_SendData[100] ; //int������ݮ���������ݷ��� ����50�ֽڻ�68�ֽ�
uint8_t Shumei_SendCmd[10]; //��ݮ����������� ����8�ֽ�

uint8_t Shumei_PID_Flag = RESET; //����ģʽPID����

void ShumeiCmd_Send(void) //��������ͺ�����������ݮ������Ӧ��
{
//	memcpy(Shumei_SendCmd, (uint8_t *)"@ACK_", 5);
	memcpy(Shumei_SendCmd, (uint8_t *)"@APP_", 5);
	memcpy(&Shumei_SendCmd[5], &Shumei_buf[1], 2);
	Shumei_SendCmd[7] = '$';
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)Shumei_SendCmd, 8); 
}

void ShumeiData_Send(void) //�������ݷ��ͺ�����������ݮ�����ݶ�ʱ���� 0.2�뷢��һ�ε���ݮ��
{
	memcpy(&Shumei_SendData[0], (uint8_t *)"@DUP", 4);
	
	Shumei_SendData[4] = (uint8_t)(Uplink_Data.Depthometer_Data*100) % 256; //��ȼ�����
	Shumei_SendData[5] = Uplink_Data.Depthometer_Data*10 / 256;
	Shumei_SendData[6] = (uint8_t)(Uplink_Data.Altimeter_Data*100) % 256; //�߶ȼ�����
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
	Shumei_SendData[40] = Uplink_Data.Motor_Status[0]; //9���ƽ���״̬
	Shumei_SendData[41] = Uplink_Data.Motor_Status[1]; //1-8���ƽ���״̬'
	Shumei_SendData[42] = 0x31;
	Shumei_SendData[43] = 0x31;
	Shumei_SendData[44] = 0x31;
	Shumei_SendData[45] = 0x31;
	Shumei_SendData[46] = Uplink_Data.Manipulator_WorkState; //��е�ֹ���״̬
	Shumei_SendData[47] = Uplink_Data.Manipulator_TaskType; //��е����������
	Shumei_SendData[48] = Uplink_Data.Manipulator_ErrorState; //��е�ִ���״̬
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
	
void ShumeiData_Analysis(void) //��ݮ�����ݽ���
{
	if(Shumei_flag == SET)
	{
		switch(Shumei_buf[1])
		{
			//Ӧ��
			case 'R': //��Դ����
				ShumeiCmd_Send();
				switch(Shumei_buf[2])
				{
					case 'S': 
						switch(Shumei_buf[3]) //�̵������
						{
							case 'A': 
								if(Shumei_buf[4] == '0') //��ͨ����Դ�ر�
									ShengTong_OFF; 
								else if(Shumei_buf[4] == '1') //��ͨ����Դ����
									ShengTong_ON;
								break;
							
							case 'B': 
								if(Shumei_buf[4] == '0') //ǰ�ô����ǵ�Դ�ر�
									Front_Magnetometer_OFF;
								else if(Shumei_buf[4] == '1') //ǰ�ô����ǵ�Դ����
									Front_Magnetometer_ON;
								break;
							
							case 'C': 
								if(Shumei_buf[4] == '0') //��е�ֵ�Դ�ر�
									Manipulator_OFF;
								else if(Shumei_buf[4] == '1') //��е�ֵ�Դ����
									Manipulator_ON;
								break;
							
							case 'D': 
								if(Shumei_buf[4] == '0') //��ɨ���ŵ�Դ�ر�
									CeSao_OFF;
								else if(Shumei_buf[4] == '1') //��ɨ���ŵ�Դ����
									CeSao_ON;
								break;
							
							case 'E': 
								if(Shumei_buf[4] == '0') //˫Ŀ�����Դ�ر�
									Camera_OFF;
								else if(Shumei_buf[4] == '1') //˫Ŀ�����Դ����
									Camera_ON;
								break;
								
							case 'F': 
								if(Shumei_buf[4] == '0') //BD/GPS��Դ�ر�
									BDGPS_OFF;
								else if(Shumei_buf[4] == '1') //BD/GPS��Դ����
									BDGPS_ON;
								break;
							
							case 'G': 
								if(Shumei_buf[4] == '0') //���˹ߵ���Դ�ر�
									Inertial_navigation_OFF;
								else if(Shumei_buf[4] == '1') //���˹ߵ���Դ����
									Inertial_navigation_ON;
								break;
							
							case 'H': 
								if(Shumei_buf[4] == '0') //UHF��Դ�ر�
									UHF_OFF;
								else if(Shumei_buf[4] == '1') //UHF��Դ����
									UHF_ON;
								break;
							
							case 'I': 
								if(Shumei_buf[4] == '0') //P360��Դ�ر�
									P360_OFF;
								else if(Shumei_buf[4] == '1') //P360��Դ����
									P360_ON;
								break;
							
							case 'J': 
								if(Shumei_buf[4] == '0') //DVL��Դ�ر�
									DVL_OFF;
								else if(Shumei_buf[4] == '1') //DVL��Դ����
									DVL_ON;
								break;
								
							case 'K': 
								if(Shumei_buf[4] == '0') //�߶ȼƵ�Դ�ر�
									Altimeter_OFF;
								else if(Shumei_buf[4] == '1') //�߶ȼƵ�Դ����
									Altimeter_ON;
								break;
							
							case 'L': 
								if(Shumei_buf[4] == '0') //����12V��Դ�ر�
									Beiyong12V_OFF;
								else if(Shumei_buf[4] == '1') //����12V��Դ����
									Beiyong12V_ON;
								break;
						}
						break;
					
					case 'A': 
						if(Shumei_buf[3] == '0') //�����豸ֹͣ����
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
						else if(Shumei_buf[3] == '1') //�����豸��ʼ����
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
			
			case 'J': //��е�ֿ���
				ShumeiCmd_Send();
				Manipulator_flag = SET;
				Manipulator_Uptask = Shumei_buf[3];
				break;
			
			case 'M': 
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				switch(Shumei_buf[2])
				{
					case 'T': //�˶�����
						
						break;
					
					case 'P': //ƽ������
						
						break;
					
					case 'R': //ת������
						
						break;
					
					case 'A': //�ջ�����
						
						break;
				}
			break;
			
			case 'G': //���ĵ���
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				break;
			
			case 'B': //��������
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				break;
			
			case 'E': //Ӧ������
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				break;
			
			case 'T': //ʱ��ͬ��
				ShumeiCmd_Send();
				switch(Shumei_buf[2])
				{
					case 'S': //ʱ��ͬ��
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 18);
						break;
					
					case 'P': //PID����
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 11);
						Shumei_PID_Flag = SET;
						break;
				}
				break;
			
			case 'D': //���ſ��� �� ��ݮ����������
				ShumeiCmd_Send();
				switch(Shumei_buf[2])
				{
					case 'T': //���ſ��� ����ģʽ
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
						break;
					
					case 'A': //���ſ��� �Զ�ģʽ
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
						break;
				}
				break;
				
			case 'W': //��ݮ����������
				memcpy(Shumei_RecvData, Shumei_buf, 40);
				break;
			
			default:
			
				break;
		}
		Shumei_flag = RESET;
	}
}

