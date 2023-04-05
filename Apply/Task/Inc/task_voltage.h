#ifndef __TASK_VOLTAGE_H_
#define __TASK_VOLTAGE_H_

#include "ocd_conf.h"

extern uint8_t CH438Q_buf[50]; //CH438Q串口数据接收缓冲区
extern uint8_t CH438Q_flag; //CH438Q串口数据接收完成标志
extern uint8_t CH438Q_NUM; //CH438Q串口号

int CH438Q_Analysis(float* _Altimeter_Data, uint8_t* _Lowvoltage_Data, uint8_t* Highvoltage_Data); //CH438Q串口数据获取函数

void Highvoltage_Send(void); //高压监测指令发送函数
void Lowvoltage_Send(void); //低压监测指令发送函数

#endif
