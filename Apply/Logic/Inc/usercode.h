#ifndef	__USERCODE_H_
#define	__USERCODE_H_

#include <stdio.h>

#define Beiyong_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[4]); //����485����ģʽ
#define Beiyong_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[4]); //����485����ģʽ

void UserLogic_Code(void);
void Test_Code(void);

#endif
