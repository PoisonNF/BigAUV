#ifndef	__USERCODE_H_
#define	__USERCODE_H_

#include <stdio.h>

#define Depthometer_RS485_Recive 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[0]); //深度计485接收模式
#define Depthometer_RS485_Send 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[0]); //深度计485发送模式
#define Manipulator_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[1]); //机械手485接收模式
#define Manipulator_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[1]); //机械手485发送模式 
#define Lowvoltage_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[2]); //低压监测485接收模式
#define Lowvoltage_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[2]); //低压监测485发送模式
#define Highvoltage_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[3]); //高压监测485接收模式
#define Highvoltage_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[3]); //高压监测485发送模式
#define Beiyong_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[4]); //备用485接收模式
#define Beiyong_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[4]); //备用485发送模式

#define ShengTong_ON 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); //备用24V电源开启
#define ShengTong_OFF 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET); //备用24V电源关闭
#define Manipulator_ON	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); //机械手电源开启
#define Manipulator_OFF 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); //机械手电源关闭
#define Beiyong24V_ON	 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); //声通机电源开启
#define Beiyong24V_OFF 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); //声通机电源关闭

#define CeSao_ON 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET); //侧扫声呐电源开启
#define CeSao_OFF		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET); //侧扫声呐电源关闭
#define BDGPS_ON 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET); //BD/GPS电源开启
#define BDGPS_OFF		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET); //BD/GPS电源关闭
#define Camera_ON 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET); //双目摄像电源开启
#define Camera_OFF	 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET); //双目摄像电源关闭
#define Inertial_navigation_ON		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET); //光纤惯导电源开启
#define Inertial_navigation_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET); //光纤惯导电源关闭
#define Beiyong12V_ON		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET); //备用12V电源开启
#define Beiyong12V_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET); //备用12V电源关闭

#define P360_ON 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET); //P360电源开启
#define P360_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET); //P360电源关闭
#define DVL_ON 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET); //DVL电源开启
#define DVL_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET); //DVL电源关闭
#define Altimeter_ON 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET); //高度计电源开启
#define Altimeter_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET); //高度计电源关闭
#define UHF_ON 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET); //UHF电源开启
#define UHF_OFF		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET); //UHF电源关闭

void UserLogic_Code(void);
void Test_Code(void);

#endif
