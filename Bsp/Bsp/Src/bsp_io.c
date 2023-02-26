#include "bsp_io.h"

/* GPIO���ʾ�� */
tagGPIO_T demoGPIO[] =
{
	
	/* AD24BIT CS */
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
//	[0]=
//	{ 
//		.tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO���� */
//		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
//		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
//		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
//		.tGPIOPort 			= GPIOD,					/* GPIO���� */
//	},
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

/* ���ھ��ʾ�� */
tagUART_T demoUart1 = 
{
	.tUARTHandle.Instance 				= USART1,			/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 115200,				/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* �ж����ȼ� */
	.ulSubPriority						= 3,				/* �ж������ȼ� */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_9,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 			= GPIOA,					/* GPIO���� */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 			= GPIOA,					/* GPIO���� */
};

tagUART_T demoUart2 = 
{
	.tUARTHandle.Instance 				= USART2,			/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* �ж����ȼ� */
	.ulSubPriority						= 3,				/* �ж������ȼ� */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_2,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 			= GPIOA,					/* GPIO���� */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_3,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 			= GPIOA,					/* GPIO���� */
};

tagUART_T demoUart3 = 
{
	.tUARTHandle.Instance 				= USART3,			/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* �ж����ȼ� */
	.ulSubPriority						= 3,				/* �ж������ȼ� */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 			= GPIOB,					/* GPIO���� */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_11,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 			= GPIOB,					/* GPIO���� */
};

tagUART_T demoUart4 = 
{
	.tUARTHandle.Instance 				= UART4,			/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* �ж����ȼ� */
	.ulSubPriority						= 3,				/* �ж������ȼ� */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 			= GPIOC,					/* GPIO���� */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_11,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 			= GPIOC,					/* GPIO���� */
};

tagUART_T demoUart5 = 
{
	.tUARTHandle.Instance 				= UART5,			/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* �ж����ȼ� */
	.ulSubPriority						= 3,				/* �ж������ȼ� */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 			= GPIOC,					/* GPIO���� */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_2,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 			= GPIOD,					/* GPIO���� */
};

tagGPIO_T CH438Q_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_6,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,					/* GPIO���� */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | 
			GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8| GPIO_PIN_13| GPIO_PIN_14,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOC,					/* GPIO���� */
	},
    
};

tagGPIO_T CH438Q_GPIO_EXIT[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_0,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_IT_FALLING,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_PULLUP,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
	
};

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

tagTIM_T tTimer3 = 
{
	.tTimerHandle.Instance				=TIM3,						/* ͨ�ö�ʱ��3 */
	.tTimerHandle.Init.Prescaler		=7200-1,						 //((1+Prescaler )/72M)*(1+Period )//��ʱ��Сʱ����ģ�
	.tTimerHandle.Init.Period			=1000-1,				//100mS����һ�����
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* ����Ƶ */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* ���ϼ����� */
	.tTimerHandle.Init.RepetitionCounter = 0, //������������ٴκ��ж�һ�Σ�0����ʾ�ж�һ�μ������
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//�Զ�װ��
	.ulPriority = 0,
	.ulSubPriority = 2,
};

tagTIM_T tTimer2 = 
{
	.tTimerHandle.Instance				=TIM2,						/* ͨ�ö�ʱ��2 */
	.tTimerHandle.Init.Prescaler		=7200-1,						/* ��Ƶϵ�������ֵ65535 */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* ���ϼ����� */
	.tTimerHandle.Init.Period			=5000-1,					//0.5S����һ�����
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* ʱ�ӷ�Ƶ���� */
	.tTimerHandle.Init.RepetitionCounter = 0, //������������ٴκ��ж�һ�Σ�0����ʾ�ж�һ�μ������
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//�Զ�װ��
	.ulPriority = 0,
	.ulSubPriority = 2,
};

tagGPIO_T RS485_GPIO[] =
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

tagGPIO_T RS485TEST_GPIO = //���԰�485
{
	 
	.tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO���� */
	.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIOPort 			= GPIOC,					/* GPIO���� */
    
};

tagGPIO_T Relay_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7 | GPIO_PIN_6,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_1 | GPIO_PIN_0,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
	[2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,					/* GPIO���� */
	},
    
};

