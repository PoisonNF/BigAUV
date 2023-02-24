#include "task_conf.h"

static tagDS3231Time_T s_tAlarmTime;
static bool s_ucAlarmFlg = false;
static uint32_t s_ulAlarmFreq = 2;		/* 单位ms */

void Task_EXTI3_IRQHandler(void)
{
	s_ucAlarmFlg = true;
}

static void S_AlarmConfig(tagDS3231Time_T *_tTimeASCII, uint32_t _ulAddTime)
{
	uint8_t ucRes;
	
	ucRes = _ulAddTime/1000;	/* ms转s */
	
	_tTimeASCII->ucSecond += SGA_DecToHex(ucRes % 60);
	if((_tTimeASCII->ucSecond & 0x0f) > 9)
	{
		_tTimeASCII->ucSecond -= 0x0a;
		_tTimeASCII->ucSecond += 0x10;
	}
	if(_tTimeASCII->ucSecond >= 0x60)
	{
		_tTimeASCII->ucSecond -= 0x60;
		_tTimeASCII->ucMinute += 1;
	}
	
	_tTimeASCII->ucMinute += SGA_DecToHex(ucRes % 3600 / 60);
	if((_tTimeASCII->ucMinute & 0x0f) > 9)
	{
		_tTimeASCII->ucMinute -= 0x0a;
		_tTimeASCII->ucMinute += 0x10;
	}
	if(_tTimeASCII->ucMinute >= 0x5a)
	{
		_tTimeASCII->ucMinute -= 0x60;
		_tTimeASCII->ucHour += 1;
	}
	
	_tTimeASCII->ucHour += SGA_DecToHex(ucRes % 86400 / 3600);
	if((_tTimeASCII->ucHour & 0x0f) > 9)
	{
		_tTimeASCII->ucHour -= 0x0a;
		_tTimeASCII->ucHour += 0x10;
	}
	if(_tTimeASCII->ucHour >= 0x24)
	{
		_tTimeASCII->ucHour -= 0x24;
	}
}

bool Task_AlarmCheck(void)
{
	if(s_ucAlarmFlg)
	{
		s_ucAlarmFlg = false;
		return true;
	}
	
	return false;
}

tagDS3231Time_T Task_AlarmGet(void)
{
	return s_tAlarmTime;
}

#define SYS_CONF_LENGH	5
#define ALARMFREQ_ADDR	0x00
static uint8_t s_ucpSysConf[SYS_CONF_LENGH] = {0};
uint32_t Task_AlarmFreqRead(void)
{
	if(OCD_AT24CXX_Check(&tAT24CXX))
	{
		OCD_AT24CXX_ReadLenByte(&tAT24CXX, ALARMFREQ_ADDR, s_ucpSysConf, SYS_CONF_LENGH);
		s_ulAlarmFreq = atoi((const char*)s_ucpSysConf);
		return s_ulAlarmFreq;
	}

	else
	{
#ifdef DEBUG_ENABLE
		printf("AT24CXX Error!\r\n");
#endif
		Task_Led_RedOn();
		return 0;
	}
}

static void S_Task_AlarmFreqSave(void)
{
	sprintf((char*)s_ucpSysConf, "%05d", s_ulAlarmFreq);
	OCD_AT24CXX_WriteLenByte(&tAT24CXX, ALARMFREQ_ADDR, s_ucpSysConf, SYS_CONF_LENGH);
#ifdef DEBUG_ENABLE
	OCD_AT24CXX_ReadLenByte(&tAT24CXX, ALARMFREQ_ADDR, s_ucpSysConf, SYS_CONF_LENGH);
	printf("Alarm Freq->%05x\r\n", SGA_StringToHex(s_ucpSysConf, 5));
#endif
}

void Task_AlarmFreqSet(uint32_t _ulFreq)
{
	s_ulAlarmFreq = _ulFreq;
	S_Task_AlarmFreqSave();
	Task_AlarmInit();
}

void Task_AlarmpSet(void)
{
	S_AlarmConfig(&s_tAlarmTime, s_ulAlarmFreq);
	OCD_DS3231_Alarm1ConfigHex(&tDS3231, &s_tAlarmTime);
}

static uint8_t s_ucComFreq = COM_FREQ_ELSE;
void Task_AlarmInit(void)
{
	OCD_DS3231_TimeGetHex(&tDS3231, &s_tAlarmTime);	/* DS3231时间采集 */
	Task_AlarmFreqRead(); 			/* 闹钟频率配置读取 */
	
	switch(s_ulAlarmFreq)
	{
		case 0:		s_ucComFreq = COM_FREQ_ONCE;	return;
		case 100:	s_ucComFreq = COM_FREQ_10HZ;	return;
		case 1000:	s_ucComFreq = COM_FREQ_ELSE;	break;
		case 2000:	s_ucComFreq = COM_FREQ_ELSE;	break;
		case 5000:	s_ucComFreq = COM_FREQ_ELSE;	break;
		case 10000:	s_ucComFreq = COM_FREQ_ELSE;	break;
		default:	s_ucComFreq = COM_FREQ_ELSE;	return;
	}
	
	Task_AlarmpSet();
}

uint8_t Task_AlarmFreqCheck(void)
{
	return s_ucComFreq;
}

const uint8_t c_usTimer = 100;
static volatile uint8_t s_usComTimerCnt = 0;
static volatile uint8_t s_usIMUTimerCnt = 0;
static volatile uint8_t s_usMagTimerCnt = 0;
static volatile uint16_t s_usCMDTimerCnt = 0;
static bool s_bComTimerFlg = false;
static bool s_bIMUTimerFlg = false;
static bool s_bMagTimerFlg = false;
static bool s_bCMDTimerFlg = false;
void Task_TIM3_IRQHandler(void)
{
	s_usComTimerCnt++;
	s_usIMUTimerCnt++;
	s_usMagTimerCnt++;
	s_usCMDTimerCnt++;
	
	if(s_usComTimerCnt > 100)
	{
		s_bComTimerFlg = true;
		s_usComTimerCnt = 0;
	}
	
	if(s_usIMUTimerCnt > 50)
	{
		s_bIMUTimerFlg = true;
		s_usIMUTimerCnt = 0;
	}
	
	if(s_usMagTimerCnt > 50)
	{
		s_bMagTimerFlg = true;
		s_usMagTimerCnt = 0;
	}
	
	if(s_usCMDTimerCnt > 5000)	/* CMD延期5S超时 */
	{
		s_usCMDTimerCnt = 0;
		s_bCMDTimerFlg = true;
	}
}

/* 正确逻辑应该是在检测时，计数器要清零，但会形成蝴蝶效应的时间误差 */
/* 要计时的准确性应不主动清零 */
bool Task_ComTimerCheck(void)
{
	if(s_bComTimerFlg)
	{
		s_bComTimerFlg = false;
		return true;
	}
	
	return false;
}

bool Task_IMUTimerCheck(void)
{
	if(s_bIMUTimerFlg)
	{
		s_bIMUTimerFlg = false;
		return true;
	}
	
	return false;
}

bool Task_MagTimerCheck(void)
{
	if(s_bMagTimerFlg)
	{
		s_bMagTimerFlg = false;
		return true;
	}
	
	return false;
}

bool Task_CMDTimerCheck(void)
{
	if(s_bCMDTimerFlg)
	{
		s_bCMDTimerFlg = false;
		return true;
	}
	
	return false;
}

void Task_CMDTimerClear(void)
{
	s_bCMDTimerFlg = false;
	s_usCMDTimerCnt = 0;
}
