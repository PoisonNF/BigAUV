#ifndef __OCD_CH438Q_H_
#define __OCD_CH438Q_H_

#include "drv_hal_conf.h"

#define CHIP1 0x00
#define CHIP2 0x01
#define CHIP3 0x02
#define CHIP4 0x03

/* CS1和CS2分别对两片CH438Q芯片进行片选，若只有一片CH438Q芯片，则只需对CS1修改 */
#define CS_SET_HIGH         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);   /* 芯片1片选控制输入无效 */
#define CS_SET_LOW          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET); /* 芯片1片选控制输入有效 */
#define CS2_SET_HIGH        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);    /* 芯片2片选控制输入无效 */
#define CS2_SET_LOW         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);  /* 芯片2片选控制输入有效 */
#define RD_SET_HIGH         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);    /* 读选通输入无效 */
#define RD_SET_LOW          HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);  /* 读选通输入有效 */
#define WR_SET_HIGH         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);    /* 写选通输入无效 */
#define WR_SET_LOW          HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);  /* 写选通输入有效 */
#define AMOD_SET_HIGH       HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);    /* 复用地址方式 */
#define AMOD_SET_LOW        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);  /* 直接地址方式 */
#define ALE_SET_HIGH        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   /* 复用地址方式的地址锁存使能输入有效 */
#define ALE_SET_LOW         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); /* 复用地址方式的地址锁存使能输入无效 */
#define INT1_GPIO_PIN       GPIO_PIN_0  /* 芯片1中断请求输出引脚 */
#define INT2_GPIO_PIN       GPIO_PIN_2  /* 芯片2中断请求输出引脚 */

#define REG_RBR_ADDR 0x00 /* 串口0接收缓冲寄存器地址 */
#define REG_THR_ADDR 0x00 /* 串口0发送保持寄存器地址 */
#define REG_IER_ADDR 0x01 /* 串口0中断使能寄存器地址 */
#define REG_IIR_ADDR 0x02 /* 串口0中断识别寄存器地址 */
#define REG_FCR_ADDR 0x02 /* 串口0FIFO控制寄存器地址 */
#define REG_LCR_ADDR 0x03 /* 串口0线路控制寄存器地址 */
#define REG_MCR_ADDR 0x04 /* 串口0MODEM控制寄存器地址 */
#define REG_LSR_ADDR 0x05 /* 串口0线路状态寄存器地址 */
#define REG_MSR_ADDR 0x06 /* 串口0MODEM状态寄存器地址 */
#define REG_SCR_ADDR 0x07 /* 串口0用户可定义寄存器地址 */
#define REG_DLL_ADDR 0x00 /* 波特率除数锁存器低8位字节地址 */
#define REG_DLM_ADDR 0x01 /* 波特率除数锁存器高8位字节地址 */

/* CH438内部串口0~7 专用状态寄存器 */

#define REG_SSR_ADDR 0x4F /* 专用状态寄存器地址 */

/* IER寄存器的位 */

#define BIT_IER_RESET 0x80    /* 该位置1则软复位该串口 */
#define BIT_IER_LOWPOWER 0x40 /* 该位为1则关闭该串口的内部基准时钟 */
#define BIT_IER_SLP 0x20      /* 串口0是SLP,为1则关闭时钟震荡器 */
#define BIT_IER1_CK2X 0x20    /* 串口1是CK2X,为1则强制将外部时钟信号2倍频后作为内部基准时钟 */
#define BIT_IER_IEMODEM 0x08  /* 该位为1允许MODEM输入状态变化中断 */
#define BIT_IER_IELINES 0x04  /* 该位为1允许接收线路状态中断 */
#define BIT_IER_IETHRE 0x02   /* 该位为1允许发送保持寄存器空中断 */
#define BIT_IER_IERECV 0x01   /* 该位为1允许接收到数据中断 */

/* IIR寄存器的位 */

#define BIT_IIR_FIFOENS1 0x80
#define BIT_IIR_FIFOENS0 0x40 /* 该2位为1表示起用FIFO */

/* 中断类型：0001没有中断，0110接收线路状态中断，0100接收数据可用中断，1100接收数据超时中断，0010THR寄存器空中断，0000MODEM输入变化中断 */
#define BIT_IIR_IID3 0x08
#define BIT_IIR_IID2 0x04 //接受数据可用
#define BIT_IIR_IID1 0x02 //THR寄存器空中断
#define BIT_IIR_NOINT 0x01

/* FCR寄存器的位 */

/* 触发点： 00对应1个字节，01对应16个字节，10对应64个字节，11对应112个字节 */
#define BIT_FCR_RECVTG1 0x00 /* 设置FIFO的中断和自动硬件流控制的触发点 */
#define BIT_FCR_RECVTG0 0x40 /* 设置FIFO的中断和自动硬件流控制的触发点 */

#define BIT_FCR_TFIFORST 0x04 /* 该位置1则清空发送FIFO中的数据 */
#define BIT_FCR_RFIFORST 0x02 /* 该位置1则清空接收FIFO中的数据 */
#define BIT_FCR_FIFOEN 0x01   /* 该位置1则起用FIFO,为0则禁用FIFO */

/* LCR寄存器的位 */

#define BIT_LCR_DLAB 0x80    /* 为1才能存取DLL，DLM，为0才能存取RBR/THR/IER */
#define BIT_LCR_BREAKEN 0x40 /* 为1则强制产生BREAK线路间隔*/

/* 设置校验格式：当PAREN为1时，00奇校验，01偶校验，10标志位（MARK，置1)，11空白位（SPACE，清0) */
#define BIT_LCR_PARMODE1 0x20 /* 设置奇偶校验位格式 */
#define BIT_LCR_PARMODE0 0x10 /* 设置奇偶校验位格式 */

#define BIT_LCR_PAREN 0x08   /* 为1则允许发送时产生和接收校验奇偶校验位 */
#define BIT_LCR_STOPBIT 0x04 /* 为1则两个停止位,为0一个停止位 */

/* 设置字长度：00则5个数据位，01则6个数据位，10则7个数据位，11则8个数据位 */
#define BIT_LCR_WORDSZ1 0x02 /* 设置字长长度 */
#define BIT_LCR_WORDSZ0 0x01

/* MCR寄存器的位 */

#define BIT_MCR_AFE 0x20  /* 为1允许CTS和RTS硬件自动流控制 */
#define BIT_MCR_LOOP 0x10 /* 为1使能内部回路的测试模式 */
#define BIT_MCR_OUT2 0x08 /* 为1允许该串口的中断请求输出 */
#define BIT_MCR_OUT1 0x04 /* 为用户定义的MODEM控制位 */
#define BIT_MCR_RTS 0x02  /* 该位为1则RTS引脚输出有效 */
#define BIT_MCR_DTR 0x01  /* 该位为1则DTR引脚输出有效 */

/* LSR寄存器的位 */

#define BIT_LSR_RFIFOERR 0x80 /* 为1表示在接收FIFO中存在至少一个错误 */
#define BIT_LSR_TEMT 0x40     /* 为1表示THR和TSR全空 */
#define BIT_LSR_THRE 0x20     /* 为1表示THR空*/
#define BIT_LSR_BREAKINT 0x10 /* 该位为1表示检测到BREAK线路间隔 */
#define BIT_LSR_FRAMEERR 0x08 /* 该位为1表示读取数据帧错误 */
#define BIT_LSR_PARERR 0x04   /* 该位为1表示奇偶校验错误 */
#define BIT_LSR_OVERR 0x02    /* 为1表示接收FIFO缓冲区溢出 */
#define BIT_LSR_DATARDY 0x01  /* 该位为1表示接收FIFO中有接收到的数据 */

/* MSR寄存器的位 */

#define BIT_MSR_DCD 0x80  /* 该位为1表示DCD引脚有效 */
#define BIT_MSR_RI 0x40   /* 该位为1表示RI引脚有效 */
#define BIT_MSR_DSR 0x20  /* 该位为1表示DSR引脚有效 */
#define BIT_MSR_CTS 0x10  /* 该位为1表示CTS引脚有效 */
#define BIT_MSR_DDCD 0x08 /* 该位为1表示DCD引脚输入状态发生变化过 */
#define BIT_MSR_TERI 0x04 /* 该位为1表示RI引脚输入状态发生变化过 */
#define BIT_MSR_DDSR 0x02 /* 该位为1表示DSR引脚输入状态发生变化过 */
#define BIT_MSR_DCTS 0x01 /* 该位为1表示CTS引脚输入状态发生变化过 */

/* 中断状态码 */

#define INT_NOINT 0x01        /* 没有中断 */
#define INT_THR_EMPTY 0x02    /* THR空中断 */
#define INT_RCV_OVERTIME 0x0C /* 接收超时中断 */
#define INT_RCV_SUCCESS 0x04  /* 接收数据可用中断 */
#define INT_RCV_LINES 0x06    /* 接收线路状态中断 */
#define INT_MODEM_CHANGE 0x00 /* MODEM输入变化中断 */

#define CH438_IIR_FIFOS_ENABLED 0xC0 /* 起用FIFO */

typedef struct 
{
    tagGPIO_T       tGPIO_CS;
    tagGPIO_T       tGPIO_RD;
    tagGPIO_T       tGPIO_WR;
    tagGPIO_T       tGPIO_AMOD;
    tagGPIO_T       tGPIO_ALE;
    tagGPIO_T       tGPIO_INT;
    tagGPIO_T       tGPIO_DATA[8];
}tagCH438Q_GPIO;

typedef struct 
{
    uint32_t        ulaBaudRate[8];
    // uint8_t         cSerial_Port[8];
}tagCH438Q_SerialPort;

typedef struct 
{
    tagCH438Q_GPIO           tCH438Q_GPIO;
    tagCH438Q_SerialPort    tCH438Q_SerialPort;
}tagCH438Q_T;

uint8_t OCD_CH438Q_CheckIIR(tagCH438Q_T *_tCH438Q, uint8_t _ucNum);
void OCD_CH438Q_CloseSeril(tagCH438Q_T *_tCH438Q, uint8_t _ucNum); /* 关闭某位串口 */
void OCD_CH438Q_CloseALLSeril(tagCH438Q_T *_tCH438Q); /* 关闭所有串口 */
void OCD_CH438Q_ResetSeril(tagCH438Q_T *_tCH438Q, uint8_t _ucNum); /* 复位串口 */
void OCD_CH438Q_SetBandrate(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint8_t _ucValue); /* 设置波特率 未使用此函数 */
void OCD_CH438Q_SendDatas(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint8_t *_ucpSendBuff, uint8_t _ucLen);
unsigned char OCD_CH438Q_RecvDatas(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint8_t *_ucpRevBuff);
void OCD_CH438Q_GPIO_Init(tagCH438Q_T *_tCH438Q);
void OCD_CH438Q_Init(tagCH438Q_T *_tCH438Q); //IO口中断等初始化
void OCD_CH438Q_Uart_Init(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint16_t _ucValue);
void OCD_CH438Q_RxHandler(tagCH438Q_T *_tCH438Q);

#endif


