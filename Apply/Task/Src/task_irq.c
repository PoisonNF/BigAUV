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
	Drv_Uart_IRQHandler(&tSMP_Uart);
	Drv_Uart_DMA_RxHandler(&tSMP_Uart);
}

/* DMA1_Channel4中断处理函数 */
void DMA1_Channel4_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&tSMP_Uart.tUartDMA.tDMATx);      //HAL库公用DMA中断处理函数
}

/* 串口发送完成回调函数 */
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart == &tSMP_Uart.tUARTHandle)
//		Drv_Uart_DMA_TxHandler(&tSMP_Uart);
//	else if(huart == &tTKC_Uart.tUARTHandle)
//		Drv_Uart_DMA_TxHandler(&tTKC_Uart);
//}

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
	Drv_Uart_IRQHandler(&tTKC_Uart);
	Drv_Uart_DMA_RxHandler(&tTKC_Uart);
//	Task_USART2_IRQHandler();
}

/* DMA1_Channel7中断处理函数 */
void DMA1_Channel7_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&tTKC_Uart.tUartDMA.tDMATx);      //HAL库公用DMA中断处理函数
}

void DMA1_Channel5_IRQHandler(void)
{
	//Drv_Uart_DMA_RxHandler(&tSMP_Uart);
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


/**
 * @brief 串口3中断服务函数
 * @param null
 * @retval Null
*/
void USART3_IRQHandler(void)
{
	// Drv_Uart_IRQHandler(&tManipulator_Uart);		/* 必需部分 */
	Drv_Uart_IRQHandler(&tManipulator_Uart);
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
	Drv_Uart_IRQHandler(&tDepthometer_Uart);
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
extern char Timeflag_800MS; //0.8秒时间标志位
extern char Timeflag_1S; //1秒时间标志位
extern char Timeflag_2S; //2秒时间标志位

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
	Drv_Timer_IRQHandler(&tTimer4);
	Timeflag_800MS = SET;
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
	Drv_Timer_IRQHandler(&tTimer6);
	Timeflag_2S = SET;
}

// extern uint8_t ShumeiIsLive;	//判断树莓派存活的计数器
// extern uint8_t ShumeiIsLiveLast;	//判断树莓派存活的计数器的上一帧
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
// 	if(htim->Instance == TIM6)
// 	{
// 		//上一帧计数器等于本次，说明树莓派断连，给推控舱发停止命令
// 		if(ShumeiIsLiveLast == ShumeiIsLive)	
// 		{
// 			Drv_Timer_Disable(&tTimer6);	//关闭定时器
// 			while(1)
// 			{
                
//                 if(Timeflag_200MS) 
//                 {
//                     printf("shikong\r\n");
//                     Drv_Uart_Transmit(&tTKC_Uart, (uint8_t *)"@MAS0$", sizeof("@MAS0$"));	//向推控舱发送@MAS0$
//                     Timeflag_200MS = RESET;
//                 }
                
//                 //等待推控舱的回应
//                 Receive_DMA();
//                 TuikongData_Analysis();

//                 //说明推控舱停止运转恢复正常
// 				if(TuikongStopFlag)
// 				{
// 					TuikongStopFlag = RESET;
// 					Drv_Timer_Enable(&tTimer6);
					
// 					//两个计数器设置为相同的值
// 					ShumeiIsLiveLast = 0;	
// 					ShumeiIsLive = 0;
// 					break;
// 				}
// 			}
// 		}
// 		else	//连接没有问题，跳过
// 		{
// 			ShumeiIsLiveLast = ShumeiIsLive;	//将本次计数值转存
// 			return;
// 		}
// 	}
// }

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


