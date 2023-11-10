#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "drv_hal_conf.h"
#include "ocd_conf.h"

/* 用户句柄声明包含区 */

extern tagGPIO_T tLED_GPIO[];
extern tagGPIO_T tAD_GPIO;
extern tagUART_T tSMP_Uart;
extern tagUART_T tTKC_Uart;
extern tagUART_T tManipulator_Uart;
extern tagUART_T tDepthometer_Uart;
extern tagUART_T tStandby_Uart;
extern tagGPIO_T tCH438Q_GPIO[];
extern tagGPIO_T tCH438Q_EXIT_GPIO;
extern tagAD24BIT_T tAD24BIT;
extern tagTIM_T tTimer4;
extern tagTIM_T tTimer3;
extern tagTIM_T tTimer2;
extern tagGPIO_T tRS485_GPIO[];
extern tagGPIO_T tRS485TEST_GPIO;
extern tagGPIO_T tRelay_GPIO[];

#endif


