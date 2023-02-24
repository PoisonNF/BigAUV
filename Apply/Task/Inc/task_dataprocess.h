#ifndef __TASK_DATAPROCESS_H_
#define __TASK_DATAPROCESS_H_

#include "bsp_io.h"

#define COM_FREQ_ONCE	0x00
#define COM_FREQ_10HZ	0x01
#define COM_FREQ_ELSE	0x02

#define CACHE_LENGTH		77

char* Task_CacheGet(void);
void Task_Send(void);
void Task_CacheUpdate(void);

#endif
