#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"

void Task_UserInit(void)
{
	int ret = 0;
	
	Drv_GPIO_Init(tLED_GPIO, 3);
	Drv_GPIO_Init(tCH438Q_GPIO, 2);
	Drv_GPIO_Init(&tCH438Q_EXIT_GPIO, 1);
	
	Drv_GPIO_Init(tRS485_GPIO, 5); 
//	Drv_GPIO_Set(RS485_GPIO); //RS485����Ϊ����ģʽ
	
//	Drv_GPIO_Init(&tAD_GPIO, 1);
	 
	Drv_GPIO_Init(&tRS485TEST_GPIO, 1); //���԰�485��ƽʱ��ע��
	
	Drv_GPIO_Init(tRelay_GPIO, 12);
	
	Drv_Uart_DMAInit(&tSMP_Uart);
	Drv_Uart_DMAInit(&tTKC_Uart);
	Drv_Uart_DMAInit(&tManipulator_Uart);
	Drv_Uart_DMAInit(&tDepthometer_Uart);
//	Drv_Uart_ITInit(&tStandby_Uart);
//	Task_PCUart_Enable();
	
	CH438_Init();
	CH438_ResetSeril(CHIP1, 0);
    CH438_Uart_Init(CHIP1, 0, 9600);
    CH438_ResetSeril(CHIP1, 1);
    CH438_Uart_Init(CHIP1, 1, 9600);
  	CH438_ResetSeril(CHIP1, 2);     
    CH438_Uart_Init(CHIP1, 2, 9600); 
    CH438_ResetSeril(CHIP1, 3);
    CH438_Uart_Init(CHIP1, 3, 9600);
    CH438_ResetSeril(CHIP1, 4);
    CH438_Uart_Init(CHIP1, 4, 9600);
	
	Drv_Timer_Init(&tTimer2);
	Drv_Timer_Init(&tTimer3);
	Drv_Timer_Enable(&tTimer2);//��������жϲ�ʹ�ܶ�ʱ��
	Drv_Timer_Enable(&tTimer3);//��������жϲ�ʹ�ܶ�ʱ��
		
	ret = OCD_AD24BIT_Init(&tAD24BIT);/*24λAD��ʼ�� */
	if (ret != 0)
	{
		DBG_ERROR("##AD init fail, error code:%d!!!\r\n",ret);
		while(1);  //���򱨴�stop	
	}
	//DBG_INFO("##AD Initialization Complete!\n");
}


