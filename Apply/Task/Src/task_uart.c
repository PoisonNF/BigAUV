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

//USART5���ڽ��ջ�����
#define Rx5_DATA_LENTH 		20
static uint8_t s_ucRxUart5[Rx5_DATA_LENTH] = {0};

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
//	Drv_Uart_ReceIT_Enable(&tSMP_Uart, s_ucRxBufferUart1, Rx1_BUFFER_SIZE);
//	Drv_Uart_ReceIT_Enable(&tTKC_Uart, s_ucRxBufferUart2, Rx2_BUFFER_SIZE);
//	Drv_Uart_ReceIT_Enable(&tManipulator_Uart, s_ucRxBufferUart3, Rx3_BUFFER_SIZE);
//	Drv_Uart_ReceIT_Enable(&tDepthometer_Uart, s_ucRxBufferUart4, Rx4_BUFFER_SIZE);
//	Drv_Uart_ReceIT_Enable(&tStandby_Uart, s_ucRxBufferUart5, Rx5_BUFFER_SIZE);
//}

void Receive_DMA(void)
{
	uint8_t size =0;
	// if(tTKC_Uart.tUartDMA.ucDMARxCplt)
	// {
	// 	memcpy(Tuikong_buf, tTKC_Uart.tRxInfo.ucpRxCache, tTKC_Uart.tRxInfo.usRxLenth);
	// 	size = tTKC_Uart.tRxInfo.usRxLenth;
	// 	Shumei_flag = SET;
		
	// 	if(s_ucRxUart1[0] == '@' && RecHead_flag1 == RESET)  //��һ��֡ͷ�ж�
	// 	{	
	// 		RecHead_flag1 = SET;
	// 	}
	// 	if(RecHead_flag1)  //�ɹ����յ�֡ͷ����ʼ�������
	// 	{	
	// 		if(s_ucRxUart1[1] == 'D') //��ݮ���������ݣ�����29���ֽ�
	// 		{
	// 			Data_length1 = 29;
	// 		}
	// 		else if(s_ucRxUart1[1] == 'T') //ʱ����Ϣ������18���ֽ�
	// 		{
	// 			Data_length1 = 18;
	// 		}
	// 		else 
	// 		{
	// 			Data_length1 = 6;
	// 		}
			
	// 		if(s_ucRxUart1[Data_length1-1] == '$')
	// 		{
	// 			RecHead_flag1 = RESET;
	// 			Rec_finish1 = SET;
	// 			memcpy(Shumei_buf, s_ucRxUart1, 100);
	// 			memset(s_ucRxUart1, 0, Rx1_DATA_LENTH);
	// 			Shumei_flag = Rec_finish1;
	// 		}
	// 		else if(Shumei_buf[Data_length1-1] != '$')
	// 		{
	// 			RecHead_flag1 = RESET;
	// 			memset(s_ucRxUart1, 0, Rx1_DATA_LENTH);
	// 		}
	// 	}
	// 	tTKC_Uart.tUartDMA.ucDMARxCplt = 0;	
	// }
	if(tSMP_Uart.tRxInfo.ucDMARxCplt)
	{
		memcpy(s_ucRxUart1, tSMP_Uart.tRxInfo.ucpDMARxCache, tSMP_Uart.tRxInfo.usDMARxLength);
		size = tSMP_Uart.tRxInfo.usDMARxLength;
		
		if(s_ucRxUart1[0] == '@')  //��һ��֡ͷ�ж�
		{	
			if(s_ucRxUart1[1] == 'W' && s_ucRxUart1[2] == 'D' ) //��ݮ���������ݣ�����29���ֽ�
			{
				Data_length1 = 29;
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
		memcpy(Tuikong_buf, tTKC_Uart.tRxInfo.ucpDMARxCache, tTKC_Uart.tRxInfo.usDMARxLength);
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
		memcpy(Manipulator_buf, tManipulator_Uart.tRxInfo.ucpDMARxCache, tManipulator_Uart.tRxInfo.usDMARxLength);
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
		memcpy(Depthometer_buf, tDepthometer_Uart.tRxInfo.ucpDMARxCache, tDepthometer_Uart.tRxInfo.usDMARxLength);
		size = tDepthometer_Uart.tRxInfo.usDMARxLength;

		if(s_ucRxUart4[0] == '@')  //��һ��֡ͷ�ж�
		{	
			
			if(s_ucRxUart4[6] == '$' && size == 7)
			{
				memcpy(Depthometer_buf, s_ucRxUart4, Rx4_DATA_LENTH);
				memset(s_ucRxUart4, 0, Rx4_DATA_LENTH);
				Depthometer_flag = SET;
			}
			else if(s_ucRxUart4[6] != '$' || size != 7)
			{
				memset(s_ucRxUart4, 0, Rx4_DATA_LENTH);
			}
		}
		tDepthometer_Uart.tRxInfo.ucDMARxCplt = 0;	
	}
	
		
	// if(Shumei_flag)
	// {
	// 	Drv_Uart_Transmit(&tTKC_Uart, Shumei_buf, size);
	// 	Shumei_flag = RESET;
	// 	memset(Shumei_buf,0,100);
	// }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) //�жϻص�����
{
	
//	//����1�жϴ����� ��ݮ��
//	if(UartHandle->Instance == USART1)
//	{
//		if(s_ucRxBufferUart1[0] == '@' && RecHead_flag1 == RESET)  //��һ��֡ͷ�ж�
//		{	
//			RecHead_flag1 = SET;
//			s_ucCntUart1 = 0;
//		}
//		if(RecHead_flag1)  //�ɹ����յ�֡ͷ����ʼ�������
//		{	
//			s_ucRxUart1[s_ucCntUart1++] = s_ucRxBufferUart1[0];
//			
//			if(s_ucCntUart1 == 2 && s_ucRxBufferUart1[0] == 'D') //��ݮ���������ݣ�����29���ֽ�
//			{
//				Data_length1 = 29;
//			}
//			else if(s_ucCntUart1 == 2 && s_ucRxBufferUart1[0] == 'T') //ʱ����Ϣ������18���ֽ�
//			{
//				Data_length1 = 18;
//			}
//			else if(s_ucCntUart1 == 2)//�����������6���ֽ�
//			{
//				Data_length1 = 6;
//			}
//			
//			if(s_ucRxBufferUart1[0] == '$' && s_ucCntUart1 == Data_length1)
//			{
//				MA_flag = RESET;
//				RecHead_flag1 = RESET;
//				RecTail_flag1 = RESET;
//				Rec_finish1 = SET;
//				s_ucCntUart1 = 0;
//				memcpy(Shumei_buf, s_ucRxUart1, 50);
//				memset(s_ucRxUart1, 0, Rx1_DATA_LENTH);
//				Shumei_flag = Rec_finish1;
//			}
//			else if(s_ucRxBufferUart1[0] != '$' && s_ucCntUart1 == Data_length1)
//			{
//				MA_flag = RESET;
//				s_ucCntUart1 = 0;
//				RecHead_flag1 = RESET;
//				memset(s_ucRxUart1, 0, Rx1_DATA_LENTH);
//			}
//		}
//		if(s_ucCntUart1 > Rx1_DATA_LENTH)
//		{
//			MA_flag = RESET;
//			s_ucCntUart1 = 0;
//			RecHead_flag1 = RESET;
//		}
//		Drv_Uart_ReceIT_Enable(&tSMP_Uart, s_ucRxBufferUart1, Rx1_BUFFER_SIZE);
//	}
//	//����2�жϴ����� �ƿز�
//	else if(UartHandle->Instance == USART2)
//	{		
//		if(s_ucRxBufferUart2[0] == '@' && RecHead_flag2 == RESET)  //��һ��֡ͷ�ж�
//		{	
//			RecHead_flag2 = SET;
//			s_ucCntUart2 = 0;
//		}
//		if(RecHead_flag2)  //�ɹ����յ�֡ͷ����ʼ�������
//		{	
//			s_ucRxUart2[s_ucCntUart2++] = s_ucRxBufferUart2[0];
//			
//			if(s_ucCntUart2 == 2 && s_ucRxBufferUart2[0] == 'S') //�ƿز��������ݣ�����25���ֽ�
//			{
//				Data_length2 = 25;
//			}
//			else if(s_ucCntUart2 == 2 && s_ucRxBufferUart2[0] == 'A') //�ƿز�����Ӧ�𣬽���8���ֽ�
//			{
//				Data_length2 = 8;
//			}
//			
//			if(s_ucRxBufferUart2[0] == '$' && s_ucCntUart2 == Data_length2)
//			{
//				RecHead_flag2 = RESET;
//				RecTail_flag2 = RESET;
//				Rec_finish2 = SET;
//				s_ucCntUart2 = 0;
//				memcpy(Tuikong_buf, s_ucRxUart2, 50);
//				memset(s_ucRxUart2, 0, Rx2_DATA_LENTH);
//				Tuikong_flag = Rec_finish2;
//			}
//			else if(s_ucRxBufferUart2[0] != '$' && s_ucCntUart2 == Data_length2)
//			{
//				s_ucCntUart2 = 0;
//				RecHead_flag2 = RESET;
//				memset(s_ucRxUart2, 0, Rx2_DATA_LENTH);
//			}
//		}
//		if(s_ucCntUart2 > Rx2_DATA_LENTH)
//		{
//			s_ucCntUart2 = 0;
//			RecHead_flag2 = RESET;
//			memset(s_ucRxUart2, 0, Rx2_DATA_LENTH);
//		}
//		Drv_Uart_ReceIT_Enable(&tTKC_Uart, s_ucRxBufferUart2, Rx2_BUFFER_SIZE);
//	}
	
	// //����3�жϴ����� ��е��
	// if(UartHandle->Instance == USART3)
	// {		
	// 	if(s_ucRxBufferUart3[0] == '@' && RecHead_flag3 == RESET)  //��һ��֡ͷ�ж�
	// 	{	
	// 		RecHead_flag3 = SET;
	// 		s_ucCntUart3 = 0;
	// 	}
	// 	if(RecHead_flag3)  //�ɹ����յ�֡ͷ����ʼ�������
	// 	{
	// 		s_ucRxUart3[s_ucCntUart3++] = s_ucRxBufferUart3[0];
			
	// 		if(s_ucRxBufferUart3[0] == '$' && s_ucCntUart3 == 7)
	// 		{
	// 			RecHead_flag3 = RESET;
	// 			Rec_finish3 = SET;
	// 			s_ucCntUart3 = 0;
	// 			memcpy(Manipulator_buf, s_ucRxUart3, 10);
	// 			memset(s_ucRxUart3, 0, Rx3_DATA_LENTH);
	// 			Manipulator_Recvflag = Rec_finish3;
	// 		}
	// 	}
	// 	if(s_ucCntUart3 > Rx3_DATA_LENTH)
	// 	{
	// 		s_ucCntUart3 = 0;
	// 		RecHead_flag3 = RESET;
	// 		memset(s_ucRxUart3, 0, Rx3_DATA_LENTH);
	// 	}
	// 	Drv_Uart_ReceIT_Enable(&tManipulator_Uart, s_ucRxBufferUart3, Rx3_BUFFER_SIZE);
	// }
	// //����4�жϴ����� ��ȼ�
	// else if(UartHandle->Instance == UART4)
	// {		
	// 	if(s_ucRxBufferUart4[0] == 0x01 && RecHead_flag4 == RESET)  //��һ��֡ͷ�ж�
	// 	{	
	// 		RecHead_flag4 = SET;
	// 		s_ucCntUart4 = 0;
	// 	}
	// 	if(RecHead_flag4)  //�ɹ����յ�֡ͷ����ʼ�������
	// 	{
	// 		s_ucRxUart4[s_ucCntUart4++] = s_ucRxBufferUart4[0];
			
	// 		if(s_ucCntUart4 == 7)
	// 		{
	// 			RecHead_flag4 = RESET;
	// 			Rec_finish4 = SET;
	// 			s_ucCntUart4 = 0;
	// 			memcpy(Depthometer_buf, s_ucRxUart4, 10);
	// 			memset(s_ucRxUart4, 0, Rx4_DATA_LENTH);
	// 			Depthometer_flag = Rec_finish4;
	// 		}
	// 	}
	
	// 	if(s_ucCntUart4 > Rx4_DATA_LENTH)
	// 	{
	// 		s_ucCntUart4 = 0;
	// 		RecHead_flag4 = RESET;
	// 		memset(s_ucRxUart4, 0, Rx4_DATA_LENTH);
	// 	}
		
		
	// 	Drv_Uart_ReceIT_Enable(&tDepthometer_Uart, s_ucRxBufferUart4, Rx4_BUFFER_SIZE);
	// }
	// //����5�жϴ�����
	// else if(UartHandle->Instance == UART5)
	// {		
	// 	s_ucRxUart5[s_ucCntUart5] = s_ucRxBufferUart5[0];
	// 	s_ucCntUart5++;
	
	// 	if(s_ucCntUart5 > Rx5_DATA_LENTH)
	// 	{
	// 		s_ucCntUart5 = 0;
	// 	}
		
	// 	Drv_Uart_ReceIT_Enable(&tStandby_Uart, s_ucRxBufferUart5, Rx5_BUFFER_SIZE);
	// }
}

