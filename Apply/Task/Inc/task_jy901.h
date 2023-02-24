#ifndef __TASKJY901COM_H_
#define __TASKJY901COM_H_

#include "bsp_io.h"

unsigned char Task_JY901DataProcess(void);
void Task_JY901RxITEnable(void);
tagIMU_T *Task_IMUGet(void);

#endif
