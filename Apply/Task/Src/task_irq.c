#include "task_conf.h"

#include "config.h"

#include "usercode.h"		/* usercode头文件 */

/**
 * @brief 外部中断5-9任务函数
 * @param null
 * @retval Null
*/
__weak void Task_EXTI9_5_IRQHandler(void)
{
	
}

/**
 * @brief 外部中断5-9服务函数
 * @param null
 * @retval Null
*/
void EXTI9_5_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&DS3231_ALARM_IRQ);	/* 必须加，参数需修改 */
	
	Task_EXTI9_5_IRQHandler();
}

/**
 * @brief 外部中断10-15任务函数
 * @param null
 * @retval Null
*/
__weak void Task_EXTI15_10_IRQHandler(void)
{
	
}

/**
 * @brief 外部中断10-15服务函数
 * @param null
 * @retval Null
*/
void EXTI15_10_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&tPCUart.tGPIO[1]);	/* 必须加，参数需修改 */
	
	Task_EXTI15_10_IRQHandler();
}

//CH438Q触发外部中断函数
void EXTI0_IRQHandler(void)
{
	Drv_GPIO_EXTI_IRQHandler(&tCH438Q_EXIT_GPIO);
}

/**
 * @brief 串口1中断任务函数
 * @param null
 * @retval Null
*/
__weak void Task_USART1_IRQHandler(void)
{
	
}

/**
 * @brief 串口1中断服务函数
 * @param null
 * @retval Null
*/
void USART1_IRQHandler(void)
{
	/* 示例 */
//	Drv_Uart_IRQHandler(&tPCUart);		/* 必需部分 */
	Drv_Uart_DMA_RxHandler(&tSMP_Uart);
	//Task_USART1_IRQHandler();
}

/**
 * @brief 串口2中断任务函数
 * @param null
 * @retval Null
*/
__weak void Task_USART2_IRQHandler(void)
{
	
}

/**
 * @brief 串口1中断服务函数
 * @param null
 * @retval Null
*/
void USART2_IRQHandler(void)
{
		/* 示例 */
//	Drv_Uart_IRQHandler(&tJY901B.tUART);		/* 必需部分 */
	Drv_Uart_DMA_RxHandler(&tTKC_Uart);
//	Task_USART2_IRQHandler();
}

void DMA1_Channel5_IRQHandler(void)
{
//	Drv_Uart_DMA_TxHandler(&tTKC_Uart);
	Drv_Uart_DMA_RxHandler(&tSMP_Uart);
}

void DMA1_Channel6_IRQHandler(void)
{
	
}

void DMA1_Channel3_IRQHandler(void)
{
	
}

void DMA2_Channel3_IRQHandler(void)
{
	
}

void DMA1_Channel7_IRQHandler(void)
{
	Drv_Uart_DMA_TxHandler(&tTKC_Uart);
}
/**
 * @brief 串口3中断服务函数
 * @param null
 * @retval Null
*/
void USART3_IRQHandler(void)
{
	// Drv_Uart_IRQHandler(&tManipulator_Uart);		/* 必需部分 */
	Drv_Uart_DMA_RxHandler(&tManipulator_Uart);
}

/**
 * @brief 串口4中断服务函数
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{
	// Drv_Uart_IRQHandler(&tDepthometer_Uart);		/* 必需部分 */
	Drv_Uart_DMA_RxHandler(&tDepthometer_Uart);  /* 重新启动DMA接收 */
}

/**
 * @brief 串口5中断服务函数
 * @param null
 * @retval Null
*/
void UART5_IRQHandler(void)
{
	// Drv_Uart_IRQHandler(&tStandby_Uart);		/* 必需部分 */
}

extern char Timeflag_200MS; //0.2秒时间标志位
extern char Timeflag_100MS; //0.1秒时间标志位
extern char Timeflag_Count1; //1S定时器中断计数标志位
extern char Timeflag_Count2; //0.2S定时器中断计数标志位
extern char Timeflag_500MS; //0.5秒时间标志位
extern char Timeflag_1S; //1秒时间标志位

/**
 * @brief 定时器2中断服务函数
 * @param null
 * @retval Null
*/
void TIM2_IRQHandler(void)
{
	/* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
	Drv_Timer_IRQHandler(&tTimer2);
	Timeflag_500MS = SET;
	Timeflag_Count1++;
	if(Timeflag_Count1 >= 2)
	{
		Timeflag_1S = SET;
	}
}

/**
 * @brief 定时器3中断服务函数
 * @param null
 * @retval Null
*/
void TIM3_IRQHandler(void)
{
	/* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
	Drv_Timer_IRQHandler(&tTimer3);
	Timeflag_100MS = SET;
	Timeflag_Count2++;
	if(Timeflag_Count2 >= 2)
	{
		Timeflag_200MS = SET;
	}
}

/**
 * @brief 定时器4中断服务函数
 * @param null
 * @retval Null
*/
void TIM4_IRQHandler(void)
{
    /* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器5中断服务函数
 * @param null
 * @retval Null
*/
void TIM5_IRQHandler(void)
{
    /* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器6中断服务函数
 * @param null
 * @retval Null
*/
void TIM6_IRQHandler(void)
{
    /* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器7中断服务函数
 * @param null
 * @retval Null
*/
void TIM7_IRQHandler(void)
{
	/* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}


