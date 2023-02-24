#include "task_conf.h"

static tagDS3231Time_T	s_tSysTime;

unsigned char Task_TimeDataGet(void)
{
	/* ��ȡ����ʱ�䣬��������ʱ��-��������Ƶ�� <= ��ǰʱ�� */
	OCD_DS3231_TimeGetHex(&tDS3231, &s_tSysTime);
	
	/* ���Ӵ��ڣ�ֱ�ӷ����� */
		
	/* ����ڣ������� */
	
	return 1;
}

tagDS3231Time_T Task_TimeGet(void)
{
	return s_tSysTime;
}

void Task_SysTimeConfig(uint8_t *_ucpData)
{
	s_tSysTime.ucYear = SGA_StringToHex(_ucpData + 4, 2);
	s_tSysTime.ucMonth = SGA_StringToHex(_ucpData + 6, 2);
	s_tSysTime.ucDate = SGA_StringToHex(_ucpData + 8, 2);
	s_tSysTime.ucHour = SGA_StringToHex(_ucpData + 10, 2);
	s_tSysTime.ucMinute = SGA_StringToHex(_ucpData + 12, 2);
	s_tSysTime.ucSecond = SGA_StringToHex(_ucpData + 14, 2);
	
	OCD_DS3231_TimeSetHex(&tDS3231, &s_tSysTime);
	
#ifdef DEBUG_ENABLE
	OCD_DS3231_TimeGetHex(&tDS3231, &s_tSysTime);
	printf("Sys Time->20%02x-%02x-%02x %02x:%02x:%02x\r\n", s_tSysTime.ucYear, s_tSysTime.ucMonth, s_tSysTime.ucDate, s_tSysTime.ucHour, s_tSysTime.ucMinute, s_tSysTime.ucSecond);
#endif
}

void Task_DS1337_Test(void)
{
	printf("Write Time:20%02x/%02x/%02x %02x:%02x:%02x\r\n", s_tSysTime.ucYear, s_tSysTime.ucMonth, s_tSysTime.ucDate, s_tSysTime.ucHour, s_tSysTime.ucMinute, s_tSysTime.ucSecond);
	OCD_DS3231_TimeSetHex(&tDS3231, &s_tSysTime);
	printf("Delay 5S!\r\n");
	Drv_Delay_Ms(5000);
	OCD_DS3231_TimeGetHex(&tDS3231, &s_tSysTime);
	printf("Read Time:20%02x/%02x/%02x %02x:%02x:%02x\r\n", s_tSysTime.ucYear, s_tSysTime.ucMonth, s_tSysTime.ucDate, s_tSysTime.ucHour, s_tSysTime.ucMinute, s_tSysTime.ucSecond);
}
