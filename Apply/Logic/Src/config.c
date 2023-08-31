#include "config.h"

/* ���İ�����ɫ�ƹ���ʾ */
tagGPIO_T tLED_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    [2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    
};

tagGPIO_T tAD_GPIO =
{

	/* AD24BIT CS */
	.tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO���� */
	.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIOPort 			= GPIOB,					/* GPIO���� */

};



/* ��ݮ��ͨ�� */
tagUART_T tSMP_Uart = 
{

	//���ڹ���ģʽ����
	.tUARTHandle.Instance 				= USART1,					/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 115200,					/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ucPriority							= 1,						/* �ж����ȼ� */
	.ucSubPriority						= 3,						/* �ж������ȼ� */
	
	//����DMA���ղ�������
	.tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel5,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tRxInfo.usDMARxMAXSize             	= 100,              	/* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

	.tUartDMA.ucDMARxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA�����ж������ȼ� */
	
	//����DMA���Ͳ�������
	.tUartDMA.bTxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMATx.Instance			= DMA1_Channel4,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 50,						/* ��������ݳ��� */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA�����ж������ȼ� */

	//����GPIO����
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_9,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */

};

/* �ƿز�ͨ�� */
tagUART_T tTKC_Uart = 
{

	//���ڹ���ģʽ����
	.tUARTHandle.Instance 				= USART2,					/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 9600,						/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ucPriority							= 1,						/* �ж����ȼ� */
	.ucSubPriority						= 3,						/* �ж������ȼ� */
	
	//����DMA���ղ�������
	.tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel6,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tRxInfo.usDMARxMAXSize             	= 100,              	/* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

	.tUartDMA.ucDMARxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA�����ж������ȼ� */
	
	//����DMA���Ͳ�������
	.tUartDMA.bTxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMATx.Instance			= DMA1_Channel7,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 50,						/* ��������ݳ��� */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA�����ж������ȼ� */

	//����GPIO����
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_3,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */

};

/* ��е��ͨ�� */
tagUART_T tManipulator_Uart = 
{

	//���ڹ���ģʽ����
	.tUARTHandle.Instance 				= USART3,					/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 9600,						/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ucPriority							= 1,						/* �ж����ȼ� */
	.ucSubPriority						= 3,						/* �ж������ȼ� */
	
	//����DMA���ղ�������
	.tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel3,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tRxInfo.usDMARxMAXSize             	= 100,              	/* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

	.tUartDMA.ucDMARxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA�����ж������ȼ� */
	
	//����DMA���Ͳ�������
	.tUartDMA.bTxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMATx.Instance			= DMA1_Channel2,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 50,						/* ��������ݳ��� */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA�����ж������ȼ� */

	//����GPIO����
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOB,					/* GPIO���� */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_11,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOB,					/* GPIO���� */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */

};

/* ��ȼ�ͨ�� */
tagUART_T tDepthometer_Uart = 
{

	//���ڹ���ģʽ����
	.tUARTHandle.Instance 				= UART4,					/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 9600,						/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ucPriority							= 1,						/* �ж����ȼ� */
	.ucSubPriority						= 3,						/* �ж������ȼ� */
	
	//����DMA���ղ�������
	.tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMARx.Instance			= DMA2_Channel3,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tRxInfo.usDMARxMAXSize             	= 20,              	/* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

	.tUartDMA.ucDMARxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA�����ж������ȼ� */
	
	//����DMA���Ͳ�������
	.tUartDMA.bTxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMATx.Instance			= DMA2_Channel5,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 50,						/* ��������ݳ��� */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA�����ж������ȼ� */

	//����GPIO����
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOC,					/* GPIO���� */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_11,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOC,					/* GPIO���� */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */

};

/* ���ô���ͨ�� */
tagUART_T tStandby_Uart = 
{

	//���ڹ���ģʽ����
	.tUARTHandle.Instance 				= UART5,					/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 9600,						/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ucPriority							= 1,						/* �ж����ȼ� */
	.ucSubPriority						= 3,						/* �ж������ȼ� */
	
	//����DMA���ղ�������
	.tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel3,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tRxInfo.usDMARxMAXSize             	= 100,              	/* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

	.tUartDMA.ucDMARxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA�����ж������ȼ� */
	
	//����DMA���Ͳ�������
	.tUartDMA.bTxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMATx.Instance			= DMA1_Channel2,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 50,						/* ��������ݳ��� */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA�����ж����ȼ� */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA�����ж������ȼ� */

	//����GPIO����
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_12,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOC,					/* GPIO���� */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOD,					/* GPIO���� */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */

};

/* CH438QоƬGPIO */
tagGPIO_T tCH438Q_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin			= GPIO_PIN_0,			/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,											/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,													/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,											/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOE,														/* GPIO���� */
	},
	[1]=
	{ 
		.tGPIOInit.Pin			= GPIO_PIN_1,			/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,											/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,													/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,											/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOE,														/* GPIO���� */
	},
	[2]=
	{ 
		.tGPIOInit.Pin			= GPIO_PIN_2,			/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,											/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,													/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,											/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOE,														/* GPIO���� */
	},
	[3]=
	{ 
		.tGPIOInit.Pin			= GPIO_PIN_6,			/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,											/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,													/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,											/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOE,														/* GPIO���� */
	},
    [4]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_0,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[5]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_1,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[6]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[7]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_3,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[8]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_4,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[9]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_5,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[10]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_6,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[11]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_7,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[12]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_8,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[13]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_13,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
	[14]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_14,				/* GPIO���� */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 				= GPIOC,					/* GPIO���� */
	},
    
};

/* CH438Q�ⲿ�ж�GPIO */
tagGPIO_T tCH438Q_EXIT_GPIO =
{
	
	.tGPIOInit.Pin		= GPIO_PIN_0,				/* GPIO���� */
	.tGPIOInit.Mode 	= GPIO_MODE_IT_FALLING,		/* GPIOģʽ */
	.tGPIOInit.Pull 	= GPIO_PULLUP,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIOPort 			= GPIOB,					/* GPIO���� */
	
	.ucPriority = 0,
	.ucSubPriority = 2,
	
};

/* ADоƬ���� */
 tagAD24BIT_T tAD24BIT =
 {

 	.tSPI.tSPIHandle.Instance 				= SPI2,
	
	.tSPI.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO���� ,SPI2_SCK*/
 	.tSPI.tGPIO[0].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
 	.tSPI.tGPIO[0].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
 	.tSPI.tGPIO[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
 	.tSPI.tGPIO[0].tGPIOPort 			= GPIOB,					/* GPIO���� */
	
 	.tSPI.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO���� ,SPI2_MOSI*/
 	.tSPI.tGPIO[1].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
 	.tSPI.tGPIO[1].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
 	.tSPI.tGPIO[1].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
 	.tSPI.tGPIO[1].tGPIOPort 			= GPIOB,					/* GPIO���� */
	
 	.tSPI.tGPIO[2].tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO���� ,SPI2_MISO*/
 	.tSPI.tGPIO[2].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
 	.tSPI.tGPIO[2].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
 	.tSPI.tGPIO[2].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
 	.tSPI.tGPIO[2].tGPIOPort 			= GPIOB,					/* GPIO���� */
	
	.tSPI.tGPIO[3].tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO���� ,CS*/
 	.tSPI.tGPIO[3].tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
 	.tSPI.tGPIO[3].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
 	.tSPI.tGPIO[3].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
 	.tSPI.tGPIO[3].tGPIOPort 			= GPIOB,					/* GPIO���� */
	
 	.port_num = 6,  //�����Ķ˿��������������õĶ˿ڶ�Ӧ����
 	.port[0].enable = PORT_ENABLE,//�˿�ʹ��
 	.port[0].num = VIN0,  //�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
 	.port[0].gain = 1.001068,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
 	.port[0].offset= 0.0,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;

 	.port[1].enable = PORT_ENABLE,
 	.port[1].num = VIN1,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
 	.port[1].gain = 1.00105,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
 	.port[1].offset= 0.0006,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	
 	.port[2].enable = PORT_ENABLE,
 	.port[2].num = VIN2,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
 	.port[2].gain = 1.001176,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
 	.port[2].offset= 0.0004,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;

 	.port[3].enable = PORT_ENABLE,//�˿�ʹ��
 	.port[3].num = VIN3,  //�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
 	.port[3].gain = 1.001068,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
 	.port[3].offset= 0.0,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;

 	.port[4].enable = PORT_ENABLE,
 	.port[4].num = VIN4,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
 	.port[4].gain = 1.00105,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
 	.port[4].offset= 0.0006,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	
 	.port[5].enable = PORT_ENABLE,
 	.port[5].num = VIN5,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
 	.port[5].gain = 1.001176,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
 	.port[5].offset= 0.0004,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
 
 };

/* ��ʱ��3���� */
tagTIM_T tTimer3 = 
{

	.tTimerHandle.Instance				=TIM3,						/* ͨ�ö�ʱ��3 */
	.tTimerHandle.Init.Prescaler		=7200-1,						 //((1+Prescaler )/72M)*(1+Period )//��ʱ��Сʱ����ģ�
	.tTimerHandle.Init.Period			=1000-1,				//100mS����һ�����
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* ����Ƶ */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* ���ϼ����� */
	.tTimerHandle.Init.RepetitionCounter = 0, //������������ٴκ��ж�һ�Σ�0����ʾ�ж�һ�μ������
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//�Զ�װ��
	.ucPriority = 0,
	.ucSubPriority = 2,

};

/* ��ʱ��2���� */
tagTIM_T tTimer2 = 
{

	.tTimerHandle.Instance				=TIM2,						/* ͨ�ö�ʱ��2 */
	.tTimerHandle.Init.Prescaler		=7200-1,						/* ��Ƶϵ�������ֵ65535 */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* ���ϼ����� */
	.tTimerHandle.Init.Period			=5000-1,					//0.5S����һ�����
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* ʱ�ӷ�Ƶ���� */
	.tTimerHandle.Init.RepetitionCounter = 0, //������������ٴκ��ж�һ�Σ�0����ʾ�ж�һ�μ������
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//�Զ�װ��
	.ucPriority = 0,
	.ucSubPriority = 2,

};

tagGPIO_T tRS485_GPIO[] =
{

	 [0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,					/* GPIO���� */
	},
	[2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,					/* GPIO���� */
	},
	[3]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_11,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,					/* GPIO���� */
	},
	[4]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_2,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,					/* GPIO���� */
	},
    
};

tagGPIO_T tRS485TEST_GPIO = //���԰�485
{
	 
	.tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO���� */
	.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIOPort 			= GPIOC,					/* GPIO���� */
    
};


tagGPIO_T tRelay_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_6,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
	[2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
	[3]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_6,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    [4]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_5,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
	[5]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_4,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,				/* GPIO���� */
	},
	[6]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_3,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    [7]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_1,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
	[8]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_0,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
	[9]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,						/* GPIO���� */
	},
    [10]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,					/* GPIO���� */
	},
	[11]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_9,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,					/* GPIO���� */
	},
    
};








