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
					case 'S': //��һģʽ
						
						break;
					
					case 'A': //����ģʽ
						
						break;
				}
			break;
			//״̬
				case 'J': //��е�ֿ���
				ShumeiCmd_Send();
				Manipulator_flag = SET;
				Manipulator_Uptask = Shumei_buf[3];

				break;
			
			case 'M': //�˶�����
				ShumeiCmd_Send();
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
				switch(Shumei_buf[2])
				{
					case 'T': //����ģʽ
						
						break;
					
					case 'P': //ƽ��ģʽ
						
						break;
					
					case 'R': //ת��ģʽ
						
						break;
					
					case 'A': //�Զ�ģʽ
						
						break;
					
					case 'Y': //ҡ��ģʽ
						
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
				Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, 6);
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
					
//					case 'D': //��ݮ����������
//						memcpy(Shumei_RecvData, &Shumei_buf[4], 24);
//						break;
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

