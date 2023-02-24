#ifndef __TASKDS1337_H_
#define __TASKDS1337_H_

#include "bsp_io.h"

#define DS1337_OK				0x01
#define DS1337_ERROR			0x02
#define DS1337_GETTIME_ERROR	0x03
#define DS1337_ALARMSET_ERROR	0x04

tagDS3231Time_T Task_TimeGet(void);
unsigned char Task_TimeDataGet(void);
void Task_SysTimeConfig(uint8_t *_ucpData);

#endif
