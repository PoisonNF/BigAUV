#include "config.h"

/* 核心板三基色灯光显示 */
tagGPIO_T tLED_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
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

tagGPIO_T tAD_GPIO =
{

	/* AD24BIT CS */
	.tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO引脚 */
	.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
	.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIOPort 			= GPIOB,					/* GPIO分组 */

};



/* 树莓派通信 */
tagUART_T tSMP_Uart = 
{

	//串口工作模式配置
	.tUARTHandle.Instance 				= USART1,					/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 115200,					/* 串口波特率 */
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
	
	.ucPriority							= 1,						/* 中断优先级 */
	.ucSubPriority						= 3,						/* 中断子优先级 */
	
	//串口DMA接收参数配置
	.tUartDMA.bRxEnable					= true,						/* DMA接收使能 */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel5,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	/* 在使用DMA发送后，测试发现150字节才能使深度计正常工作 */
	.tRxInfo.usDMARxMAXSize             	= 150,              	/* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/

	.tUartDMA.ucDMARxPriority				= 1,					/* DMA接收中断优先级 */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA接收中断子优先级 */
	
	//串口DMA发送参数配置
	.tUartDMA.bTxEnable					= true,						/* DMA发送使能 */
	.tUartDMA.tDMATx.Instance			= DMA1_Channel4,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 100,						/* 最大发送数据长度 */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA发送中断优先级 */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA发送中断子优先级 */

	//串口GPIO配置
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_9,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO重映射 */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO重映射 */

};

/* 推控舱通信 */
tagUART_T tTKC_Uart = 
{

	//串口工作模式配置
	.tUARTHandle.Instance 				= USART2,					/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 9600,						/* 串口波特率 */
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
	
	.ucPriority							= 1,						/* 中断优先级 */
	.ucSubPriority						= 3,						/* 中断子优先级 */
	
	//串口DMA接收参数配置
	.tUartDMA.bRxEnable					= true,						/* DMA接收使能 */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel6,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tRxInfo.usDMARxMAXSize             	= 100,              	/* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/

	.tUartDMA.ucDMARxPriority				= 2,					/* DMA接收中断优先级 */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA接收中断子优先级 */
	
	//串口DMA发送参数配置
	.tUartDMA.bTxEnable					= true,						/* DMA发送使能 */
	.tUartDMA.tDMATx.Instance			= DMA1_Channel7,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 50,						/* 最大发送数据长度 */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA发送中断优先级 */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA发送中断子优先级 */

	//串口GPIO配置
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO重映射 */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_3,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO重映射 */

};

/* 机械手通信 */
tagUART_T tManipulator_Uart = 
{

	//串口工作模式配置
	.tUARTHandle.Instance 				= USART3,					/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 9600,						/* 串口波特率 */
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
	
	.ucPriority							= 3,						/* 中断优先级 */
	.ucSubPriority						= 3,						/* 中断子优先级 */
	
	//串口DMA接收参数配置
	.tUartDMA.bRxEnable					= true,						/* DMA接收使能 */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel3,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	/* 原先给的100字节太大了，导致无法正确接收数据 */
	.tRxInfo.usDMARxMAXSize             	= 20,              	/* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/

	.tUartDMA.ucDMARxPriority				= 2,					/* DMA接收中断优先级 */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA接收中断子优先级 */
	
	//串口DMA发送参数配置
	.tUartDMA.bTxEnable					= true,						/* DMA发送使能 */
	.tUartDMA.tDMATx.Instance			= DMA1_Channel2,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 20,						/* 最大发送数据长度 */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA发送中断优先级 */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA发送中断子优先级 */

	//串口GPIO配置
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 				= GPIOB,					/* GPIO分组 */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO重映射 */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_11,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 				= GPIOB,					/* GPIO分组 */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO重映射 */

};

/* 深度计通信 */
tagUART_T tDepthometer_Uart = 
{

	//串口工作模式配置
	.tUARTHandle.Instance 				= UART4,					/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 9600,						/* 串口波特率 */
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
	
	.ucPriority							= 3,						/* 中断优先级 */
	.ucSubPriority						= 3,						/* 中断子优先级 */
	
	//串口DMA接收参数配置
	.tUartDMA.bRxEnable					= true,						/* DMA接收使能 */
	.tUartDMA.tDMARx.Instance			= DMA2_Channel3,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tRxInfo.usDMARxMAXSize             	= 20,              	/* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/

	.tUartDMA.ucDMARxPriority				= 1,					/* DMA接收中断优先级 */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA接收中断子优先级 */
	
	//串口DMA发送参数配置
	.tUartDMA.bTxEnable					= true,						/* DMA发送使能 */
	.tUartDMA.tDMATx.Instance			= DMA2_Channel5,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 50,						/* 最大发送数据长度 */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA发送中断优先级 */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA发送中断子优先级 */

	//串口GPIO配置
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 				= GPIOC,					/* GPIO分组 */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO重映射 */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_11,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 				= GPIOC,					/* GPIO分组 */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO重映射 */

};

/* 备用串口通信 */
tagUART_T tStandby_Uart = 
{

	//串口工作模式配置
	.tUARTHandle.Instance 				= UART5,					/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 9600,						/* 串口波特率 */
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
	
	.ucPriority							= 1,						/* 中断优先级 */
	.ucSubPriority						= 3,						/* 中断子优先级 */
	
	//串口DMA接收参数配置
	.tUartDMA.bRxEnable					= true,						/* DMA接收使能 */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel3,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tRxInfo.usDMARxMAXSize             	= 100,              	/* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/

	.tUartDMA.ucDMARxPriority				= 1,					/* DMA接收中断优先级 */
	.tUartDMA.ucDMARxSubPriority			= 1,					/* DMA接收中断子优先级 */
	
	//串口DMA发送参数配置
	.tUartDMA.bTxEnable					= true,						/* DMA发送使能 */
	.tUartDMA.tDMATx.Instance			= DMA1_Channel2,
	.tUartDMA.tDMATx.Init.Direction		= DMA_MEMORY_TO_PERIPH,
	.tUartDMA.tDMATx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMATx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMATx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMATx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMATx.Init.Priority		= DMA_PRIORITY_LOW,

	.tTxInfo.usDMATxMAXSize				= 50,						/* 最大发送数据长度 */
	
	.tUartDMA.ucDMATxPriority				= 1,					/* DMA发送中断优先级 */
	.tUartDMA.ucDMATxSubPriority			= 1,					/* DMA发送中断子优先级 */

	//串口GPIO配置
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_12,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 				= GPIOC,					/* GPIO分组 */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO重映射 */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 				= GPIOD,					/* GPIO分组 */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO重映射 */

};

/* CH438Q芯片GPIO */
tagGPIO_T tCH438Q_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin			= GPIO_PIN_0,			/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,											/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,													/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,											/* GPIO速度 */	
		.tGPIOPort 				= GPIOE,														/* GPIO分组 */
	},
	[1]=
	{ 
		.tGPIOInit.Pin			= GPIO_PIN_1,			/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,											/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,													/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,											/* GPIO速度 */	
		.tGPIOPort 				= GPIOE,														/* GPIO分组 */
	},
	[2]=
	{ 
		.tGPIOInit.Pin			= GPIO_PIN_2,			/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,											/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,													/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,											/* GPIO速度 */	
		.tGPIOPort 				= GPIOE,														/* GPIO分组 */
	},
	[3]=
	{ 
		.tGPIOInit.Pin			= GPIO_PIN_6,			/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,											/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,													/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,											/* GPIO速度 */	
		.tGPIOPort 				= GPIOE,														/* GPIO分组 */
	},
    [4]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_0,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[5]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_1,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[6]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[7]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_3,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[8]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_4,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[9]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_5,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[10]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_6,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[11]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_7,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[12]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_8,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[13]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_13,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
	[14]=
	{ 
		.tGPIOInit.Pin 			= GPIO_PIN_14,				/* GPIO引脚 */
		.tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 				= GPIOC,					/* GPIO分组 */
	},
    
};

/* CH438Q外部中断GPIO */
tagGPIO_T tCH438Q_EXIT_GPIO =
{
	
	.tGPIOInit.Pin		= GPIO_PIN_0,				/* GPIO引脚 */
	.tGPIOInit.Mode 	= GPIO_MODE_IT_FALLING,		/* GPIO模式 */
	.tGPIOInit.Pull 	= GPIO_PULLUP,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	
	.ucPriority = 0,
	.ucSubPriority = 2,
	
};

/* AD芯片配置 */
tagAD24BIT_T tAD24BIT =
{
	.tSPI.tSPIHandle.Instance 				= SPI2,		.tSPI.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO引脚 ,SPI2_SCK*/
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
	.tSPI.tGPIO[2].tGPIOPort 			= GPIOB,					/* GPIO分组 */		.tSPI.tGPIO[3].tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO引脚 ,CS*/
	.tSPI.tGPIO[3].tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
	.tSPI.tGPIO[3].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tSPI.tGPIO[3].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tSPI.tGPIO[3].tGPIOPort 			= GPIOB,					/* GPIO分组 */	
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

/* 定时器4配置 */
tagTIM_T tTimer4 = 
{

	.tTimerHandle.Instance				=TIM4,						/* 通用定时器4 */
	.tTimerHandle.Init.Prescaler		=7200-1,						 //((1+Prescaler )/72M)*(1+Period )//定时最小时间节拍，
	.tTimerHandle.Init.Period			=8000-1,				//100mS产生一次溢出
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* 不分频 */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* 向上计数器 */
	.tTimerHandle.Init.RepetitionCounter = 0, //计数器溢出多少次后，中断一次，0：表示中断一次即溢出。
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//自动装载
	.ucPriority = 0,
	.ucSubPriority = 2,

};

/* 定时器3配置 */
tagTIM_T tTimer3 = 
{

	.tTimerHandle.Instance				=TIM3,						/* 通用定时器3 */
	.tTimerHandle.Init.Prescaler		=7200-1,						 //((1+Prescaler )/72M)*(1+Period )//定时最小时间节拍，
	.tTimerHandle.Init.Period			=1000-1,				//100mS产生一次溢出
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* 不分频 */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* 向上计数器 */
	.tTimerHandle.Init.RepetitionCounter = 0, //计数器溢出多少次后，中断一次，0：表示中断一次即溢出。
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//自动装载
	.ucPriority = 0,
	.ucSubPriority = 2,

};

/* 定时器2配置 */
tagTIM_T tTimer2 = 
{

	.tTimerHandle.Instance				=TIM2,						/* 通用定时器2 */
	.tTimerHandle.Init.Prescaler		=7200-1,						/* 分频系数，最大值65535 */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* 向上计数器 */
	.tTimerHandle.Init.Period			=5000-1,					//0.5S产生一次溢出
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* 时钟分频因子 */
	.tTimerHandle.Init.RepetitionCounter = 0, //计数器溢出多少次后，中断一次，0：表示中断一次即溢出。
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//自动装载
	.ucPriority = 0,
	.ucSubPriority = 2,

};

/* 定时器6配置 */
tagTIM_T tTimer6 = 
{

	.tTimerHandle.Instance				=TIM6,						/* 通用定时器2 */
	.tTimerHandle.Init.Prescaler		=7200-1,						/* 分频系数，最大值65535 */
	.tTimerHandle.Init.CounterMode		=TIM_COUNTERMODE_UP,		/* 向上计数器 */
	.tTimerHandle.Init.Period			=20000-1,					//2S产生一次溢出
	.tTimerHandle.Init.ClockDivision	=TIM_CLOCKDIVISION_DIV1,	/* 时钟分频因子 */
	.tTimerHandle.Init.RepetitionCounter = 0, //计数器溢出多少次后，中断一次，0：表示中断一次即溢出。
	.tTimerHandle.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_ENABLE,//自动装载
	.ucPriority = 0,
	.ucSubPriority = 2,

};

tagGPIO_T tRS485_GPIO[] =
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

tagGPIO_T tRS485TEST_GPIO = //测试板485
{
	 
	.tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO引脚 */
	.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
	.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIOPort 			= GPIOC,					/* GPIO分组 */
    
};


tagGPIO_T tRelay_GPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_6,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
	[2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
	[3]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_6,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
    [4]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_5,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
	[5]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_4,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,				/* GPIO分组 */
	},
	[6]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_3,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
    [7]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_1,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
	[8]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_0,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
	[9]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_7,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,						/* GPIO分组 */
	},
    [10]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,					/* GPIO分组 */
	},
	[11]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_9,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,					/* GPIO分组 */
	},
    
};








