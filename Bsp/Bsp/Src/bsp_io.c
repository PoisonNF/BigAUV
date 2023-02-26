#include "bsp_io.h"

/* GPIO句柄示例 */
tagGPIO_T demoGPIO[] =
{
	
	/* AD24BIT CS */
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
//	[0]=
//	{ 
//		.tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO引脚 */
//		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
//		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
//		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
//		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
//	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
    [2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
    
};

/* 串口句柄示例 */
tagUART_T demoUart1 = 
{
	.tUARTHandle.Instance 				= USART1,			/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 115200,				/* 串口波特率 */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* 中断优先级 */
	.ulSubPriority						= 3,				/* 中断子优先级 */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_9,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 			= GPIOA,					/* GPIO分组 */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 			= GPIOA,					/* GPIO分组 */
};

tagUART_T demoUart2 = 
{
	.tUARTHandle.Instance 				= USART2,			/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* 串口波特率 */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* 中断优先级 */
	.ulSubPriority						= 3,				/* 中断子优先级 */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_2,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 			= GPIOA,					/* GPIO分组 */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_3,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 			= GPIOA,					/* GPIO分组 */
};

tagUART_T demoUart3 = 
{
	.tUARTHandle.Instance 				= USART3,			/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* 串口波特率 */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* 中断优先级 */
	.ulSubPriority						= 3,				/* 中断子优先级 */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 			= GPIOB,					/* GPIO分组 */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_11,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 			= GPIOB,					/* GPIO分组 */
};

tagUART_T demoUart4 = 
{
	.tUARTHandle.Instance 				= UART4,			/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* 串口波特率 */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* 中断优先级 */
	.ulSubPriority						= 3,				/* 中断子优先级 */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 			= GPIOC,					/* GPIO分组 */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_11,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 			= GPIOC,					/* GPIO分组 */
};

tagUART_T demoUart5 = 
{
	.tUARTHandle.Instance 				= UART5,			/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* 串口波特率 */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	//.tRxInfo.usRxLenth                  = 100,                 /* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* 中断优先级 */
	.ulSubPriority						= 3,				/* 中断子优先级 */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 			= GPIOC,					/* GPIO分组 */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_2,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 			= GPIOD,					/* GPIO分组 */
};

tagGPIO_T CH438Q_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_6,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,					/* GPIO分组 */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | 
			GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8| GPIO_PIN_13| GPIO_PIN_14,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOC,					/* GPIO分组 */
	},
    
};

tagGPIO_T CH438Q_GPIO_EXIT[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_0,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_IT_FALLING,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_PULLUP,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
	
};

tagAD24BIT_T tAD24BIT =
{
	.tSPI.tSPIHandle.Instance 				= SPI2,

	.tSPI.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO引脚 ,SPI2_SCK*/
	.tSPI.tGPIO[0].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tSPI.tGPIO[0].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tSPI.tGPIO[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tSPI.tGPIO[0].tGPIOPort 			= GPIOB,					/* GPIO分组 */
	
	.tSPI.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO引脚 ,SPI2_MOSI*/
	.tSPI.tGPIO[1].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tSPI.tGPIO[1].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tSPI.tGPIO[1].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tSPI.tGPIO[1].tGPIOPort 			= GPIOB,					/* GPIO分组 */
	
	.tSPI.tGPIO[2].tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO引脚 ,SPI2_MISO*/
	.tSPI.tGPIO[2].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tSPI.tGPIO[2].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tSPI.tGPIO[2].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tSPI.tGPIO[2].tGPIOPort 			= GPIOB,					/* GPIO分组 */
	
	.port_num = 6,  //测量的端口数，跟下面配置的端口对应起来
	.port[0].enable = PORT_ENABLE,//端口使能
	.port[0].num = VIN0,  //采集信号的,单端模式，信号的地接Vincom端口;差分模式，信号接对应端口
	.port[0].gain = 1.001068,  //校正参数增益Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;
	.port[0].offset= 0.0,//校正参数偏移量Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;

	.port[1].enable = PORT_ENABLE,
	.port[1].num = VIN1,	//采集信号的,单端模式，信号的地接Vincom端口;差分模式，信号接对应端口
	.port[1].gain = 1.00105,  //校正参数增益Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;
	.port[1].offset= 0.0006,//校正参数偏移量Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;
	
	.port[2].enable = PORT_ENABLE,
	.port[2].num = VIN2,	//采集信号的,单端模式，信号的地接Vincom端口;差分模式，信号接对应端口
	.port[2].gain = 1.001176,  //校正参数增益Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;
	.port[2].offset= 0.0004,//校正参数偏移量Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;

	.port[3].enable = PORT_ENABLE,//端口使能
	.port[3].num = VIN3,  //采集信号的,单端模式，信号的地接Vincom端口;差分模式，信号接对应端口
	.port[3].gain = 1.001068,  //校正参数增益Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;
	.port[3].offset= 0.0,//校正参数偏移量Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;

	.port[4].enable = PORT_ENABLE,
	.port[4].num = VIN4,	//采集信号的,单端模式，信号的地接Vincom端口;差分模式，信号接对应端口
	.port[4].gain = 1.00105,  //校正参数增益Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;
	.port[4].offset= 0.0006,//校正参数偏移量Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;
	
	.port[5].enable = PORT_ENABLE,
	.port[5].num = VIN5,	//采集信号的,单端模式，信号的地接Vincom端口;差分模式，信号接对应端口
	.port[5].gain = 1.001176,  //校正参数增益Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;
	.port[5].offset= 0.0004,//校正参数偏移量Y =  gain*X+offset,若不需要校正则默认gain = 1.0,offset = 0.0;
};

tagTIM_T tTimer3 = 
{
	.tTimerHandle.Instance				=TIM3,						/* 通用定时器3 */
	.tTimerHandle.Init.Prescaler		=7200-1,						 //((1+Prescaler )/72M)*(1+Period )//定时最小时间节拍，
	.tTimerHandle.Init.Period			=1000-1,				//100mS产生一次溢出
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* 不分频 */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* 向上计数器 */
	.tTimerHandle.Init.RepetitionCounter = 0, //计数器溢出多少次后，中断一次，0：表示中断一次即溢出。
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//自动装载
	.ulPriority = 0,
	.ulSubPriority = 2,
};

tagTIM_T tTimer2 = 
{
	.tTimerHandle.Instance				=TIM2,						/* 通用定时器2 */
	.tTimerHandle.Init.Prescaler		=7200-1,						/* 分频系数，最大值65535 */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* 向上计数器 */
	.tTimerHandle.Init.Period			=5000-1,					//0.5S产生一次溢出
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* 时钟分频因子 */
	.tTimerHandle.Init.RepetitionCounter = 0, //计数器溢出多少次后，中断一次，0：表示中断一次即溢出。
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//自动装载
	.ulPriority = 0,
	.ulSubPriority = 2,
};

tagGPIO_T RS485_GPIO[] =
{
	 [0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,					/* GPIO分组 */
	},
	[2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,					/* GPIO分组 */
	},
	[3]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_11,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,					/* GPIO分组 */
	},
	[4]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_2,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,					/* GPIO分组 */
	},
    
};

tagGPIO_T RS485TEST_GPIO = //测试板485
{
	 
	.tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO引脚 */
	.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
	.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIOPort 			= GPIOC,					/* GPIO分组 */
    
};

tagGPIO_T Relay_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7 | GPIO_PIN_6,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_1 | GPIO_PIN_0,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
	[2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,					/* GPIO分组 */
	},
    
};

