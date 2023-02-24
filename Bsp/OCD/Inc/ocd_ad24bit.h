#ifndef __OCD_AD24bit_H_
#define __OCD_AD24bit_H_

#include "drv_hal_conf.h"

#define	Comm_ERROR -21//SPI通信有问题
#define	REG_ADDR_ERROR  -22//获取寄存器地址错误
#define	REG_READ_ERROR  -23//读错误
#define	REG_WRITE_ERROR  -24//写错误
#define	REG_VALUE_ERROR  -25//值错误
#define REG_TIMEROUT_ERROR  -26//超时错误
#define PORT_NUM_ERROR  -27//端口号错误
#define RESULT_TIMEROUT_ERROR  -28//读取结果超时

#define REG_READ_SUCCESS  0//读数据成功
#define RESULT_SUCCESS  0//读数据成功
typedef enum {
	AD24BIT_DISABLE,
	AD24BIT_USE_CRC,
	AD24BIT_USE_XOR,
} ad24bit_crc_mode;

typedef enum {
	VIN0,
	VIN1,
	VIN2,
	VIN3,
	VIN4,
	VIN5,
	VIN6,
	VIN7,
	VIN1_0,
	VIN3_2,
	VIN5_4,
	VIN7_6,
	IIN0,
	IIN1,
	IIN2,
	IIN3,
	PORT_NULL,
} input_port;


typedef enum {
 PORT_DISABLE= 0,  
 PORT_ENABLE, 
} port_enable;

/*! Port measurement info */
typedef struct {
	port_enable enable;
	input_port  num;
	uint32_t value; // ad输出的裸数据
	double gain;
	double offset;
	double result;// ad输出的电压、电流值
} ad24bit_input_port;

/*! AD24BIT register info */
typedef struct {
	int32_t addr;
	int32_t value;
	int32_t size;
} ad24bit_st_reg;
/*
 * The structure describes the device and is used with the AD24BIT driver.
 * @slave_select_id: The ID of the Slave Select to be passed to the SPI calls.
 * @regs: A reference to the register list of the device that the user must
 *       provide when calling the Setup() function.
 * @num_regs: The length of the register list.
 * @userCRC: Error check type to use on SPI transfers.
 */
typedef struct {
	/* SPI */
	tagSPI_T		tSPI;
	/* Device Settings */
	ad24bit_st_reg		*regs;
	uint8_t			num_regs;
	ad24bit_crc_mode		useCRC;
	ad24bit_input_port  port[12];
	uint8_t			port_num;
}tagAD24BIT_T;






/*****************************************************************************/
/******************* AD24BIT Constants ****************************************/
/*****************************************************************************/
#define AD24BIT_CRC8_POLYNOMIAL_REPRESENTATION 0x07 /* x8 + x2 + x + 1 */

/*****************************************************************************/
/************************ Functions Declarations *****************************/
/*****************************************************************************/


/**
 * @brief 初始化AD芯片
 * @param device-初始化AD24BIT实例指针
 * @retval  0 :初始化成功
						-1：device不可用
						Comm_ERROR:SPI通信出差，检查连接线和相关配置device->tSPI.tSPIHandle.Instance;
*/
int32_t OCD_AD24BIT_Init(tagAD24BIT_T* device );


/**
 * @brief 获取AD24bit转化后的电压或电流值，结果存储在对应端口的device->port[i].result中
 * @param device-初始化AD24BIT实例指针,timeout-设定超时时间单位ms，设定时间内没有读取到数据则退出
 * @retval  RESULT_SUCCESS :读取成功
						REG_ADDR_ERROR:参数device错误
					  REG_TIMEROUT_ERROR：AD转换超时，一般是SPI硬件接口问题
					  REG_READ_ERROR：读取失败，一般是SPI硬件接口问题
						RESULT_TIMEROUT_ERROR;//超时错误
*/
int32_t OCD_AD24bit_GetResult(tagAD24BIT_T *device,uint32_t timeout);

#endif
