#ifndef __TASK_SMP_H_
#define __TASK_SMP_H_

#include "ocd_conf.h"

#define ShengTong_ON 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET) //声通机电源开启
#define ShengTong_OFF 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET) //声通机电源关闭
#define Manipulator_ON	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET) //机械手电源开启
#define Manipulator_OFF 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET) //机械手电源关闭
#define Front_Magnetometer_ON	 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET) //前置磁力仪电源开启
#define Front_Magnetometer_OFF 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET) //前置磁力仪电源关闭

#define CeSao_ON 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET) //侧扫声呐电源开启
#define CeSao_OFF		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET) //侧扫声呐电源关闭
#define BDGPS_ON 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET) //BD/GPS电源开启
#define BDGPS_OFF		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET) //BD/GPS电源关闭
#define Camera_ON 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET) //双目摄像电源开启
#define Camera_OFF	 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET) //双目摄像电源关闭
#define Inertial_navigation_ON		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET) //光纤惯导电源开启
#define Inertial_navigation_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET) //光纤惯导电源关闭
#define Beiyong12V_ON		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET) //备用12V电源开启
#define Beiyong12V_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET) //备用12V电源关闭

#define P360_ON 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET) //P360电源开启
#define P360_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET) //P360电源关闭
#define DVL_ON 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET) //DVL电源开启
#define DVL_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET) //DVL电源关闭
#define Altimeter_ON 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET) //高度计电源开启
#define Altimeter_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET) //高度计电源关闭
#define UHF_ON 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET) //UHF电源开启
#define UHF_OFF		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET) //UHF电源关闭

typedef struct {
	float Depthometer_Data; //深度计数据
	float Altimeter_Data; //高度计数据
	uint8_t Manipulator_Data[7]; //机械手数据
	tagMagnetometerData_T Magnetometer_L; //左梯度磁力仪数据
	tagMagnetometerData_T Magnetometer_R; //右梯度磁力仪数据
	uint8_t Lowvoltage_Data[2]; //电池低压数据
	uint8_t Highvoltage_Data[2]; //电池高压数据
	uint8_t Motor_Status[2]; //推进器工作状态
	uint8_t Other_Status[2]; //其他状态，即重心/浮心/舱门/漏水状态
	uint8_t Relay_Status[2]; //继电器状态
	uint8_t Manipulator_WorkState; //机械手工作状态
	uint8_t Manipulator_TaskType; //机械手任务类型
	uint8_t Manipulator_ErrorState; //机械手错误状态
	uint8_t Motor_Turning_State[18]; //1-9号推进器转动状态，1-4号为电压值，5-9号为PWM值
}tagUplinkData_T; //上行数据内容，发送至树莓派

extern tagUplinkData_T Uplink_Data;

extern uint8_t Shumei_RecvData[40] ; //树莓派下行数据接收 数据24字节

extern uint8_t Shumei_buf[100]; //树莓派串口接收缓冲区
extern uint8_t Shumei_flag; //树莓派串口数据接收完成标志

void ShumeiCmd_Send(void); //上行命令发送函数，即向树莓派数据应答
void ShumeiData_Send(void); //上行数据发送函数，即向树莓派数据定时发送 0.2秒发送一次到树莓派
void ShumeiData_Analysis(void); //树莓派数据解析

#endif
