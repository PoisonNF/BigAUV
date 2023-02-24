#include "task_conf.h"

static tagIMU_T			s_tSysIMU;

#define Rx2_DATA_LENTH		100
#define Rx2_BUFFER_SIZE		1
static uint8_t s_ucCntUart2 = 0;
static uint8_t s_ucRxFlgUart2 = 0;
static uint8_t s_ucRxBufferUart2[Rx2_BUFFER_SIZE] = {0};
static uint8_t s_ucRxUart2[Rx2_DATA_LENTH] = {0};
void Task_USART2_IRQHandler(void)
{
	/* 以下为逻辑部分 */
	s_ucRxUart2[s_ucCntUart2] = s_ucRxBufferUart2[0];
	s_ucCntUart2++;
	
	s_ucRxFlgUart2 = 1;
	
	if(s_ucCntUart2 > Rx2_DATA_LENTH)
		s_ucCntUart2 = 0;
	
	Drv_Uart_ReceIT_Enable(&tJY901B.tUART, s_ucRxBufferUart2, Rx2_BUFFER_SIZE);
}

static void S_Task_JY901BufferClear(void)
{
	/* 顺序不能变，先提取数据再重置串口标志 */
	s_ucRxFlgUart2 = 0;
	s_ucCntUart2 = 0;
	memset(s_ucRxBufferUart2, 0, Rx2_BUFFER_SIZE);
	memset(s_ucRxUart2, 0, Rx2_DATA_LENTH);
}

static unsigned char S_Task_JY901Listener(unsigned char *_ucpBuffer, unsigned char _ucSize)
{
	if(s_ucRxFlgUart2)
	{
		memcpy(_ucpBuffer, s_ucRxUart2, _ucSize);
			
		return s_ucCntUart2;
	}
	
	return 0;
}

#define ANGLE_DATA_LENTH	11
uint8_t ucpJY901Data[Rx2_DATA_LENTH] = {0};
unsigned char Task_JY901DataProcess(void)
{
	uint8_t ucRxNum;
	uint8_t ucSum = 0;		/* 和校验 */
	uint8_t index;
	
	ucRxNum = S_Task_JY901Listener(ucpJY901Data, Rx2_DATA_LENTH);
	
	if(ucRxNum)
	{
		/* 协议解析 */
		if((ucRxNum%ANGLE_DATA_LENTH) == 0)
		{
			/* 和校验 */
			for(index = 0; index < ANGLE_DATA_LENTH - 1; index++)
				ucSum += ucpJY901Data[index];
			
			if(ucSum == ucpJY901Data[ANGLE_DATA_LENTH - 1])
			{
				/* 接收到有效数据 */
				s_tSysIMU.fRoll = (float)((ucpJY901Data[3]<<8)|ucpJY901Data[2]) / 32768 * 180;
				s_tSysIMU.fPitch = (float)((ucpJY901Data[5]<<8)|ucpJY901Data[4]) / 32768 * 180;
				s_tSysIMU.fYaw = (float)((ucpJY901Data[7]<<8)|ucpJY901Data[6]) / 32768 * 180;
				
				S_Task_JY901BufferClear();
				OCD_JY901_OutputOnce(&tJY901B);		/* 接收完后再次发送一条问询指令，执行其它过程时，用于等待接收 */
				
//				printf("Roll :%.2f  Pitch :%.2f  Yaw :%.2f\r\n", s_tSysIMU.fRoll, s_tSysIMU.fPitch, s_tSysIMU.fYaw);
				
				return 1;
			}
		}
	}
	
	return 0;
}

tagIMU_T *Task_IMUGet(void)
{
	return &s_tSysIMU;
}

void Task_JY901RxITEnable(void)
{
	Drv_Uart_ReceIT_Enable(&tJY901B.tUART, s_ucRxBufferUart2, Rx2_BUFFER_SIZE);
}
