#include "task_conf.h"

static char s_ucpSaveFileName[25] = {0};
void Task_FATFSDataSave(void)
{
	uint32_t ulBr;
	
	sprintf(s_ucpSaveFileName, "/Data/20%02x%02x%02x.txt", Task_TimeGet().ucYear, Task_TimeGet().ucMonth, Task_TimeGet().ucDate);		/* sd�����ļ�������	*/
	OCD_FATFS_Write_End(&tFATFS, s_ucpSaveFileName, Task_CacheGet(), CACHE_LENGTH, ulBr);
}

void Task_FATFSDataRead(void)
{

}

static tagFileInfo_T s_tInfo[256];
void Task_FATFSReadDir(void)
{
	uint8_t index;
	uint8_t ucNum = 0;					/* �ļ����� */
	
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
	uint32_t ulFileSize = 0;			/* �ļ���С */
	uint32_t ulOffset = 0;				/* ���ƫ������С */
	uint16_t usLen = DATA_BUFFER_SIZE;	/* һ���Զ�ȡ���ݳ��� */
	bool ucEndFlg = false;				/* �����ļ�������ɱ�־ */
	uint32_t ulBr;

	/* ȷ���ļ���С */
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
		/* ����Լ���ȡ���ȼ��� */
		if((ulOffset + usLen) > ulFileSize)
		{
			usLen = ulFileSize - ulOffset;
			ucEndFlg = 1;
		}
		
		/* ����Ӧ�ļ����� */
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
