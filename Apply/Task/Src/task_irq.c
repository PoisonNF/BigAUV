#include "task_conf.h"

#include "config.h"

#include "usercode.h"		/* usercodeͷ�ļ� */

/**
 * @brief �ⲿ�ж�5-9������
 * @param null
 * @retval Null
*/
__weak void Task_EXTI9_5_IRQHandler(void)
{
	
}

/**
 * @brief �ⲿ�ж�5-9������
 * @param null
 * @retval Null
*/
void EXTI9_5_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&DS3231_ALARM_IRQ);	/* ����ӣ��������޸� */
	
	Task_EXTI9_5_IRQHandler();
}

/**
 * @brief �ⲿ�ж�10-15������
 * @param null
 * @retval Null
*/
__weak void Task_EXTI15_10_IRQHandler(void)
{
	
}

/**
 * @brief �ⲿ�ж�10-15������
 * @param null
 * @retval Null
*/
void EXTI15_10_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&tPCUart.tGPIO[1]);	/* ����ӣ��������޸� */
	
	Task_EXTI15_10_IRQHandler();
}

/**
 * @brief ����1�ж�������
 * @param null
 * @retval Null
*/
__weak void Task_USART1_IRQHandler(void)
{
	
}

/**
 * @brief ����1�жϷ�����
 * @param null
 * @retval Null
*/
void USART1_IRQHandler(void)
{
	/* ʾ�� */
//	Drv_Uart_IRQHandler(&tPCUart);		/* ���貿�� */
	Drv_Uart_DMA_RxHandler(&tSMP_Uart);
	//Task_USART1_IRQHandler();
}

/**
 * @brief ����2�ж�������
 * @param null
 * @retval Null
*/
__weak void Task_USART2_IRQHandler(void)
{
	
}

/**
 * @brief ����1�жϷ�����
 * @param null
 * @retval Null
*/
void USART2_IRQHandler(void)
{
		/* ʾ�� */
//	Drv_Uart_IRQHandler(&tJY901B.tUART);		/* ���貿�� */
	Drv_Uart_DMA_RxHandler(&tTKC_Uart);
//	
//	Task_USART2_IRQHandler();
}

void DMA1_Channel7_IRQHandler(void)
{
	Drv_Uart_DMA_TxHandler(&tTKC_Uart);
}
/**
 * @brief ����3�жϷ�����
 * @param null
 * @retval Null
*/
void USART3_IRQHandler(void)
{
	// Drv_Uart_IRQHandler(&tManipulator_Uart);		/* ���貿�� */
	Drv_Uart_DMA_RxHandler(&tManipulator_Uart);
}

/**
 * @brief ����4�жϷ�����
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{
	// Drv_Uart_IRQHandler(&tDepthometer_Uart);		/* ���貿�� */
	Drv_Uart_DMA_RxHandler(&tDepthometer_Uart);	
}

/**
 * @brief ����5�жϷ�����
 * @param null
 * @retval Null
*/
void UART5_IRQHandler(void)
{
	// Drv_Uart_IRQHandler(&tStandby_Uart);		/* ���貿�� */
}

extern char Timeflag_200MS; //0.2��ʱ���־λ
extern char Timeflag_100MS; //0.1��ʱ���־λ
extern char Timeflag_Count1; //1S��ʱ���жϼ�����־λ
extern char Timeflag_Count2; //0.2S��ʱ���жϼ�����־λ
extern char Timeflag_500MS; //0.5��ʱ���־λ
extern char Timeflag_1S; //1��ʱ���־λ

/**
 * @brief ��ʱ��2�жϷ�����
 * @param null
 * @retval Null
*/
void TIM2_IRQHandler(void)
{
	/* ʾ�� */
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
 * @brief ��ʱ��3�жϷ�����
 * @param null
 * @retval Null
*/
void TIM3_IRQHandler(void)
{
	/* ʾ�� */
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
 * @brief ��ʱ��4�жϷ�����
 * @param null
 * @retval Null
*/
void TIM4_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��5�жϷ�����
 * @param null
 * @retval Null
*/
void TIM5_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��6�жϷ�����
 * @param null
 * @retval Null
*/
void TIM6_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��7�жϷ�����
 * @param null
 * @retval Null
*/
void TIM7_IRQHandler(void)
{
	/* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

#ifndef RTT_ENABLE
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
 * @brief ϵͳ�δ��ж�
 * @param Null
 * @retval Null
*/
void SysTick_Handler(void)
{
    Drv_HAL_IncTick();
}

/**
 * @brief HAL��ϵͳ�����ж�
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

