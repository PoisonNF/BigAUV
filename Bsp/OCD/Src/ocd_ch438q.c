/****************************************************************************

* Sigma�Ŷ�

* �ļ���: ocd_ch438q.c

* ���ݼ�����ch438qģ���ļ�

* �ļ���ʷ��

* �汾��	����		����		˵��

* 1.0.0a 	2022-08-28	��Ծ��		�������ļ�

****************************************************************************/
#include "ocd_ch438q.h"

#define Fpclk 1843200 /* �����ڲ�ʱ��Ƶ��,Ĭ���ⲿ�����12��Ƶ    */
#define MaxRecvLen 50 /* ���ջ�������С    */

const unsigned char offsetadd[] = {
    0x00,
    0x10,
    0x20,
    0x30,
    0x08,
    0x18,
    0x28,
    0x38,
}; /* ���ںŵ�ƫ�Ƶ�ַ */

const unsigned char Interruptnum[] = {
    0x01,
    0x02,
    0x04,
    0x08,
    0x10,
    0x20,
    0x40,
    0x80,
}; /* SSR�Ĵ����жϺŶ�Ӧֵ */

void SetOutPut() //IO���ģʽ
{
    GPIOC->CRL &= 0;
    GPIOC->CRL = 0X33333333;
}

void SetInPut() //IO����ģʽ
{
    GPIOC->CRL &= 0;
    GPIOC->CRL = 0X88888888;
}

static void S_CH438Q_DelayUs(void)
{
    Drv_Delay_Us(1);
}

static void S_CH438Q_CS_H(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Set(&_tCH438Q->tCH438Q_GPIO.tGPIO_CS);
}

static void S_CH438Q_CS_L(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Reset(&_tCH438Q->tCH438Q_GPIO.tGPIO_CS);
}

static void S_CH438Q_RD_H(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Set(&_tCH438Q->tCH438Q_GPIO.tGPIO_RD);
}

static void S_CH438Q_RD_L(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Reset(&_tCH438Q->tCH438Q_GPIO.tGPIO_RD);
}

static void S_CH438Q_WR_H(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Set(&_tCH438Q->tCH438Q_GPIO.tGPIO_WR);
}

static void S_CH438Q_WR_L(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Reset(&_tCH438Q->tCH438Q_GPIO.tGPIO_WR);
}

static void S_CH438Q_AMOD_H(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Set(&_tCH438Q->tCH438Q_GPIO.tGPIO_AMOD);
}

static void S_CH438Q_AMOD_L(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Reset(&_tCH438Q->tCH438Q_GPIO.tGPIO_AMOD);
}

static void S_CH438Q_ALE_H(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Set(&_tCH438Q->tCH438Q_GPIO.tGPIO_ALE);
}

static void S_CH438Q_ALE_L(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Reset(&_tCH438Q->tCH438Q_GPIO.tGPIO_ALE);
}

static void S_CH438Q_IO_OutPut(tagCH438Q_T *_tCH438Q) //IO���ģʽ
{
    _tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->CRL &= 0;
    _tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->CRL = 0X33333333;
}

static void S_CH438Q_IO_InPut(tagCH438Q_T *_tCH438Q) //IO����ģʽ
{
    _tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->CRL &= 0;
    _tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->CRL = 0X88888888;
}

static void S_CH438Q_WriteReg(tagCH438Q_T *_tCH438Q, uint8_t _ucAdd, uint8_t _ucData) /* //дһ���ֽڵ��Ĵ��� */
{
    //	uint16_t  value ;
    S_CH438Q_CS_H(_tCH438Q);//CS1_SET_HIGH;//CS = 1;
    S_CH438Q_WR_H(_tCH438Q);
    S_CH438Q_RD_H(_tCH438Q); //WR = 1,RD = 1
    S_CH438Q_IO_OutPut(_tCH438Q);

    _tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->ODR = (_tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->ODR & 0XFF00) | _ucAdd; /* //�Ͱ�λʮ����λȷ���߰�λ���ݲ���  д�Ĵ�����ַ */

    S_CH438Q_CS_L(_tCH438Q);//CS1_SET_LOW;//CS = 0;

    S_CH438Q_ALE_H(_tCH438Q); //ALE =1;
    S_CH438Q_DelayUs();
    S_CH438Q_ALE_L(_tCH438Q); //ALE = 0;

    _tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->ODR = (_tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->ODR & 0XFF00) | _ucData; /* //д���� */

    S_CH438Q_WR_L(_tCH438Q); //WR =0 ;
    S_CH438Q_DelayUs();
    S_CH438Q_WR_H(_tCH438Q); //WR =1;

    S_CH438Q_CS_H(_tCH438Q);
    //CS1_SET_HIGH;//CS =1;
}

static uint8_t S_CH438Q_ReadReg(tagCH438Q_T *_tCH438Q, uint8_t _ucAdd) /* //��ȡһ���ֽ� */
{
    uint8_t ucValue;

    S_CH438Q_CS_H(_tCH438Q);//CS1_SET_HIGH;//CS = 1;
    S_CH438Q_WR_H(_tCH438Q);
    S_CH438Q_RD_H(_tCH438Q); //WR = 1,RD = 1
    S_CH438Q_IO_OutPut(_tCH438Q);

    S_CH438Q_CS_L(_tCH438Q); //CS1_SET_LOW;//CS = 0;

    S_CH438Q_ALE_H(_tCH438Q); //ALE =1;
    _tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->ODR = (_tCH438Q->tCH438Q_GPIO.tGPIO_DATA[0].tGPIOPort->ODR & 0XFF00) | _ucAdd;
    S_CH438Q_ALE_L(_tCH438Q); //	ALE = 0;
    S_CH438Q_IO_InPut(_tCH438Q);

    S_CH438Q_RD_L(_tCH438Q);         //RD = 0;
    ucValue = GPIOC->IDR;
    S_CH438Q_RD_H(_tCH438Q); //RD =1;

    S_CH438Q_CS_H(_tCH438Q); //CS1_SET_HIGH;//CS =1;

    return ucValue;
}

uint8_t OCD_CH438Q_CheckIIR(tagCH438Q_T *_tCH438Q, uint8_t _ucNum)
{
    uint8_t ucValue;

    ucValue = S_CH438Q_ReadReg(_tCH438Q, offsetadd[_ucNum] | REG_IIR_ADDR);
    return ucValue;
}

void OCD_CH438Q_CloseSeril(tagCH438Q_T *_tCH438Q, uint8_t _ucNum) /* //�ر�ĳλ���� */
{
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_IER_ADDR, BIT_IER_LOWPOWER);
}

void OCD_CH438Q_CloseALLSeril(tagCH438Q_T *_tCH438Q) /* //�ر����д��� */
{
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[0] | REG_IER_ADDR, BIT_IER_LOWPOWER | BIT_IER_SLP);
}

void OCD_CH438Q_ResetSeril(tagCH438Q_T *_tCH438Q, uint8_t _ucNum) /*  //��λ���� */
{
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_IER_ADDR, BIT_IER_RESET);
}

void OCD_CH438Q_SetBandrate(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint8_t _ucValue) /* //���ò����� δʹ�ô˺��� */
{
    uint16_t usBandspeed;

    usBandspeed = Fpclk / 16 / _ucValue;
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_LCR_ADDR, BIT_LCR_DLAB);
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_DLL_ADDR, (uint8_t)usBandspeed);
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_DLM_ADDR, (uint8_t)(usBandspeed >> 8));
}

/* //�������� */
void OCD_CH438Q_SendDatas(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint8_t *_ucpSendBuff, uint8_t _ucLen)
{
    while(_ucLen)
    {
        if((S_CH438Q_ReadReg(_tCH438Q, offsetadd[_ucNum] | REG_LSR_ADDR) & BIT_LSR_THRE)) //LSR->THRE==1  ���ּĴ�����
        {
            S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_THR_ADDR, *_ucpSendBuff++);
            _ucLen--;
        }
    }
}

/* //�������� */
unsigned char OCD_CH438Q_RecvDatas(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint8_t *_ucpRevBuff)
{
    uint8_t uclen = 0;
    uint8_t *ucpRev;

    ucpRev = _ucpRevBuff;
    if(!(S_CH438Q_ReadReg(_tCH438Q, offsetadd[_ucNum] | REG_LSR_ADDR) & (BIT_LSR_BREAKINT | BIT_LSR_FRAMEERR | BIT_LSR_PARERR | BIT_LSR_OVERR))) /* b1-b4�޴��� */
    {
        while((S_CH438Q_ReadReg(_tCH438Q, offsetadd[_ucNum] | REG_LSR_ADDR) & BIT_LSR_DATARDY) == 0); /*�ȴ�����׼���� */
			
        do{
            *ucpRev = S_CH438Q_ReadReg(_tCH438Q, offsetadd[_ucNum] | REG_RBR_ADDR);
            ucpRev++;
            uclen++;
        }while((S_CH438Q_ReadReg(_tCH438Q, offsetadd[_ucNum] | REG_LSR_ADDR) & BIT_LSR_DATARDY)); /* //LSR->DATARDY==1 */
    }
    else
        S_CH438Q_ReadReg(_tCH438Q, offsetadd[_ucNum] | REG_RBR_ADDR);

    return uclen;
}

void OCD_CH438Q_GPIO_Init(tagCH438Q_T *_tCH438Q)
{
    Drv_GPIO_Init(&_tCH438Q->tCH438Q_GPIO.tGPIO_CS, 1);
    Drv_GPIO_Init(&_tCH438Q->tCH438Q_GPIO.tGPIO_RD, 1);
    Drv_GPIO_Init(&_tCH438Q->tCH438Q_GPIO.tGPIO_WR, 1);
    Drv_GPIO_Init(&_tCH438Q->tCH438Q_GPIO.tGPIO_AMOD, 1);
    Drv_GPIO_Init(&_tCH438Q->tCH438Q_GPIO.tGPIO_ALE, 1);
    Drv_GPIO_Init(&_tCH438Q->tCH438Q_GPIO.tGPIO_INT, 1);
    Drv_GPIO_Init(_tCH438Q->tCH438Q_GPIO.tGPIO_DATA, 8);
}

/* //���ڳ�ʼ������ ������� ���ںźͲ����� */
void OCD_CH438Q_Uart_Init(tagCH438Q_T *_tCH438Q, uint8_t _ucNum, uint16_t _ucValue)
{
    uint16_t usDiv;
    uint8_t ucDLL, ucDLM;

    /**************************************************************************
          ����CH438����num�ļĴ���
    **************************************************************************/
    usDiv = (Fpclk >> 4) / _ucValue;
    ucDLM = usDiv >> 8;
    ucDLL = usDiv & 0xff;
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_LCR_ADDR, BIT_LCR_DLAB); /* ����DLABΪ1 */
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_DLL_ADDR, ucDLL);          /* ���ò����� */
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_DLM_ADDR, ucDLM);

    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_FCR_ADDR, BIT_FCR_RECVTG1 | BIT_FCR_RECVTG0 | BIT_FCR_FIFOEN); /* ����FIFOģʽ��������Ϊ16�ֽ� */
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_LCR_ADDR, BIT_LCR_WORDSZ1 | BIT_LCR_WORDSZ0); /* �ֳ�8λ��1λֹͣλ����У�� */ /* ����DLABΪ0 */
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_IER_ADDR, BIT_IER_IERECV); /* ʹ���ж� */ //| BIT_IER_IETHRE  BIT_IER_IEMODEM | BIT_IER_IELINES |
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_MCR_ADDR, BIT_MCR_OUT2); //| BIT_MCR_RTS     | BIT_MCR_DTR );              /* �����ж����,DTR,RTSΪ1 */
    S_CH438Q_WriteReg(_tCH438Q, offsetadd[_ucNum] | REG_FCR_ADDR, S_CH438Q_ReadReg(_tCH438Q, offsetadd[_ucNum] | REG_FCR_ADDR) | BIT_FCR_TFIFORST | BIT_FCR_RFIFORST); /* ���FIFO�е����� */
}

void OCD_CH438Q_Init(tagCH438Q_T *_tCH438Q) //IO���жϵȳ�ʼ��
{
    uint8_t ucNum = 0;
    OCD_CH438Q_GPIO_Init(_tCH438Q);
    S_CH438Q_AMOD_H(_tCH438Q);
    S_CH438Q_CS_H(_tCH438Q);

    for(ucNum = 0; ucNum < 8; ucNum++)
    {
        S_CH438Q_WriteReg(_tCH438Q, offsetadd[0] | REG_IER_ADDR, BIT_IER_RESET);
        OCD_CH438Q_Uart_Init(_tCH438Q, 0, 9600);
    }
}

/* //�жϴ����� */
extern uint8_t CH438Q_buf[50]; //CH438Q�������ݽ��ջ�����
extern uint8_t CH438Q_flag; //CH438Q�������ݽ�����ɱ�־
extern uint8_t CH438Q_NUM; //CH438Q���ں�
unsigned char Revbuff[MaxRecvLen]; /* ���ջ����� */
unsigned char RevLen;              /* ���ռ��� */

void OCD_CH438Q_RxHandler(tagCH438Q_T *_tCH438Q)
{
    uint8_t gInterruptStatus;
    uint8_t InterruptStatus;
    uint8_t i;

    gInterruptStatus = S_CH438Q_ReadReg(_tCH438Q, REG_SSR_ADDR);

    if (!gInterruptStatus)
    {
        return;
    }

    for (i = 0; i < 8; i++)
    {
        if (gInterruptStatus & Interruptnum[i]) /* ����ĸ����ڷ����ж� */
        {
            InterruptStatus = S_CH438Q_ReadReg(_tCH438Q, offsetadd[i] | REG_IIR_ADDR) & 0x0f; /* �����ڵ��ж�״̬ */

            switch (InterruptStatus)
            {
                case INT_NOINT: /* û���ж� */
                    break;
                case INT_THR_EMPTY: /* THR���ж� */
                    break;
                case INT_RCV_OVERTIME: /* ���ճ�ʱ�ж� */
                    RevLen = OCD_CH438Q_RecvDatas(_tCH438Q, i, Revbuff);
                    memcpy(CH438Q_buf, Revbuff, 50);
                    CH438Q_NUM = i;
                    CH438Q_flag = SET;
    //                CH438_SendDatas(CHIP1, i, Revbuff, RevLen);
                    memset(Revbuff, 0, MaxRecvLen);
                    break;
                case INT_RCV_SUCCESS: /* �������ݿ����ж� */
                    RevLen = OCD_CH438Q_RecvDatas(_tCH438Q, i, Revbuff);
                    OCD_CH438Q_SendDatas(_tCH438Q, i, Revbuff, RevLen);
                    break;
                case INT_RCV_LINES: /* ������·״̬�ж� */
                    S_CH438Q_ReadReg(_tCH438Q, offsetadd[i] | REG_LSR_ADDR);
                    break;
                case INT_MODEM_CHANGE: /* MODEM����仯�ж� */
                    S_CH438Q_ReadReg(_tCH438Q, offsetadd[i] | REG_MSR_ADDR);
                    break;
                default:
                    break;
            }
        }
    }
}



