#include "task_conf.h"

#include "bsp_io.h"

static uint16_t s_ucCntUart1 = 0;	/* 缓冲区计数器 */

/**
 * @brief 串口1中断函数
 * @param null
 * @retval Null
*/
__weak void Task_EXTI9_5_IRQHandler(void)
{
	
}

/**
 * @brief This function handles EXTI line[9:5] interrupts.
*/
void EXTI9_5_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&DS3231_ALARM_IRQ);	/* 必须加，参数需修改 */
	
	Task_EXTI9_5_IRQHandler();
}

__weak void Task_EXTI15_10_IRQHandler(void)
{
	
}

void EXTI15_10_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&tPCUart.tGPIO[1]);	/* 必须加，参数需修改 */
	
	Task_EXTI15_10_IRQHandler();
}

//CH438Q触发外部中断函数
void EXTI0_IRQHandler(void)
{
	Drv_GPIO_EXTI_IRQHandler(CH438Q_GPIO_EXIT);
}

/**
 * @brief 串口1中断函数
 * @param null
 * @retval Null
*/
__weak void Task_USART1_IRQHandler(void)
{
	
}

/**
 * @brief 串口1中断函数
 * @param null
 * @retval Null
*/
void USART1_IRQHandler(void)
{
	/* 示例 */
	Drv_Uart_IRQHandler(&demoUart1);		/* 必需部分 */
	
//	Task_USART1_IRQHandler();
}

/**
 * @brief 串口2中断函数
 * @param null
 * @retval Null
*/
__weak void Task_USART2_IRQHandler(void)
{

}

void USART2_IRQHandler(void)
{
		/* 示例 */
	Drv_Uart_IRQHandler(&demoUart2);		/* 必需部分 */
//	
//	Task_USART2_IRQHandler();
}

/**
 * @brief 串口3中断函数
 * @param null
 * @retval Null
*/
void USART3_IRQHandler(void)
{
	Drv_Uart_IRQHandler(&demoUart3);		/* 必需部分 */
}

/**
 * @brief 串口4中断函数
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{
	Drv_Uart_IRQHandler(&demoUart4);		/* 必需部分 */
}

/**
 * @brief 串口5中断函数
 * @param null
 * @retval Null
*/
void UART5_IRQHandler(void)
{
	Drv_Uart_IRQHandler(&demoUart5);		/* 必需部分 */
}

extern char Timeflag_200MS; //0.2秒时间标志位
extern char Timeflag_100MS; //0.1秒时间标志位
extern char Timeflag_Count1; //1S定时器中断计数标志位
extern char Timeflag_Count2; //0.2S定时器中断计数标志位
extern char Timeflag_500MS; //0.5秒时间标志位
extern char Timeflag_1S; //1秒时间标志位

/**
 * @brief 定时器2中断函数
 * @param null
 * @retval Null
*/
void TIM2_IRQHandler(void)
{
    Drv_Timer_IRQHandler(&tTimer2);
	Timeflag_500MS = SET;
	Timeflag_Count1++;
	if(Timeflag_Count1 >= 2)
	{
		Timeflag_1S = SET;
	}
}

extern int time_rand; //随机数生成种子

/**
 * @brief 定时器3中断函数
 * @param null
 * @retval Null
*/
void TIM3_IRQHandler(void)
{
	Drv_Timer_IRQHandler(&tTimer3);
	Timeflag_100MS = SET;
	Timeflag_Count2++;
	if(Timeflag_Count2 >= 2)
	{
		Timeflag_200MS = SET;
	}
//	time_rand++;
}

/**
 * @brief 定时器4中断函数
 * @param null
 * @retval Null
*/
void TIM4_IRQHandler(void)
{
    /* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器5中断函数
 * @param null
 * @retval Null
*/
void TIM5_IRQHandler(void)
{
    /* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器6中断函数
 * @param null
 * @retval Null
*/
void TIM6_IRQHandler(void)
{
    /* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器7中断函数
 * @param null
 * @retval Null
*/
void TIM7_IRQHandler(void)
{
	/* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

#ifndef RTT_ENBALE
/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief 系统滴答中断
 * @param Null
 * @retval Null
*/
void SysTick_Handler(void)
{
    Drv_HAL_IncTick();
}

/**
 * @brief HAL库系统报错中断
 * @param Null
 * @retval Null
*/
void HardFault_Handler(void)
{
	while(1)
	{
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
}

#endif

