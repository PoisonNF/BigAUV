#ifndef __TASK_UART_H_
#define __TASK_UART_H_

#include "ocd_conf.h"

void Task_PCUart_Enable(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);

//unsigned char Task_PCListen(void);
//uint8_t *Task_GetPCUart(void);

#endif
