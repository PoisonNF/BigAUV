#ifndef __TASK_DEPTHOMETER_H_
#define __TASK_DEPTHOMETER_H_

#include "ocd_conf.h"

int Depthometer_Analysis(float* _Depthometer_Data); //深度计数据获取函数
void Depthometer_Send(void); //深度计指令发送函数

extern uint8_t Depthometer_buf[20]; //深度计串口接收缓冲区
extern uint8_t Depthometer_flag; //深度计串口数据接收完成标志

#endif
