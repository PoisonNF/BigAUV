#ifndef __OCD_CH438Q_H_
#define __OCD_CH438Q_H_

#include "drv_hal_conf.h"

#define CHIP1 0x00
#define CHIP2 0x01
#define CHIP3 0x02
#define CHIP4 0x03

/* CS1��CS2�ֱ����ƬCH438QоƬ����Ƭѡ����ֻ��һƬCH438QоƬ����ֻ���CS1�޸� */
#define CS_SET_HIGH         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);   /* оƬ1Ƭѡ����������Ч */
#define CS_SET_LOW          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET); /* оƬ1Ƭѡ����������Ч */
#define CS2_SET_HIGH        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);    /* оƬ2Ƭѡ����������Ч */
#define CS2_SET_LOW         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);  /* оƬ2Ƭѡ����������Ч */
#define RD_SET_HIGH         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);    /* ��ѡͨ������Ч */
#define RD_SET_LOW          HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);  /* ��ѡͨ������Ч */
#define WR_SET_HIGH         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);    /* дѡͨ������Ч */
#define WR_SET_LOW          HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);  /* дѡͨ������Ч */
#define AMOD_SET_HIGH       HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);    /* ���õ�ַ��ʽ */
#define AMOD_SET_LOW        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);  /* ֱ�ӵ�ַ��ʽ */
#define ALE_SET_HIGH        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   /* ���õ�ַ��ʽ�ĵ�ַ����ʹ��������Ч */
#define ALE_SET_LOW         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); /* ���õ�ַ��ʽ�ĵ�ַ����ʹ��������Ч */
#define INT1_GPIO_PIN       GPIO_PIN_0  /* оƬ1�ж������������ */
#define INT2_GPIO_PIN       GPIO_PIN_2  /* оƬ2�ж������������ */

#define REG_RBR_ADDR 0x00 /* ����0���ջ���Ĵ�����ַ */
#define REG_THR_ADDR 0x00 /* ����0���ͱ��ּĴ�����ַ */
#define REG_IER_ADDR 0x01 /* ����0�ж�ʹ�ܼĴ�����ַ */
#define REG_IIR_ADDR 0x02 /* ����0�ж�ʶ��Ĵ�����ַ */
#define REG_FCR_ADDR 0x02 /* ����0FIFO���ƼĴ�����ַ */
#define REG_LCR_ADDR 0x03 /* ����0��·���ƼĴ�����ַ */
#define REG_MCR_ADDR 0x04 /* ����0MODEM���ƼĴ�����ַ */
#define REG_LSR_ADDR 0x05 /* ����0��·״̬�Ĵ�����ַ */
#define REG_MSR_ADDR 0x06 /* ����0MODEM״̬�Ĵ�����ַ */
#define REG_SCR_ADDR 0x07 /* ����0�û��ɶ���Ĵ�����ַ */
#define REG_DLL_ADDR 0x00 /* �����ʳ�����������8λ�ֽڵ�ַ */
#define REG_DLM_ADDR 0x01 /* �����ʳ�����������8λ�ֽڵ�ַ */

/* CH438�ڲ�����0~7 ר��״̬�Ĵ��� */

#define REG_SSR_ADDR 0x4F /* ר��״̬�Ĵ�����ַ */

/* IER�Ĵ�����λ */

#define BIT_IER_RESET 0x80    /* ��λ��1����λ�ô��� */
#define BIT_IER_LOWPOWER 0x40 /* ��λΪ1��رոô��ڵ��ڲ���׼ʱ�� */
#define BIT_IER_SLP 0x20      /* ����0��SLP,Ϊ1��ر�ʱ������ */
#define BIT_IER1_CK2X 0x20    /* ����1��CK2X,Ϊ1��ǿ�ƽ��ⲿʱ���ź�2��Ƶ����Ϊ�ڲ���׼ʱ�� */
#define BIT_IER_IEMODEM 0x08  /* ��λΪ1����MODEM����״̬�仯�ж� */
#define BIT_IER_IELINES 0x04  /* ��λΪ1���������·״̬�ж� */
#define BIT_IER_IETHRE 0x02   /* ��λΪ1�����ͱ��ּĴ������ж� */
#define BIT_IER_IERECV 0x01   /* ��λΪ1������յ������ж� */

/* IIR�Ĵ�����λ */

#define BIT_IIR_FIFOENS1 0x80
#define BIT_IIR_FIFOENS0 0x40 /* ��2λΪ1��ʾ����FIFO */

/* �ж����ͣ�0001û���жϣ�0110������·״̬�жϣ�0100�������ݿ����жϣ�1100�������ݳ�ʱ�жϣ�0010THR�Ĵ������жϣ�0000MODEM����仯�ж� */
#define BIT_IIR_IID3 0x08
#define BIT_IIR_IID2 0x04 //�������ݿ���
#define BIT_IIR_IID1 0x02 //THR�Ĵ������ж�
#define BIT_IIR_NOINT 0x01

/* FCR�Ĵ�����λ */

/* �����㣺 00��Ӧ1���ֽڣ�01��Ӧ16���ֽڣ�10��Ӧ64���ֽڣ�11��Ӧ112���ֽ� */
#define BIT_FCR_RECVTG1 0x00 /* ����FIFO���жϺ��Զ�Ӳ�������ƵĴ����� */
#define BIT_FCR_RECVTG0 0x40 /* ����FIFO���жϺ��Զ�Ӳ�������ƵĴ����� */

#define BIT_FCR_TFIFORST 0x04 /* ��λ��1����շ���FIFO�е����� */
#define BIT_FCR_RFIFORST 0x02 /* ��λ��1����ս���FIFO�е����� */
#define BIT_FCR_FIFOEN 0x01   /* ��λ��1������FIFO,Ϊ0�����FIFO */

/* LCR�Ĵ�����λ */

#define BIT_LCR_DLAB 0x80    /* Ϊ1���ܴ�ȡDLL��DLM��Ϊ0���ܴ�ȡRBR/THR/IER */
#define BIT_LCR_BREAKEN 0x40 /* Ϊ1��ǿ�Ʋ���BREAK��·���*/

/* ����У���ʽ����PARENΪ1ʱ��00��У�飬01żУ�飬10��־λ��MARK����1)��11�հ�λ��SPACE����0) */
#define BIT_LCR_PARMODE1 0x20 /* ������żУ��λ��ʽ */
#define BIT_LCR_PARMODE0 0x10 /* ������żУ��λ��ʽ */

#define BIT_LCR_PAREN 0x08   /* Ϊ1��������ʱ�����ͽ���У����żУ��λ */
#define BIT_LCR_STOPBIT 0x04 /* Ϊ1������ֹͣλ,Ϊ0һ��ֹͣλ */

/* �����ֳ��ȣ�00��5������λ��01��6������λ��10��7������λ��11��8������λ */
#define BIT_LCR_WORDSZ1 0x02 /* �����ֳ����� */
#define BIT_LCR_WORDSZ0 0x01

/* MCR�Ĵ�����λ */

#define BIT_MCR_AFE 0x20  /* Ϊ1����CTS��RTSӲ���Զ������� */
#define BIT_MCR_LOOP 0x10 /* Ϊ1ʹ���ڲ���·�Ĳ���ģʽ */
#define BIT_MCR_OUT2 0x08 /* Ϊ1����ô��ڵ��ж�������� */
#define BIT_MCR_OUT1 0x04 /* Ϊ�û������MODEM����λ */
#define BIT_MCR_RTS 0x02  /* ��λΪ1��RTS���������Ч */
#define BIT_MCR_DTR 0x01  /* ��λΪ1��DTR���������Ч */

/* LSR�Ĵ�����λ */

#define BIT_LSR_RFIFOERR 0x80 /* Ϊ1��ʾ�ڽ���FIFO�д�������һ������ */
#define BIT_LSR_TEMT 0x40     /* Ϊ1��ʾTHR��TSRȫ�� */
#define BIT_LSR_THRE 0x20     /* Ϊ1��ʾTHR��*/
#define BIT_LSR_BREAKINT 0x10 /* ��λΪ1��ʾ��⵽BREAK��·��� */
#define BIT_LSR_FRAMEERR 0x08 /* ��λΪ1��ʾ��ȡ����֡���� */
#define BIT_LSR_PARERR 0x04   /* ��λΪ1��ʾ��żУ����� */
#define BIT_LSR_OVERR 0x02    /* Ϊ1��ʾ����FIFO��������� */
#define BIT_LSR_DATARDY 0x01  /* ��λΪ1��ʾ����FIFO���н��յ������� */

/* MSR�Ĵ�����λ */

#define BIT_MSR_DCD 0x80  /* ��λΪ1��ʾDCD������Ч */
#define BIT_MSR_RI 0x40   /* ��λΪ1��ʾRI������Ч */
#define BIT_MSR_DSR 0x20  /* ��λΪ1��ʾDSR������Ч */
#define BIT_MSR_CTS 0x10  /* ��λΪ1��ʾCTS������Ч */
#define BIT_MSR_DDCD 0x08 /* ��λΪ1��ʾDCD��������״̬�����仯�� */
#define BIT_MSR_TERI 0x04 /* ��λΪ1��ʾRI��������״̬�����仯�� */
#define BIT_MSR_DDSR 0x02 /* ��λΪ1��ʾDSR��������״̬�����仯�� */
#define BIT_MSR_DCTS 0x01 /* ��λΪ1��ʾCTS��������״̬�����仯�� */

/* �ж�״̬�� */

#define INT_NOINT 0x01        /* û���ж� */
#define INT_THR_EMPTY 0x02    /* THR���ж� */
#define INT_RCV_OVERTIME 0x0C /* ���ճ�ʱ�ж� */
#define INT_RCV_SUCCESS 0x04  /* �������ݿ����ж� */
#define INT_RCV_LINES 0x06    /* ������·״̬�ж� */
#define INT_MODEM_CHANGE 0x00 /* MODEM����仯�ж� */

#define CH438_IIR_FIFOS_ENABLED 0xC0 /* ����FIFO */

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
void OCD_CH438Q_CloseSeril(tagCH438Q_T *_tCH438Q, uint8_t _ucNum); /* �ر�ĳλ���� */
void OCD_CH438Q_CloseALLSeril(tagCH438Q_T *_tCH438Q); /* �ر����д��� */
void OCD_CH438Q_ResetSeril(tagCH438Q_T *_tCH438Q, uint8_t _ucNum); /* ��λ���� */
void OCD_CH438Q_SetBandrate(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint8_t _ucValue); /* ���ò����� δʹ�ô˺��� */
void OCD_CH438Q_SendDatas(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint8_t *_ucpSendBuff, uint8_t _ucLen);
unsigned char OCD_CH438Q_RecvDatas(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint8_t *_ucpRevBuff);
void OCD_CH438Q_GPIO_Init(tagCH438Q_T *_tCH438Q);
void OCD_CH438Q_Init(tagCH438Q_T *_tCH438Q); //IO���жϵȳ�ʼ��
void OCD_CH438Q_Uart_Init(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint16_t _ucValue);
void OCD_CH438Q_RxHandler(tagCH438Q_T *_tCH438Q);

#endif


