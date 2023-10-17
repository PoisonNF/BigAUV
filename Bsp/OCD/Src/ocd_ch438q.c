/****************************************************************************

* Sigma�Ŷ�

* �ļ���: ocd_ch438q.c

* ���ݼ�����ch438qģ���ļ�

* �ļ���ʷ��

* �汾��	����		����		˵��

* 1.0.0a 	2020-08-28	��Ծ��		�������ļ�

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

unsigned char Revbuff[MaxRecvLen]; /* ���ջ����� */
unsigned char RevLen;              /* ���ռ��� */

void Delay_1us(void)
{
    unsigned char a;
    for (a = 2; a > 0; a--)
        ;
}

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

void CH438_Init() //IO���жϵȳ�ʼ��
{
    AMOD_SET_HIGH;
    CS1_SET_HIGH;
    CS2_SET_HIGH;
	HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void CH438WriteReg(uint8_t ChipNum, uint8_t add, uint8_t data) /* //дһ���ֽڵ��Ĵ��� */
{
    //	uint16_t  value ;

    CS_SET_HIGH(ChipNum);
    //CS1_SET_HIGH;//CS = 1;

    WR_SET_HIGH; //WR = 1;
    RD_SET_HIGH; //RD = 1;
    SetOutPut();
    GPIOC->ODR = (GPIOC->ODR & 0XFF00) | add; /* //�Ͱ�λʮ����λȷ���߰�λ���ݲ���  д�Ĵ�����ַ */

    CS_SET_LOW(ChipNum);
    //CS1_SET_LOW;//CS = 0;

    ALE_SET_HIGH; //ALE =1;
    Delay_1us();
    ALE_SET_LOW; //ALE = 0;

    GPIOC->ODR = (GPIOC->ODR & 0XFF00) | data; /* //д���� */
    WR_SET_LOW;                                //WR =0 ;
    Delay_1us();
    WR_SET_HIGH; //WR =1;

    CS_SET_HIGH(ChipNum);
    //CS1_SET_HIGH;//CS =1;
}

uint8_t CH438ReadReg(uint8_t ChipNum, uint8_t add) /* //��ȡһ���ֽ� */
{
    uint8_t value;

    CS_SET_HIGH(ChipNum);
    //CS1_SET_HIGH;//CS = 1;

    WR_SET_HIGH; //WR =1;
    RD_SET_HIGH; //RD =1;
    SetOutPut(); //

    CS_SET_LOW(ChipNum);
    //CS1_SET_LOW;//CS = 0;

    ALE_SET_HIGH; //ALE =1;
    GPIOC->ODR = (GPIOC->ODR & 0XFF00) | add;
    ALE_SET_LOW; //	ALE = 0;
    SetInPut();
    RD_SET_LOW;         //RD = 0;
    value = GPIOC->IDR; //GPIO_ReadInputData(GPIOG);
                        //GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

    RD_SET_HIGH; //RD =1;

    CS_SET_HIGH(ChipNum);
    //CS1_SET_HIGH;//CS =1;

    return value;
}

unsigned char CH438_CheckIIR(uint8_t ChipNum, unsigned char num)
{
    unsigned char value;

    value = CH438ReadReg(ChipNum, offsetadd[num] | REG_IIR_ADDR);
    return value;
}

void CH438_CloseSeril(uint8_t ChipNum, unsigned char num) /* //�ر�ĳλ���� */
{
    CH438WriteReg(ChipNum, offsetadd[num] | REG_IER_ADDR, BIT_IER_LOWPOWER);
}

void CH438_CloseALLSeril(uint8_t ChipNum) /* //�ر����д��� */
{
    CH438WriteReg(ChipNum, offsetadd[0] | REG_IER_ADDR, BIT_IER_LOWPOWER | BIT_IER_SLP);
}

void CH438_ResetSeril(uint8_t ChipNum, unsigned char num) /*  //��λ���� */
{
    CH438WriteReg(ChipNum, offsetadd[num] | REG_IER_ADDR, BIT_IER_RESET);
}

void CH438_SetBandrate(uint8_t ChipNum, unsigned char num, unsigned long value) /* //���ò����� δʹ�ô˺��� */
{
    uint16_t bandspeed;

    bandspeed = Fpclk / 16 / value;
    CH438WriteReg(ChipNum, offsetadd[num] | REG_LCR_ADDR, BIT_LCR_DLAB);
    CH438WriteReg(ChipNum, offsetadd[num] | REG_DLL_ADDR, (uint8_t)bandspeed);
    CH438WriteReg(ChipNum, offsetadd[num] | REG_DLM_ADDR, (uint8_t)(bandspeed >> 8));

    //////////////////////////////////////////////////////////////////////////////////////
    // printf("bandrate: %d\n", bandspeed);
    // printf("DLM: %d\n", CH438ReadReg(offsetadd[num]|REG_DLM_ADDR));
    // printf("DLL: %d\n", CH438ReadReg(offsetadd[num]|REG_DLL_ADDR));
}

void CH438_UARTInit(uint8_t ChipNum, unsigned char num) /* //��ʼ��  δʹ�õ� */
{
    CH438_SetBandrate(ChipNum, num, 9600); /* CH438����1���������� */
    CH438_TranConfig(ChipNum, num);        /* CH438����1���ݸ�ʽ���ü�FIFO��С */
}

/* //�������� */
void CH438_SendDatas(uint8_t ChipNum, unsigned char num, unsigned char *sendbuff, unsigned char len)
{

    // do
    // {
    // 	while((CH438ReadReg(offsetadd[num]|REG_LSR_ADDR)&BIT_LSR_THRE)==0);    /* //LSR->THRE==1  ���ּĴ����� */

    // 		CH438WriteReg(offsetadd[num]|REG_THR_ADDR,*sendbuff++);
    // }while(--len);
    while (len)
    {
        if ((CH438ReadReg(ChipNum, offsetadd[num] | REG_LSR_ADDR) & BIT_LSR_THRE)) //LSR->THRE==1  ���ּĴ�����
        {
            CH438WriteReg(ChipNum, offsetadd[num] | REG_THR_ADDR, *sendbuff++);
            len--;
        }
    }
}

/* //�������� */
unsigned char CH438_RecvDatas(uint8_t ChipNum, unsigned char num, unsigned char *revbuff)
{
    uint8_t len = 0;
    uint8_t *p_rev;

    p_rev = revbuff;
    if (!(CH438ReadReg(ChipNum, offsetadd[num] | REG_LSR_ADDR) & (BIT_LSR_BREAKINT | BIT_LSR_FRAMEERR | BIT_LSR_PARERR | BIT_LSR_OVERR))) /* b1-b4�޴��� */
    {
        while ((CH438ReadReg(ChipNum, offsetadd[num] | REG_LSR_ADDR) & BIT_LSR_DATARDY) == 0); /*�ȴ�����׼���� */
				
        do
        {
            *p_rev = CH438ReadReg(ChipNum, offsetadd[num] | REG_RBR_ADDR);
            p_rev++;
            len++;
        } while ((CH438ReadReg(ChipNum, offsetadd[num] | REG_LSR_ADDR) & BIT_LSR_DATARDY)); /* //LSR->DATARDY==1 */
    }
    else
        CH438ReadReg(ChipNum, offsetadd[num] | REG_RBR_ADDR);

    return len;
}

void CH438_TranConfig(uint8_t ChipNum, unsigned char num)
{
    /* �������ݸ�ʽ:8λ���ݣ���У�飬1��ֹͣλ  */
    CH438WriteReg(ChipNum, offsetadd[num] | REG_LCR_ADDR, BIT_LCR_WORDSZ1 | BIT_LCR_WORDSZ0);
    /* ����FIFOģʽ��������Ϊ112�ֽ� */
    CH438WriteReg(ChipNum, offsetadd[num] | REG_FCR_ADDR, BIT_FCR_RECVTG1 | BIT_FCR_RECVTG0 | BIT_FCR_FIFOEN);
    CH438WriteReg(ChipNum, offsetadd[num] | REG_FCR_ADDR, CH438ReadReg(CHIP1, offsetadd[num] | REG_FCR_ADDR) | BIT_FCR_TFIFORST | BIT_FCR_RFIFORST);
}

void CH438_INTConfig(uint8_t ChipNum, unsigned char num)
{
    /* ע��: CH438��BIT_IER_IETHRE�ж�(0->1),�����һ���������ж� */
    CH438WriteReg(CHIP1, offsetadd[num] | REG_IER_ADDR, BIT_IER_IELINES | BIT_IER_IETHRE | BIT_IER_IERECV);
    CH438_CheckIIR(ChipNum, num);
    CH438WriteReg(CHIP1, offsetadd[num] | REG_MCR_ADDR, BIT_MCR_OUT2 | BIT_MCR_RTS | BIT_MCR_DTR); /* //���Բ���һ��ʵ�ʵ��ж� */
}

void CH438_AutoHFCtrl(uint8_t ChipNum, unsigned char num)
{
    CH438WriteReg(ChipNum, offsetadd[num] | REG_MCR_ADDR, BIT_MCR_AFE | BIT_MCR_OUT2 | BIT_MCR_RTS); /* ����MCR�Ĵ�����AFE��RTSΪ1 */
}

/* //�жϴ����� */

extern uint8_t CH438Q_buf[50]; //CH438Q�������ݽ��ջ�����
extern uint8_t CH438Q_flag; //CH438Q�������ݽ�����ɱ�־
extern uint8_t CH438Q_NUM; //CH438Q���ں�

//void EXTI1_IRQHandler()
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t gInterruptStatus;
    uint8_t InterruptStatus;
    uint8_t i;
    //HAL_NVIC_DisableIRQ(EXTI2_IRQn);

    gInterruptStatus = CH438ReadReg(CHIP1, REG_SSR_ADDR);

    if (!gInterruptStatus)
    {
        return;
    }

    for (i = 0; i < 8; i++)
    {
        if (gInterruptStatus & Interruptnum[i]) /* ����ĸ����ڷ����ж� */
        {
            InterruptStatus = CH438ReadReg(CHIP1, offsetadd[i] | REG_IIR_ADDR) & 0x0f; /* �����ڵ��ж�״̬ */

            switch (InterruptStatus)
            {
            case INT_NOINT: /* û���ж� */
                break;
            case INT_THR_EMPTY: /* THR���ж� */
                break;
            case INT_RCV_OVERTIME: /* ���ճ�ʱ�ж� */
                RevLen = CH438_RecvDatas(CHIP1, i, Revbuff);
				memcpy(CH438Q_buf, Revbuff, 50);
		     	CH438Q_NUM = i;
				CH438Q_flag = SET;
//                CH438_SendDatas(CHIP1, i, Revbuff, RevLen);
				memset(Revbuff, 0, MaxRecvLen);
                break;
            case INT_RCV_SUCCESS: /* �������ݿ����ж� */
                RevLen = CH438_RecvDatas(CHIP1, i, Revbuff);
                CH438_SendDatas(CHIP1, i, Revbuff, RevLen);
                break;
            case INT_RCV_LINES: /* ������·״̬�ж� */
                CH438ReadReg(CHIP1, offsetadd[i] | REG_LSR_ADDR);
                break;
            case INT_MODEM_CHANGE: /* MODEM����仯�ж� */
                CH438ReadReg(CHIP1, offsetadd[i] | REG_MSR_ADDR);
                break;
            default:
                break;
            }
        }
    }

    //HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}

void CH438_RegTEST(uint8_t ChipNum, unsigned char num) /* //����ʹ�õĺ��� */
{
    //////////////////////////////////////////////////////////////////////////////////////
    // printf("current test serilnum: %d \r\n",(unsigned short)offsetadd[num]);
    // printf("IER: %02x\r\n",(unsigned short)CH438ReadReg(offsetadd[num] | REG_IER_ADDR));//?IER
    // printf("IIR: %02x\r\n",(unsigned short)CH438ReadReg(offsetadd[num] | REG_IIR_ADDR));//?IIR
    // printf("LCR: %02x\r\n",(unsigned short)CH438ReadReg(offsetadd[num] | REG_LCR_ADDR));//?LCR
    // printf("MCR: %02x\r\n",(unsigned short)CH438ReadReg(offsetadd[num] | REG_MCR_ADDR));//?MCR
    // printf("LSR: %02x\r\n",(unsigned short)CH438ReadReg(offsetadd[num] | REG_LSR_ADDR));//?LSR
    // printf("MSR: %02x\r\n",(unsigned short)CH438ReadReg(offsetadd[num] | REG_MSR_ADDR));//?MSR
    // //CH438WriteReg(offsetadd[num] | REG_SCR_ADDR, 0x78);
    // printf("SCR: %02x\r\n",(unsigned short)CH438ReadReg(offsetadd[num] | REG_SCR_ADDR));//?SCR
    // printf("FCR: %02x\r\n",(unsigned short)CH438ReadReg(offsetadd[num] | REG_FCR_ADDR));//?SCR
}

/* //���ڳ�ʼ������ ������� ���ںźͲ����� */
void CH438_Uart_Init(uint8_t ChipNum, unsigned char num, unsigned long value)
{

    // uint8_t dlab=1;
    // uint16_t bandspeed;
    // dlab = CH438ReadReg(offsetadd[num]|REG_IER_ADDR);
    // dlab &= 0xDF;
    // CH438WriteReg(offsetadd[num]|REG_IER_ADDR, dlab);

    // dlab = CH438ReadReg(offsetadd[num]|REG_LCR_ADDR);
    // dlab |= 0x80;		/* //��LCR�Ĵ���DLABλΪ1 */
    // CH438WriteReg(offsetadd[num]|REG_LCR_ADDR, dlab);

    // bandspeed = Fpclk/16/value;
    // CH438WriteReg(offsetadd[num]|REG_DLL_ADDR, (uint8_t)bandspeed);
    // CH438WriteReg(offsetadd[num]|REG_DLM_ADDR, (uint8_t)(bandspeed>>8));
    // dlab &= 0x7F;		/* //��IIR�Ĵ���DLABλΪ0 */
    // CH438WriteReg(offsetadd[num]|REG_LCR_ADDR, dlab);
    // CH438WriteReg(offsetadd[num]|REG_FCR_ADDR,BIT_FCR_RECVTG1 | BIT_FCR_RECVTG0 | BIT_FCR_FIFOEN );
    // CH438WriteReg(offsetadd[num]|REG_LCR_ADDR,BIT_LCR_WORDSZ1 | BIT_LCR_WORDSZ0 );
    // CH438WriteReg(offsetadd[num]|REG_IER_ADDR,BIT_IER_IELINES | BIT_IER_IETHRE | BIT_IER_IERECV);
    // CH438WriteReg(offsetadd[num]|REG_MCR_ADDR,BIT_MCR_OUT2    | BIT_MCR_RTS     | BIT_MCR_DTR);
    // CH438WriteReg(offsetadd[num]|REG_FCR_ADDR,CH438ReadReg(offsetadd[num]|REG_FCR_ADDR)| BIT_FCR_TFIFORST|BIT_FCR_RFIFORST);

    uint16_t div;
    uint8_t DLL, DLM;

    /**************************************************************************
          ����CH438����num�ļĴ���
**************************************************************************/
    div = (Fpclk >> 4) / value;
    DLM = div >> 8;
    DLL = div & 0xff;
    CH438WriteReg(ChipNum, offsetadd[num] | REG_LCR_ADDR, BIT_LCR_DLAB); /* ����DLABΪ1 */
    CH438WriteReg(ChipNum, offsetadd[num] | REG_DLL_ADDR, DLL);          /* ���ò����� */
    CH438WriteReg(ChipNum, offsetadd[num] | REG_DLM_ADDR, DLM);

    CH438WriteReg(ChipNum, offsetadd[num] | REG_FCR_ADDR, BIT_FCR_RECVTG1 | BIT_FCR_RECVTG0 | BIT_FCR_FIFOEN); /* ����FIFOģʽ��������Ϊ16�ֽ� */

    CH438WriteReg(ChipNum, offsetadd[num] | REG_LCR_ADDR, BIT_LCR_WORDSZ1 | BIT_LCR_WORDSZ0); /* �ֳ�8λ��1λֹͣλ����У�� */ /* ����DLABΪ0 */

    CH438WriteReg(ChipNum, offsetadd[num] | REG_IER_ADDR, BIT_IER_IERECV); /* ʹ���ж� */ //| BIT_IER_IETHRE  BIT_IER_IEMODEM | BIT_IER_IELINES |

    CH438WriteReg(ChipNum, offsetadd[num] | REG_MCR_ADDR, BIT_MCR_OUT2); //| BIT_MCR_RTS     | BIT_MCR_DTR );              /* �����ж����,DTR,RTSΪ1 */

    CH438WriteReg(ChipNum, offsetadd[num] | REG_FCR_ADDR, CH438ReadReg(ChipNum, offsetadd[num] | REG_FCR_ADDR) | BIT_FCR_TFIFORST | BIT_FCR_RFIFORST); /* ���FIFO�е����� */
}


