#include "task_conf.h"

#include "config.h"

int Mag_data_getL(double* LX, double* LY, double* LZ, double* allL, double* RX, double* RY, double* RZ, double* allR)
{
		
		int ret;
		ret  = OCD_AD24bit_GetResult(&tAD24BIT, 50);
//		if(ret!=0)
//		{
//				DBG_ERROR("OCD_AD24bit_GetResult error：%d\r\n",ret);
//				return -1;
//		}
		
		*LX = tAD24BIT.port[0].result;
		*LY = tAD24BIT.port[1].result;
		*LZ = tAD24BIT.port[2].result;
		*RX = tAD24BIT.port[3].result;
		*RY = tAD24BIT.port[4].result;
		*RZ = tAD24BIT.port[5].result;
		
		*LX = (*LX)*10000;//电压对应磁场关系
		*LY = (*LY)*10000;
		*LZ = (*LZ)*10000;
		*allL = (double)((*LX)*(*LX));
		*allL += (double)((*LY)*(*LY));
		*allL += (double)((*LZ)*(*LZ));
		*allL = sqrt(*allL);//总磁场
		
		*RX = (*RX)*10000;//电压对应磁场关系
		*RY = (*RY)*10000;
		*RZ = (*RZ)*10000;
		*allR = (double)((*RX)*(*RX));
		*allR += (double)((*RY)*(*RY));
		*allR += (double)((*RZ)*(*RZ));
		*allR = sqrt(*allR);//总磁场
		
		return 0;
		
}



