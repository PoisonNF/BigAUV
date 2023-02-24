#include "task_conf.h"

static char s_ucpSaveFileName[25] = {0};
void Task_FATFSDataSave(void)
{
	uint32_t ulBr;
	
	sprintf(s_ucpSaveFileName, "/Data/20%02x%02x%02x.txt", Task_TimeGet().ucYear, Task_TimeGet().ucMonth, Task_TimeGet().ucDate);		/* sd卡中文件名更新	*/
	OCD_FATFS_Write_End(&tFATFS, s_ucpSaveFileName, Task_CacheGet(), CACHE_LENGTH, ulBr);
}

void Task_FATFSDataRead(void)
{

}

static tagFileInfo_T s_tInfo[256];
void Task_FATFSReadDir(void)
{
	uint8_t index;
	uint8_t ucNum = 0;					/* 文件数量 */
	
	ucNum = OCD_FATFS_ReadDir(&tFATFS, s_tInfo, "/Data", 13);
	
	for(index = 0; index < ucNum; index++)
	{
		printf("@h*");
		Drv_Uart_Transmit(&tPCUart, s_tInfo[index].ucpFileName, strlen((char*)s_tInfo[index].ucpFileName));
		printf("*\r\n");
	}
}

#define DATA_BUFFER_SIZE	512
static uint8_t ucpSendFileName[20] = {0};
static uint8_t ucpDataBuffer[DATA_BUFFER_SIZE] = {0};
void Task_FATFSSendFile(uint8_t *_ucpFileName)
{
	uint8_t index;
	uint32_t ulFileSize = 0;			/* 文件大小 */
	uint32_t ulOffset = 0;				/* 光标偏移量大小 */
	uint16_t usLen = DATA_BUFFER_SIZE;	/* 一次性读取数据长度 */
	bool ucEndFlg = false;				/* 单次文件传输完成标志 */
	uint32_t ulBr;

	/* 确认文件大小 */
	memcpy(ucpSendFileName, _ucpFileName + 2, 8);
	SGA_Function_Insert_Sub(ucpSendFileName,  (uint8_t*)"/Data/", 0);
	SGA_Function_Insert_Sub(ucpSendFileName,  (uint8_t*)".txt", 14);
	OCD_FATFS_GetFileInfo(&tFATFS, (char*)ucpSendFileName);
	ulFileSize = tFATFS.tFATFSInfo.tFILINFO.fsize;
	
	if(!ulFileSize)
	{
#ifdef DEBUG_ENABLE
		printf("File Name Error!!!\r\n");
#endif
		return;
	}
	
#ifdef DEBUG_ENABLE
	printf("CMD Waiting!!!\r\n");
#endif
	
	while(1)
	{
		/* 光标以及读取长度计算 */
		if((ulOffset + usLen) > ulFileSize)
		{
			usLen = ulFileSize - ulOffset;
			ucEndFlg = 1;
		}
		
		/* 读对应文件数据 */
		OCD_FATFS_ReadData_SpecifyIndex(&tFATFS, (char*)ucpSendFileName, ucpDataBuffer, usLen, ulOffset, ulBr);
		Drv_Uart_Transmit(&tPCUart, ucpDataBuffer, usLen);
		ulOffset += usLen;
		
		if(ucEndFlg)
		{
			ulOffset = 0;
			index++;
			ucEndFlg = 0;
			usLen = DATA_BUFFER_SIZE;
			break;
		}
	}
}
