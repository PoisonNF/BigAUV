#ifndef	__USERCODE_H_
#define	__USERCODE_H_

#include <stdio.h>

#define Depthometer_RS485_Recive 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[0]); //��ȼ�485����ģʽ
#define Depthometer_RS485_Send 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[0]); //��ȼ�485����ģʽ
#define Manipulator_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[1]); //��е��485����ģʽ
#define Manipulator_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[1]); //��е��485����ģʽ 
#define Lowvoltage_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[2]); //��ѹ���485����ģʽ
#define Lowvoltage_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[2]); //��ѹ���485����ģʽ
#define Highvoltage_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[3]); //��ѹ���485����ģʽ
#define Highvoltage_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[3]); //��ѹ���485����ģʽ
#define Beiyong_RS485_Recive 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);//Drv_GPIO_Reset(&RS485_GPIO[4]); //����485����ģʽ
#define Beiyong_RS485_Send 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);//Drv_GPIO_Set(&RS485_GPIO[4]); //����485����ģʽ

#define ShengTong_ON 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); //����24V��Դ����
#define ShengTong_OFF 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET); //����24V��Դ�ر�
#define Manipulator_ON	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); //��е�ֵ�Դ����
#define Manipulator_OFF 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); //��е�ֵ�Դ�ر�
#define Beiyong24V_ON	 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); //��ͨ����Դ����
#define Beiyong24V_OFF 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); //��ͨ����Դ�ر�

#define CeSao_ON 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET); //��ɨ���ŵ�Դ����
#define CeSao_OFF		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET); //��ɨ���ŵ�Դ�ر�
#define BDGPS_ON 		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET); //BD/GPS��Դ����
#define BDGPS_OFF		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET); //BD/GPS��Դ�ر�
#define Camera_ON 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET); //˫Ŀ�����Դ����
#define Camera_OFF	 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET); //˫Ŀ�����Դ�ر�
#define Inertial_navigation_ON		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET); //���˹ߵ���Դ����
#define Inertial_navigation_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET); //���˹ߵ���Դ�ر�
#define Beiyong12V_ON		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET); //����12V��Դ����
#define Beiyong12V_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET); //����12V��Դ�ر�

#define P360_ON 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET); //P360��Դ����
#define P360_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET); //P360��Դ�ر�
#define DVL_ON 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET); //DVL��Դ����
#define DVL_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET); //DVL��Դ�ر�
#define Altimeter_ON 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET); //�߶ȼƵ�Դ����
#define Altimeter_OFF 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET); //�߶ȼƵ�Դ�ر�
#define UHF_ON 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET); //UHF��Դ����
#define UHF_OFF		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET); //UHF��Դ�ر�

void UserLogic_Code(void);
void Test_Code(void);

#endif
