#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"

void Task_UserInit(void)
{
	int ret = 0;
	
	Drv_GPIO_Init(tLED_GPIO, 3);
	
	Drv_GPIO_Init(tRS485_GPIO, 5); 
//	Drv_GPIO_Set(RS485_GPIO); //RS485设置为接收模式

//	Drv_GPIO_Init(&tRS485TEST_GPIO, 1); //测试板485，平时可注释
	
	Drv_GPIO_Init(tRelay_GPIO, 12);
	
	Drv_Uart_DMAInit(&tSMP_Uart);
	Drv_Uart_DMAInit(&tTKC_Uart);
	Drv_Uart_DMAInit(&tManipulator_Uart);
	Drv_Uart_DMAInit(&tDepthometer_Uart);
//	Drv_Uart_ITInit(&tStandby_Uart);
//	Task_PCUart_Enable();
	
	Drv_Timer_Init(&tTimer2);
	Drv_Timer_Init(&tTimer3);
	Drv_Timer_Enable(&tTimer2);//启动溢出中断并使能定时器
	Drv_Timer_Enable(&tTimer3);//启动溢出中断并使能定时器
	
//	OCD_CH438Q_Init(&tCH438Q);
		
	ret = OCD_AD24BIT_Init(&tAD24BIT);/*24位AD初始化 */
	if (ret != 0)
	{
		DBG_ERROR("##AD init fail, error code:%d!!!\r\n",ret);
		while(1);  //程序报错stop	
	}
	//DBG_INFO("##AD Initialization Complete!\n");
}












