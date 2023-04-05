#ifndef __TASK_ADCOLLECT_H_
#define __TASK_ADCOLLECT_H_

union float_data //发送float类型数据 4字节
{
    float f_data;
    uint8_t byte[4];
};

typedef struct{
	union float_data X; //磁力仪X值
	union float_data Y; //磁力仪Y值
	union float_data Z; //磁力仪Z值
	union float_data all; //磁力仪总场
}tagMagnetometerData_T;

int Mag_data_getL(double* LX, double* LY, double* LZ, double* allL, double* RX, double* RY, double* RZ, double* allR);

#endif


