#include "task_conf.h"

static char s_ucpCache[CACHE_LENGTH] = {0x30};

static tagDS3231Time_T	s_tSysTime;
static tagIMU_T*		s_tSysIMU;
static tagMag_T*		s_tSysMag;

void Task_CacheUpdate(void)
{
	uint8_t ucOffset = 0;
	
	/* 获取系统时间 */
	s_tSysTime = Task_TimeGet();
	
	/* 获取磁场数据 */
	s_tSysMag = Task_MagGet();
	
	/* 获取YJ901B数据 */
	s_tSysIMU = Task_IMUGet();
	
	/* 字符串拼接 */
	sprintf(s_ucpCache, "20%02x-%02x-%02x %02x:%02x:%02x,", s_tSysTime.ucYear, s_tSysTime.ucMonth, s_tSysTime.ucDate, s_tSysTime.ucHour, s_tSysTime.ucMinute, s_tSysTime.ucSecond);
	ucOffset += 20;
	sprintf(s_ucpCache + ucOffset, "%8.1f,%8.1f,%8.1f,%8.1f,", s_tSysMag->dXMag, s_tSysMag->dYMag, s_tSysMag->dZMag, s_tSysMag->dAllMag);
	ucOffset += 36;
	sprintf(s_ucpCache + ucOffset, "%6.1f,%6.1f,%5.1f", s_tSysIMU->fRoll, s_tSysIMU->fPitch, s_tSysIMU->fYaw);
}

void Task_Send(void)
{
	printf("@C*");
	Drv_Uart_Transmit(&tPCUart, (uint8_t*)s_ucpCache, CACHE_LENGTH);
	printf("*\r\n");
}

char* Task_CacheGet(void)
{
	return s_ucpCache;
}
