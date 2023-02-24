#include "task_conf.h"

void Task_Led_GreenOn(void)
{
	Drv_GPIO_Reset(&LED_GREEN);
	Drv_GPIO_Set(&LED_BLUE);
	Drv_GPIO_Set(&LED_RED);
	
	printf("Green Led On!!!\r\n");
}

void Task_Led_RedOn(void)
{
	Drv_GPIO_Set(&LED_GREEN);
	Drv_GPIO_Set(&LED_BLUE);
	Drv_GPIO_Reset(&LED_RED);
	
	printf("Red Led On!!!\r\n");
}

void Task_Led_BlueOn(void)
{
	Drv_GPIO_Set(&LED_GREEN);
	Drv_GPIO_Reset(&LED_BLUE);
	Drv_GPIO_Set(&LED_RED);
	
	printf("Blue Led On!!!\r\n");
}

void Task_Led_AllOff(void)
{
	Drv_GPIO_Set(&LED_GREEN);
	Drv_GPIO_Set(&LED_BLUE);
	Drv_GPIO_Set(&LED_RED);
	
	printf("All Led Off!!!\r\n");
}
