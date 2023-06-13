#ifndef __TASK_TKC_H_
#define __TASK_TKC_H_

#include "ocd_conf.h"

typedef struct {
    uint8_t Pose_Velocity_Data[24]; //树莓派下行数据中 位姿速度信息
	float Depthometer_Data; //深度计数据
	float Altimeter_Data; //高度计数据
	uint8_t Cursor_Coordinate[4]; //光标坐标
}tagDownlinkData_T; //下行数据内容，发送至推控舱

extern tagDownlinkData_T Downlink_Data;

extern uint8_t Hatchdoor_flag; //舱门开关标志位

extern uint8_t Tuikong_buf[50]; //推控舱串口接收缓冲区
extern uint8_t Tuikong_flag; //推控舱串口数据接收完成标志

void TuikongData_Analysis(void); //推控舱数据解析
void TuikongData_Send(void); //下行数据发送函数，即向推控舱数据定时发送 0.5秒发送一次到推控舱

#endif
