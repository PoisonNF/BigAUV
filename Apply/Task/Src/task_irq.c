#include "task_conf.h"

#include "bsp_io.h"

static uint16_t s_ucCntUart1 = 0;	/* ������������ */

/**
 * @brief ����1�жϺ���
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
//	Drv_GPIO_EXTI_IRQHandler(&DS3231_ALARM_IRQ);	/* ����ӣ��������޸� */
	
	Task_EXTI9_5_IRQHandler();
}

__weak void Task_EXTI15_10_IRQHandler(void)
{
	
}

void EXTI15_10_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&tPCUart.tGPIO[1]);	/* ����ӣ��������޸� */
	
	Task_EXTI15_10_IRQHandler();
}

//CH438Q�����ⲿ�жϺ���
void EXTI0_IRQHandler(void)
{
	Drv_GPIO_EXTI_IRQHandler(CH438Q_GPIO_EXIT);
}

/**
 * @brief ����1�жϺ���
 * @param null
 * @retval Null
*/
__weak void Task_USART1_IRQHandler(void)
{
	
}

/**
 * @brief ����1�жϺ���
 * @param null
 * @retval Null
*/
void USART1_IRQHandler(void)
{
	/* ʾ�� */
	Drv_Uart_IRQHandler(&demoUart1);		/* ���貿�� */
	
//	Task_USART1_IRQHandler();
}

/**
 * @brief ����2�жϺ���
 * @param null
 * @retval Null
*/
__weak void Task_USART2_IRQHandler(void)
{

}

void USART2_IRQHandler(void)
{
		/* ʾ�� */
	Drv_Uart_IRQHandler(&demoUart2);		/* ���貿�� */
//	
//	Task_USART2_IRQHandler();
}

/**
 * @brief ����3�жϺ���
 * @param null
 * @retval Null
*/
void USART3_IRQHandler(void)
{
	Drv_Uart_IRQHandler(&demoUart3);		/* ���貿�� */
}

/**
 * @brief ����4�жϺ���
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{
	Drv_Uart_IRQHandler(&demoUart4);		/* ���貿�� */
}

/**
 * @brief ����5�жϺ���
 * @param null
 * @retval Null
*/
void UART5_IRQHandler(void)
{
	Drv_Uart_IRQHandler(&demoUart5);		/* ���貿�� */
}

extern char Timeflag_200MS; //0.2��ʱ���־λ
extern char Timeflag_100MS; //0.1��ʱ���־λ
extern char Timeflag_Count1; //1S��ʱ���жϼ�����־λ
extern char Timeflag_Count2; //0.2S��ʱ���жϼ�����־λ
extern char Timeflag_500MS; //0.5��ʱ���־λ
extern char Timeflag_1S; //1��ʱ���־λ

/**
 * @brief ��ʱ��2�жϺ���
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

extern int time_rand; //�������������

/**
 * @brief ��ʱ��3�жϺ���
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
 * @brief ��ʱ��4�жϺ���
 * @param null
 * @retval Null
*/
void TIM4_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��5�жϺ���
 * @param null
 * @retval Null
*/
void TIM5_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��6�жϺ���
 * @param null
 * @retval Null
*/
void TIM6_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��7�жϺ���
 * @param null
 * @retval Null
*/
void TIM7_IRQHandler(void)
{
	/* ʾ�� */
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

