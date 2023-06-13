#include "task_conf.h"

#include "config.h"

tagUplinkData_T Uplink_Data;

uint8_t Shumei_buf[100]; //��ݮ�ɴ��ڽ��ջ�����
uint8_t Shumei_flag = RESET; //��ݮ�ɴ������ݽ�����ɱ�־

uint8_t Shumei_RecvData[30] ; //��ݮ���������ݽ��� ����24�ֽ�
uint8_t Shumei_SendData_Int[50] ; //int������ݮ���������ݷ��� ����50�ֽ�
uint8_t Shumei_SendData_Float[30] ; //float������ݮ���������ݷ��� ����24�ֽ�
uint8_t Shumei_SendCmd[5]; //��ݮ����������� ����3�ֽ�

void ShumeiCmd_Send(void) //��������ͺ�����������ݮ������Ӧ��
{
	memcpy(Shumei_SendCmd, &Shumei_buf[1], 2);
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)"@ACK_", 5);
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)Shumei_SendCmd, 2); 
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)"$", 1);	
}

void ShumeiData_Send(void) //�������ݷ��ͺ�����������ݮ�����ݶ�ʱ���� 0.2�뷢��һ�ε���ݮ��
{
	Shumei_SendData_Int[0] = Uplink_Data.Depthometer_Data*10 / 256; //��ȼ�����
	Shumei_SendData_Int[1] = (int)(Uplink_Data.Depthometer_Data*10) % 256;
	Shumei_SendData_Int[2] = Uplink_Data.Altimeter_Data*100 / 256; //�߶ȼ�����
	Shumei_SendData_Int[3] = (int)(Uplink_Data.Altimeter_Data*100) % 256;
	Shumei_SendData_Int[12] = Uplink_Data.Motor_Status[0]; //9���ƽ���״̬
	Shumei_SendData_Int[13] = Uplink_Data.Motor_Status[1]; //1-8���ƽ���״̬
	Shumei_SendData_Int[18] = Uplink_Data.Manipulator_WorkState; //��е�ֹ���״̬
	Shumei_SendData_Int[19] = Uplink_Data.Manipulator_TaskType; //��е����������
	Shumei_SendData_Int[20] = Uplink_Data.Manipulator_ErrorState; //��е�ִ���״̬
	
	memcpy(&Shumei_SendData_Float[0], &Uplink_Data.Magnetometer_L.X.byte, 4);
	memcpy(&Shumei_SendData_Float[4], &Uplink_Data.Magnetometer_L.Y.byte, 4);
	memcpy(&Shumei_SendData_Float[8], &Uplink_Data.Magnetometer_L.Z.byte, 4);
	memcpy(&Shumei_SendData_Float[12], &Uplink_Data.Magnetometer_R.X.byte, 4);
	memcpy(&Shumei_SendData_Float[16], &Uplink_Data.Magnetometer_R.Y.byte, 4);
	memcpy(&Shumei_SendData_Float[20], &Uplink_Data.Magnetometer_R.Z.byte, 4);
	
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)"@DUP", 4);
	Drv_Uart_Transmit(&tSMP_Uart, Shumei_SendData_Int, 8);
	Drv_Uart_Transmit(&tSMP_Uart, Shumei_SendData_Float, 24);
	Drv_Uart_Transmit(&tSMP_Uart, &Shumei_SendData_Int[8], 13); //13
	Drv_Uart_Transmit(&tSMP_Uart, (uint8_t *)"$", 1);	
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
								if(Shumei_buf[4] == '0') //����24V��Դ�ر�
									Beiyong24V_OFF;
								else if(Shumei_buf[4] == '1') //����24V��Դ����
									Beiyong24V_ON;
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
							Beiyong24V_OFF;
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
							Beiyong24V_ON;
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
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
						break;
					
					case 'P': //PID����
						Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
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
				memcpy(Shumei_RecvData, &Shumei_buf[4], 24);
				break;
			
			default:
			
				break;
		}
		Shumei_flag = RESET;
	}
}

