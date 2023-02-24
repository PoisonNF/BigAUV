#ifndef __TASK_FATFS_H_
#define __TASK_FATFS_H_

#include "bsp_io.h"

void Task_FATFSDataSave(void);
void Task_FATFSDataRead(void);
void Task_FATFSReadDir(void);
void Task_FATFSSendFile(uint8_t *_ucpFileName);

#endif
