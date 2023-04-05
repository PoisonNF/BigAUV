#ifndef __TASK_MANIPULATOR_H_
#define __TASK_MANIPULATOR_H_

#include "ocd_conf.h"

extern uint8_t Manipulator_flag; //机械手工作标志位
extern uint8_t Manipulator_Recvflag; //机械手串口数据接收完成标志
extern uint8_t Manipulator_buf[20]; //机械手串口接收缓冲区
extern uint8_t Manipulator_Uptask; //上行命令机械手任务类型

void Manipulator_SendDate(void); //机械手指令发送函数
void Manipulator_Analysis(void); //机械手数据分析函数

#endif




