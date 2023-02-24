#include "task_conf.h"

#include "bsp_io.h"

void Task_UserInit(void)
{
	int ret = 0;
	
	Drv_GPIO_Init(demoGPIO, 3);
	Drv_GPIO_Init(CH438Q_GPIO, 2);
	Drv_GPIO_Init(CH438Q_GPIO_EXIT, 1);
	
	Drv_GPIO_Init(RS485_GPIO, 5); 
//	Drv_GPIO_Set(RS485_GPIO); //RS485设置为接收模式
	
	Drv_GPIO_Init(Relay_GPIO, 3);
			
	Drv_Uart_ITInit(&demoUart1);
	Drv_Uart_ITInit(&demoUart2);
	Drv_Uart_ITInit(&demoUart3);
	Drv_Uart_ITInit(&demoUart4);
	Drv_Uart_ITInit(&demoUart5);
	Task_PCUart_Enable();
	
	CH438_Init();
	CH438_ResetSeril(CHIP1, 0);
    CH438_Uart_Init(CHIP1, 0, 9600);
    CH438_ResetSeril(CHIP1, 1);
    CH438_Uart_Init(CHIP1, 1, 9600);
  	CH438_ResetSeril(CHIP1, 2);      /* 软件复位串口2 */
    CH438_Uart_Init(CHIP1, 2, 9600); /* //串口2打开  波特率9600 */
    CH438_ResetSeril(CHIP1, 3);
    CH438_Uart_Init(CHIP1, 3, 9600);
    CH438_ResetSeril(CHIP1, 4);
    CH438_Uart_Init(CHIP1, 4, 9600);
	
	Drv_Timer_Init(&tTimer2);
	Drv_Timer_Init(&tTimer3);
	Drv_Timer_Enable(&tTimer2);//启动溢出中断并使能定时器
	Drv_Timer_Enable(&tTimer3);//启动溢出中断并使能定时器
		
	ret = OCD_AD24BIT_Init(&tAD24BIT);/*24位AD初始化 */
	if (ret != 0)
	{
		DBG_ERROR("##AD init fail, error code:%d!!!\r\n",ret);
		while(1);  //程序报错stop	
	}
	DBG_INFO("##AD Initialization Complete!\n");
}
