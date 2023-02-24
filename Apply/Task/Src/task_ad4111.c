#include "task_conf.h"

static tagMag_T s_tSysMag;
static bool s_bXMagFlg = false;
static bool s_bYMagFlg = false;
static bool s_bZMagFlg = false;

static tagKalmanParam_T s_tKPMagX = {0.02, 0, 0, 0, 0, 0.001, 0.543};
static tagKalmanParam_T s_tKPMagY = {0.02, 0, 0, 0, 0, 0.001, 0.543};
static tagKalmanParam_T s_tKPMagZ = {0.02, 0, 0, 0, 0, 0.001, 0.543};

uint8_t Task_AD4111DataGet(void)
{
	/* 数据采集 */
	do
	{
		if(!s_bXMagFlg)
		{
			if(OCD_AD4111_ReadActualData(&tAD4111, AD4111_CHANNEL0, 10) == AD4111_OK)
			{
				s_bXMagFlg = true;
				s_tSysMag.dXMag = tAD4111.tChannel[AD4111_CHANNEL0].dValue;
			}
			else
				break;
		}
		
		if(!s_bYMagFlg)
		{
			if(OCD_AD4111_ReadActualData(&tAD4111, AD4111_CHANNEL1, 10) == AD4111_OK)
			{
				s_bYMagFlg = true;
				s_tSysMag.dYMag = tAD4111.tChannel[AD4111_CHANNEL1].dValue;
			}
			else
				break;
		}
			
		if(!s_bZMagFlg)
			if(OCD_AD4111_ReadActualData(&tAD4111, AD4111_CHANNEL2, 10) == AD4111_OK)
			{
				s_bZMagFlg = true;
				s_tSysMag.dZMag = tAD4111.tChannel[AD4111_CHANNEL2].dValue;
			}		
	}while(0);
	
	if(s_bZMagFlg && s_bZMagFlg && s_bZMagFlg)
	{
		/* 卡尔曼滤波算法 */
		
		/* 比例换算 */
		s_tSysMag.dXMag *= 10000;
		s_tSysMag.dYMag *= 10000;
		s_tSysMag.dZMag *= 10000;
		
		/* 总场计算 */
		s_tSysMag.dAllMag = s_tSysMag.dXMag * s_tSysMag.dXMag
							+ s_tSysMag.dYMag * s_tSysMag.dYMag
							+ s_tSysMag.dZMag * s_tSysMag.dZMag;
		
		s_tSysMag.dAllMag = sqrt(s_tSysMag.dAllMag);
		
		s_bXMagFlg = false;
		s_bYMagFlg = false;
		s_bZMagFlg = false;
		return 1;
	}
	
	/* 滤波算法，可选择不滤波 */
#ifdef	AD4111_FILTER_ENABLE
	
#endif
	
	return 0;
}

tagMag_T *Task_MagGet(void)
{
	return &s_tSysMag;
}
