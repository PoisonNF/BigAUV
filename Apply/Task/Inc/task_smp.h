#ifndef __TASK_SMP_H_
#define __TASK_SMP_H_

#include "ocd_conf.h"

typedef struct {
	float Depthometer_Data; //深度计数据
	float Altimeter_Data; //高度计数据
	uint8_t Manipulator_Data[7]; //机械手数据
	tagMagnetometerData_T Magnetometer_L; //左梯度磁力仪数据
	tagMagnetometerData_T Magnetometer_R; //右梯度磁力仪数据
	uint8_t Lowvoltage_Data[2]; //电池低压数据
	uint8_t Highvoltage_Data[2]; //电池高压数据
	uint8_t Motor_Status[2]; //推进器状态
	uint8_t Other_Status[2]; //其他状态，即重心/浮心/舱门/漏水状态
	uint8_t Relay_Status[2]; //继电器状态
}tagUplinkData_T; //上行数据内容，发送至树莓派

extern tagUplinkData_T Uplink_Data;

extern uint8_t Shumei_RecvData[30] ; //树莓派下行数据接收 数据24字节

extern uint8_t Shumei_buf[100]; //树莓派串口接收缓冲区
extern uint8_t Shumei_flag; //树莓派串口数据接收完成标志

void ShumeiCmd_Send(void); //上行命令发送函数，即向树莓派数据应答
void ShumeiData_Send(void); //上行数据发送函数，即向树莓派数据定时发送 0.2秒发送一次到树莓派
void ShumeiData_Analysis(void); //树莓派数据解析

#endif
