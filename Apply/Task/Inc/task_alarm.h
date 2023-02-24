#ifndef __TASK_ALARM_H_
#define __TASK_ALARM_H_

#include "bsp_io.h"

void Task_AlarmpSet(void);
void Task_AlarmFreqSet(unsigned int _ulFreq);
uint32_t Task_AlarmFreqRead(void);
bool Task_AlarmCheck(void);
bool Task_ComTimerCheck(void);
bool Task_IMUTimerCheck(void);
bool Task_MagTimerCheck(void);
bool Task_CMDTimerCheck(void);
void Task_CMDTimerClear(void);
uint8_t Task_AlarmFreqCheck(void);
void Task_AlarmInit(void);

#endif
