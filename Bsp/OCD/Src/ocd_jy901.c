/****************************************************************************

* Sigma�Ŷ�

* �ļ���: ocd_jy901.c

* ���ݼ�����jy901ģ���ļ�

* �ļ���ʷ��

* �汾��	����		����		˵��
* 1.1.8		2022-10-22	�����		�Խṹ����������ϣ��ṩITģʽ��DMAģʽ
									�ṩjy901���ݵĴ�����ת������ӡ����

* 1.0.0a 	2020-03-14	���		�������ļ�

* 1.1.0a 	2020-03-29	���		�޸Ĳ����ı�

****************************************************************************/
#include "ocd_jy901.h"

const uint8_t ucpUnlockCmd[] = {0xff, 0xaa, 0x69, 0x88, 0xb5}; 
/**
 * @brief JY901���ͽ���ָ���
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
static void S_JY901_UnLock(tagJY901_T *_tJY901)
{
	Drv_Uart_Transmit(&_tJY901->tUART, (uint8_t*)ucpUnlockCmd, sizeof(ucpUnlockCmd));
}

/**
 * @brief JY901��ʱ����
 * @param Null
 * @retval Null
*/
static void S_JY901_Delay(void)
{
	Drv_Delay_Ms(20);
}

/**
 * @brief JY901�������ú���
 * @param _tJY901-JY901���ָ��
 * @param _ucSet-SAVE_NOW ���浱ǰ;SAVE_RESET ��������;SAVE_DEFAULT �ָ���������;
 * @retval Null
*/
static void S_JY901_SaveConfig(tagJY901_T *_tJY901, uint8_t _ucSet)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x00, 0x00, 0x00};
	
	switch(_ucSet)
	{
		case SAVE_NOW:
			ucpWrite[3] = SAVE_NOW;
		break;
		
		case SAVE_DEFAULT:
			ucpWrite[3] = SAVE_DEFAULT;
		break;

		case SAVE_RESET:
			ucpWrite[3] = SAVE_RESET;
		
		default:
			
		break;
	}
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
}

/**
 * @brief JY901�ش���������
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_RxTypeConfig(tagJY901_T *_tJY901)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x02, 0x00, 0x00};
	
	ucpWrite[3] = _tJY901->tConfig.usType >> 8;
	ucpWrite[4] = _tJY901->tConfig.usType;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);		
}

/**
 * @brief JY901У׼����
 * @param _tJY901-JY901���ָ��
 * @param _ucMode-У׼ģʽ		
 * @retval Null
*/
void OCD_JY901_Correct(tagJY901_T *_tJY901, uint8_t _ucMode)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x01, 0x00, 0x00};
	
	ucpWrite[3] = _ucMode;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);
}

const uint8_t ucpSleepCmd[] = {0xff, 0xaa, 0x22, 0x01, 0x00}; 
/**
 * @brief JY901���ߺ��������ߺ��ٴε���Ϊ������ߣ�
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_Sleep(tagJY901_T *_tJY901)
{
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, (uint8_t*)ucpSleepCmd, sizeof(ucpSleepCmd));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);
}

/**
 * @brief JY901�ش���������
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_RxSpeedConfig(tagJY901_T *_tJY901)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x03, 0x00, 0x00};
	
	ucpWrite[3] = _tJY901->tConfig.ucRate;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);		
}

/**
 * @brief JY901�ش�����������
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_RxBaudConfig(tagJY901_T *_tJY901)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x04, 0x00, 0x00};
	
	ucpWrite[3] = _tJY901->tConfig.ucBaud;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);		
}

/**
 * @brief JY901�������Զ�У׼����
 * @param _tJY901-JY901���ָ��
 * @param _ucMode-1-�����Զ�У׼;0-�����Զ�У׼
 * @retval Null
*/
void OCD_JY901_GyroAutoCorrect(tagJY901_T *_tJY901, uint8_t _ucMode)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x63, 0x00, 0x00};
	
	ucpWrite[3] = _ucMode;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);
}

const uint8_t ucpOutputOnceCmd[] = {0xff, 0xaa, 0x03, 0x0c, 0x00}; 
/**
 * @brief JY901��������������ûش�����Ϊ���������
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_OutputOnce(tagJY901_T *_tJY901)
{
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, (uint8_t*)ucpOutputOnceCmd, sizeof(ucpOutputOnceCmd));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);
}

/**
 * @brief JY901�жϳ�ʼ������
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_ITInit(tagJY901_T *_tJY901)
{
	Drv_Uart_ITInit(&_tJY901->tUART);

	OCD_JY901_RxBaudConfig(_tJY901);
	OCD_JY901_RxSpeedConfig(_tJY901);
	OCD_JY901_RxTypeConfig(_tJY901);
}

/**
 * @brief JY901DMA��ʼ������
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_DMAInit(tagJY901_T *_tJY901)
{
	Drv_Uart_DMAInit(&_tJY901->tUART);

	OCD_JY901_RxBaudConfig(_tJY901);
	OCD_JY901_RxSpeedConfig(_tJY901);
	OCD_JY901_RxTypeConfig(_tJY901);
}

/**
 * @brief JY901���ݴ�������,�����������ͷ������Ӧ�Ľṹ���Ա��
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_DataProcess(tagJY901_T *_tJY901)
{
	/* �жϱ�־λ */
	if(_tJY901->tUART.tUartDMA.ucDMARxCplt)
	{
		/* �������� */
		for (int i = 0; i < _tJY901->tUART.tRxInfo.usRxLenth; i++)
		{
			if(_tJY901->tUART.tRxInfo.ucpRxCache[i] == JY901_HEAD) /* �������ͷΪ0x55 */
			{
				/* ��У�� */
				uint8_t ucSum = 0;
				for(int j = 0;j<10;j++)
				{
					ucSum += _tJY901->tUART.tRxInfo.ucpRxCache[i+j];
				}
				/* ��У��ɹ���Ϊ��Ҫ�������� */
				if(ucSum == _tJY901->tUART.tRxInfo.ucpRxCache[i+10])
				{
					/* ����type��������Ӧ�Ľṹ���� */
					switch (_tJY901->tUART.tRxInfo.ucpRxCache[i+1])
					{
						case JY901_TIME:	memcpy(&_tJY901->stcTime,&_tJY901->tUART.tRxInfo.ucpRxCache[i+2],8);
											break;
						case JY901_ACCEL:	memcpy(&_tJY901->stcAcc,&_tJY901->tUART.tRxInfo.ucpRxCache[i+2],8);
											break;
						case JY901_GYRO:	memcpy(&_tJY901->stcGyro,&_tJY901->tUART.tRxInfo.ucpRxCache[i+2],8);
											break;
						case JY901_ANGLE:	memcpy(&_tJY901->stcAngle,&_tJY901->tUART.tRxInfo.ucpRxCache[i+2],8);
											break;
						case JY901_MAG:		memcpy(&_tJY901->stcMag,&_tJY901->tUART.tRxInfo.ucpRxCache[i+2],8);
											break;
						case JY901_QUATER:  memcpy(&_tJY901->stcQuater,&_tJY901->tUART.tRxInfo.ucpRxCache[i+2],8);
											break;
						default:	
											break;
					}
				}
				else continue;
			}
		}
		_tJY901->tUART.tUartDMA.ucDMARxCplt = 0;	/* ��־λ���� */
	}
}

/**
 * @brief JY901����ת������,��������ת��Ϊ�ɶ�,�洢����ӦCon��Ա��
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_DataConversion(tagJY901_T *_tJY901)
{
	/* ��ȡ���ٶ� */
	if(_tJY901->tConfig.usType & JY901_OUTPUT_ACCEL)
	{
		_tJY901->stcAcc.ConAccX = (float)_tJY901->stcAcc.AccX /32768*16;
		_tJY901->stcAcc.ConAccY = (float)_tJY901->stcAcc.AccY /32768*16;
		_tJY901->stcAcc.ConAccZ = (float)_tJY901->stcAcc.AccZ /32768*16;
	}
	/* ��ȡ������ */
	if(_tJY901->tConfig.usType & JY901_OUTPUT_GYRO)
	{
		_tJY901->stcGyro.ConGyroX = (float)_tJY901->stcGyro.GyroX/32768*2000;
		_tJY901->stcGyro.ConGyroY = (float)_tJY901->stcGyro.GyroY/32768*2000;
		_tJY901->stcGyro.ConGyroZ = (float)_tJY901->stcGyro.GyroZ/32768*2000;
	}
	/* ��ȡŷ���� */
	if (_tJY901->tConfig.usType & JY901_OUTPUT_ANGLE)
	{
		_tJY901->stcAngle.ConRoll = (float)_tJY901->stcAngle.Roll/32768*180;
		_tJY901->stcAngle.ConPitch = (float)_tJY901->stcAngle.Pitch/32768*180;
		_tJY901->stcAngle.ConYaw = (float)_tJY901->stcAngle.Yaw/32768*180;
	}
	/* ��ȡ�ų� */
	if (_tJY901->tConfig.usType & JY901_OUTPUT_MAG)
	{
		_tJY901->stcMag.ConMagX = (float)_tJY901->stcMag.MagX;
		_tJY901->stcMag.ConMagY = (float)_tJY901->stcMag.MagY;
		_tJY901->stcMag.ConMagZ = (float)_tJY901->stcMag.MagZ;
	}
	/* ��ȡ��Ԫ�� */
	if(_tJY901->tConfig.usType & JY901_OUTPUT_QUATER)
	{
		_tJY901->stcQuater.Conq0 = (float)_tJY901->stcQuater.q0/32768;
		_tJY901->stcQuater.Conq1 = (float)_tJY901->stcQuater.q1/32768;
		_tJY901->stcQuater.Conq2 = (float)_tJY901->stcQuater.q2/32768;
		_tJY901->stcQuater.Conq3 = (float)_tJY901->stcQuater.q3/32768;
	}
}

/**
 * @brief JY901�򴮿ڴ�ӡ������ɵ����ݣ�ʹ��printf����rt_printf
 * @param _tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_Printf(tagJY901_T *_tJY901)
{
	/* ��ӡʱ�� */
	if(_tJY901->tConfig.usType & JY901_OUTPUT_TIME)		printf("time: %d��%d��%d��%dʱ%d��%d��\r\n",_tJY901->stcTime.Year,_tJY901->stcTime.Month,_tJY901->stcTime.Day,_tJY901->stcTime.Hour,_tJY901->stcTime.Min,_tJY901->stcTime.Sec);
	/* ��ӡ���ٶ� */
	if(_tJY901->tConfig.usType & JY901_OUTPUT_ACCEL)	printf("Acc:  %.3f %.3f %.3f\r\n",_tJY901->stcAcc.ConAccX,_tJY901->stcAcc.ConAccY,_tJY901->stcAcc.ConAccZ);
	/* ��ӡ���ٶ� */
	if(_tJY901->tConfig.usType & JY901_OUTPUT_GYRO)		printf("Gyro: %.3f %.3f %.3f\r\n",_tJY901->stcGyro.ConGyroX,_tJY901->stcGyro.ConGyroY,_tJY901->stcGyro.ConGyroZ);
	/* ��ӡŷ���� */
	if(_tJY901->tConfig.usType & JY901_OUTPUT_ANGLE)	printf("Angle:%.3f %.3f %.3f\r\n",_tJY901->stcAngle.ConRoll,_tJY901->stcAngle.ConPitch,_tJY901->stcAngle.ConYaw);
	/* ��ӡ�ų� */
	if(_tJY901->tConfig.usType & JY901_OUTPUT_MAG)		printf("Mag:  %.3f %.3f %.3f\r\n",_tJY901->stcMag.ConMagX,_tJY901->stcMag.ConMagY,_tJY901->stcMag.ConMagZ);
	/* ��ӡ��Ԫ�� */
	if(_tJY901->tConfig.usType & JY901_OUTPUT_QUATER)	printf("Quater:  %.3f %.3f %.3f %.3f\r\n",_tJY901->stcQuater.Conq0,_tJY901->stcQuater.Conq1,_tJY901->stcQuater.Conq2,_tJY901->stcQuater.Conq3);
}