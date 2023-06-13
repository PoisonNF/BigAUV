#include "task_conf.h"

#include "config.h"

//USART1���ڽ��ջ�����
#define Rx1_DATA_LENTH 		100
static uint8_t s_ucRxUart1[Rx1_DATA_LENTH] = {0};

//USART2���ڽ��ջ�����
#define Rx2_DATA_LENTH 		100
static uint8_t s_ucRxUart2[Rx2_DATA_LENTH] = {0};

//USART3���ڽ��ջ�����
#define Rx3_DATA_LENTH 		20
static uint8_t s_ucRxUart3[Rx3_DATA_LENTH] = {0};

//USART4���ڽ��ջ�����
#define Rx4_DATA_LENTH 		20
static uint8_t s_ucRxUart4[Rx4_DATA_LENTH] = {0};

// //USART5���ڽ��ջ�����
// #define Rx5_DATA_LENTH 		20
// static uint8_t s_ucRxUart5[Rx5_DATA_LENTH] = {0};

//���������������ֽڳ���
int Data_length1 = 30; //�������ݳ���
int Data_length2 = 30; //�������ݳ���
int Data_length3 = 30; //�������ݳ���
int Data_length4 = 30; //�������ݳ���

extern uint8_t Tuikong_buf[50]; //�ƿزմ��ڽ��ջ�����
extern uint8_t Tuikong_flag; //�ƿزմ������ݽ�����ɱ�־
extern uint8_t Shumei_buf[100]; //��ݮ�ɴ��ڽ��ջ�����
extern uint8_t Shumei_flag; //��ݮ�ɴ������ݽ�����ɱ�־
extern uint8_t Manipulator_buf[20]; //��е�ִ��ڽ��ջ�����
extern uint8_t Manipulator_Recvflag; //��е�ִ������ݽ�����ɱ�־
extern uint8_t Depthometer_buf[20]; //��ȼƴ��ڽ��ջ�����
extern uint8_t Depthometer_flag; //��ȼƴ������ݽ�����ɱ�־

//void Task_PCUart_Enable(void) //�����ж�ʹ��
//{
//	Drv_Uart_ReceIT_Enable(&tStandby_Uart, s_ucRxBufferUart5, Rx5_BUFFER_SIZE);
//}

void Receive_DMA(void)
{
	uint8_t size =0;

	if(tSMP_Uart.tRxInfo.ucDMARxCplt)
	{
		memcpy(s_ucRxUart1, tSMP_Uart.tRxInfo.ucpDMARxCache, tSMP_Uart.tRxInfo.usDMARxLength);
		size = tSMP_Uart.tRxInfo.usDMARxLength;
		
		if(s_ucRxUart1[0] == '@')  //��һ��֡ͷ�ж�
		{	
			if(s_ucRxUart1[1] == 'W' && s_ucRxUart1[2] == 'D' ) //��ݮ���������ݣ�����29���ֽ�
			{
				Data_length1 = 33;
			}
			else if(s_ucRxUart1[1] == 'T') //ʱ����Ϣ������18���ֽ�
			{
				Data_length1 = 18;
			}
			else 
			{
				Data_length1 = 6;
			}
			
			if(s_ucRxUart1[Data_length1-1] == '$' && size == Data_length1)
			{
				memcpy(Shumei_buf, s_ucRxUart1, Rx1_DATA_LENTH);
				memset(s_ucRxUart1, 0, Rx1_DATA_LENTH);
				Shumei_flag = SET;
			}
			else if(s_ucRxUart1[Data_length1-1] != '$' || size != Data_length1)
			{
				memset(s_ucRxUart1, 0, Rx1_DATA_LENTH);
			}
		}
		tSMP_Uart.tRxInfo.ucDMARxCplt = 0;	
	}
	else if (tTKC_Uart.tRxInfo.ucDMARxCplt)
	{
		memcpy(s_ucRxUart2, tTKC_Uart.tRxInfo.ucpDMARxCache, tTKC_Uart.tRxInfo.usDMARxLength);
		size = tTKC_Uart.tRxInfo.usDMARxLength;
		
		if(s_ucRxUart2[0] == '@')  //��һ��֡ͷ�ж�
		{	
			if(s_ucRxUart2[1] == 'S') //�ƿز��������ݣ�����25���ֽ�
			{
				Data_length2 = 25;
			}
			else if(s_ucRxUart2[1] == 'A') //�ƿز�����Ӧ�𣬽���8���ֽ�
			{
				Data_length2 = 8;
			}
			
			if(s_ucRxUart2[Data_length2-1] == '$' && size == Data_length2)
			{
				memcpy(Tuikong_buf, s_ucRxUart2, Rx2_DATA_LENTH);
				memset(s_ucRxUart2, 0, Rx2_DATA_LENTH);
				Tuikong_flag = SET;
			}
			else if(s_ucRxUart2[Data_length2-1] != '$' || size != Data_length2)
			{
				memset(s_ucRxUart2, 0, Rx2_DATA_LENTH);
			}
		}
		tTKC_Uart.tRxInfo.ucDMARxCplt = 0;	
	}
	else if (tManipulator_Uart.tRxInfo.ucDMARxCplt)
	{
		memcpy(s_ucRxUart3, tManipulator_Uart.tRxInfo.ucpDMARxCache, tManipulator_Uart.tRxInfo.usDMARxLength);
		size = tManipulator_Uart.tRxInfo.usDMARxLength;

		if(s_ucRxUart3[0] == '@')  //��һ��֡ͷ�ж�
		{	
			
			if(s_ucRxUart3[6] == '$' && size == 7)
			{
				memcpy(Manipulator_buf, s_ucRxUart3, Rx3_DATA_LENTH);
				memset(s_ucRxUart3, 0, Rx3_DATA_LENTH);
				Manipulator_flag = SET;
			}
			else if(s_ucRxUart3[6] != '$' || size != 7)
			{
				memset(s_ucRxUart3, 0, Rx3_DATA_LENTH);
			}
		}
		tManipulator_Uart.tRxInfo.ucDMARxCplt = 0;	
	}
	else if (tDepthometer_Uart.tRxInfo.ucDMARxCplt)
	{
		memcpy(s_ucRxUart4, tDepthometer_Uart.tRxInfo.ucpDMARxCache, tDepthometer_Uart.tRxInfo.usDMARxLength);
		size = tDepthometer_Uart.tRxInfo.usDMARxLength;

		if(s_ucRxUart4[0] == 0x01)  //��һ��֡ͷ�ж�
		{	
			
			if(size == 7)
			{
				memcpy(Depthometer_buf, s_ucRxUart4, Rx4_DATA_LENTH);
				memset(s_ucRxUart4, 0, Rx4_DATA_LENTH);
				Depthometer_flag = SET;
			}
			else
			{
				memset(s_ucRxUart4, 0, Rx4_DATA_LENTH);
			}
		}
		tDepthometer_Uart.tRxInfo.ucDMARxCplt = 0;	
	}
	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) //�жϻص�����
{

}

