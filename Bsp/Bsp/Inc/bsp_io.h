#ifndef __BSP_IO_H_
#define __BSP_IO_H_

#include "drv_hal_conf.h"

/* 用户头文件包含区 */
#include "ocd_ch438q.h"
#include "ocd_ad24bit.h"
#include "sga_func.h"

extern tagGPIO_T demoGPIO[];
extern tagGPIO_T CH438Q_GPIO[];
extern tagGPIO_T CH438Q_GPIO_EXIT[];
extern tagGPIO_T RS485_GPIO[];
extern tagGPIO_T Relay_GPIO[];
extern tagGPIO_T RS485TEST_GPIO;

extern tagUART_T demoUart1;
extern tagUART_T demoUart2;
extern tagUART_T demoUart3;
extern tagUART_T demoUart4;
extern tagUART_T demoUart5;
extern tagAD24BIT_T tAD24BIT;
extern tagTIM_T tTimer2;
extern tagTIM_T tTimer3;

#endif
