/****************************************************************************

* Sigma团队

* 文件名: ocd_ch438q.c

* 内容简述：ch438q模块文件

* 文件历史：

* 版本号	日期		作者		说明

* 1.0.0a 	2020-08-28	张跃男		创建该文件

****************************************************************************/
#include "ocd_ch438q.h"

#define Fpclk 1843200 /* 定义内部时钟频率,默认外部晶振的12分频    */
#define MaxRecvLen 50 /* 接收缓冲区大小    */

const unsigned char offsetadd[] = {
    0x00,
    0x10,
    0x20,
    0x30,
    0x08,
    0x18,
    0x28,
    0x38,
}; /* 串口号的偏移地址 */

const unsigned char Interruptnum[] = {
    0x01,
    0x02,
    0x04,
    0x08,
    0x10,
    0x20,
    0x40,
    0x80,
}; /* SSR寄存器中断号对应值 */

unsigned char Revbuff[MaxRecvLen]; /* 接收缓存区 */
unsigned char RevLen;              /* 接收计数 */

void Delay_1us(void)
{
    unsigned char a;
    for (a = 2; a > 0; a--)
        ;
}

void SetOutPut() //IO输出模式
{
    GPIOC->CRL &= 0;
    GPIOC->CRL = 0X33333333;
}

void SetInPut() //IO输入模式
{
    GPIOC->CRL &= 0;
    GPIOC->CRL = 0X88888888;
}

void CH438_Init() //IO口中断等初始化
{
    AMOD_SET_HIGH;
    CS1_SET_HIGH;
    CS2_SET_HIGH;
	HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void CH438WriteReg(uint8_t ChipNum, uint8_t add, uint8_t data) /* //写一个字节到寄存器 */
{
    //	uint16_t  value ;

    CS_SET_HIGH(ChipNum);
    //CS1_SET_HIGH;//CS = 1;

    WR_SET_HIGH; //WR = 1;
    RD_SET_HIGH; //RD = 1;
    SetOutPut();
    GPIOC->ODR = (GPIOC->ODR & 0XFF00) | add; /* //低八位十数据位确保高八位数据不变  写寄存器地址 */

    CS_SET_LOW(ChipNum);
    //CS1_SET_LOW;//CS = 0;

    ALE_SET_HIGH; //ALE =1;
    Delay_1us();
    ALE_SET_LOW; //ALE = 0;

    GPIOC->ODR = (GPIOC->ODR & 0XFF00) | data; /* //写数据 */
    WR_SET_LOW;                                //WR =0 ;
    Delay_1us();
    WR_SET_HIGH; //WR =1;

    CS_SET_HIGH(ChipNum);
    //CS1_SET_HIGH;//CS =1;
}

uint8_t CH438ReadReg(uint8_t ChipNum, uint8_t add) /* //读取一个字节 */
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

void CH438_CloseSeril(uint8_t ChipNum, unsigned char num) /* //关闭某位串口 */
{
    CH438WriteReg(ChipNum, offsetadd[num] | REG_IER_ADDR, BIT_IER_LOWPOWER);
}

void CH438_CloseALLSeril(uint8_t ChipNum) /* //关闭所有串口 */
{
    CH438WriteReg(ChipNum, offsetadd[0] | REG_IER_ADDR, BIT_IER_LOWPOWER | BIT_IER_SLP);
}

void CH438_ResetSeril(uint8_t ChipNum, unsigned char num) /*  //复位串口 */
{
    CH438WriteReg(ChipNum, offsetadd[num] | REG_IER_ADDR, BIT_IER_RESET);
}

void CH438_SetBandrate(uint8_t ChipNum, unsigned char num, unsigned long value) /* //设置波特率 未使用此函数 */
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

void CH438_UARTInit(uint8_t ChipNum, unsigned char num) /* //初始化  未使用到 */
{
    CH438_SetBandrate(ChipNum, num, 9600); /* CH438串口1波特率设置 */
    CH438_TranConfig(ChipNum, num);        /* CH438串口1数据格式配置及FIFO大小 */
}

/* //发送数据 */
void CH438_SendDatas(uint8_t ChipNum, unsigned char num, unsigned char *sendbuff, unsigned char len)
{

    // do
    // {
    // 	while((CH438ReadReg(offsetadd[num]|REG_LSR_ADDR)&BIT_LSR_THRE)==0);    /* //LSR->THRE==1  保持寄存器空 */

    // 		CH438WriteReg(offsetadd[num]|REG_THR_ADDR,*sendbuff++);
    // }while(--len);
    while (len)
    {
        if ((CH438ReadReg(ChipNum, offsetadd[num] | REG_LSR_ADDR) & BIT_LSR_THRE)) //LSR->THRE==1  保持寄存器空
        {
            CH438WriteReg(ChipNum, offsetadd[num] | REG_THR_ADDR, *sendbuff++);
            len--;
        }
    }
}

/* //接收数据 */
unsigned char CH438_RecvDatas(uint8_t ChipNum, unsigned char num, unsigned char *revbuff)
{
    uint8_t len = 0;
    uint8_t *p_rev;

    p_rev = revbuff;
    if (!(CH438ReadReg(ChipNum, offsetadd[num] | REG_LSR_ADDR) & (BIT_LSR_BREAKINT | BIT_LSR_FRAMEERR | BIT_LSR_PARERR | BIT_LSR_OVERR))) /* b1-b4无错误 */
    {
        while ((CH438ReadReg(ChipNum, offsetadd[num] | REG_LSR_ADDR) & BIT_LSR_DATARDY) == 0); /*等待数据准备好 */
				
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
    /* 发送数据格式:8位数据，无校验，1个停止位  */
    CH438WriteReg(ChipNum, offsetadd[num] | REG_LCR_ADDR, BIT_LCR_WORDSZ1 | BIT_LCR_WORDSZ0);
    /* 设置FIFO模式，触发点为112字节 */
    CH438WriteReg(ChipNum, offsetadd[num] | REG_FCR_ADDR, BIT_FCR_RECVTG1 | BIT_FCR_RECVTG0 | BIT_FCR_FIFOEN);
    CH438WriteReg(ChipNum, offsetadd[num] | REG_FCR_ADDR, CH438ReadReg(CHIP1, offsetadd[num] | REG_FCR_ADDR) | BIT_FCR_TFIFORST | BIT_FCR_RFIFORST);
}

void CH438_INTConfig(uint8_t ChipNum, unsigned char num)
{
    /* 注意: CH438打开BIT_IER_IETHRE中断(0->1),会产生一个发生空中断 */
    CH438WriteReg(CHIP1, offsetadd[num] | REG_IER_ADDR, BIT_IER_IELINES | BIT_IER_IETHRE | BIT_IER_IERECV);
    CH438_CheckIIR(ChipNum, num);
    CH438WriteReg(CHIP1, offsetadd[num] | REG_MCR_ADDR, BIT_MCR_OUT2 | BIT_MCR_RTS | BIT_MCR_DTR); /* //可以产生一个实际的中断 */
}

void CH438_AutoHFCtrl(uint8_t ChipNum, unsigned char num)
{
    CH438WriteReg(ChipNum, offsetadd[num] | REG_MCR_ADDR, BIT_MCR_AFE | BIT_MCR_OUT2 | BIT_MCR_RTS); /* 设置MCR寄存器的AFE和RTS为1 */
}

/* //中断处理函数 */

extern uint8_t CH438Q_buf[50]; //CH438Q串口数据接收缓冲区
extern uint8_t CH438Q_flag; //CH438Q串口数据接收完成标志
extern uint8_t CH438Q_NUM; //CH438Q串口号

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
        if (gInterruptStatus & Interruptnum[i]) /* 检测哪个串口发生中断 */
        {
            InterruptStatus = CH438ReadReg(CHIP1, offsetadd[i] | REG_IIR_ADDR) & 0x0f; /* 读串口的中断状态 */

            switch (InterruptStatus)
            {
            case INT_NOINT: /* 没有中断 */
                break;
            case INT_THR_EMPTY: /* THR空中断 */
                break;
            case INT_RCV_OVERTIME: /* 接收超时中断 */
                RevLen = CH438_RecvDatas(CHIP1, i, Revbuff);
				memcpy(CH438Q_buf, Revbuff, 50);
		     	CH438Q_NUM = i;
				CH438Q_flag = SET;
//                CH438_SendDatas(CHIP1, i, Revbuff, RevLen);
				memset(Revbuff, 0, MaxRecvLen);
                break;
            case INT_RCV_SUCCESS: /* 接收数据可用中断 */
                RevLen = CH438_RecvDatas(CHIP1, i, Revbuff);
                CH438_SendDatas(CHIP1, i, Revbuff, RevLen);
                break;
            case INT_RCV_LINES: /* 接收线路状态中断 */
                CH438ReadReg(CHIP1, offsetadd[i] | REG_LSR_ADDR);
                break;
            case INT_MODEM_CHANGE: /* MODEM输入变化中断 */
                CH438ReadReg(CHIP1, offsetadd[i] | REG_MSR_ADDR);
                break;
            default:
                break;
            }
        }
    }

    //HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}

void CH438_RegTEST(uint8_t ChipNum, unsigned char num) /* //测试使用的函数 */
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

/* //串口初始化函数 输入参数 串口号和波特率 */
void CH438_Uart_Init(uint8_t ChipNum, unsigned char num, unsigned long value)
{

    // uint8_t dlab=1;
    // uint16_t bandspeed;
    // dlab = CH438ReadReg(offsetadd[num]|REG_IER_ADDR);
    // dlab &= 0xDF;
    // CH438WriteReg(offsetadd[num]|REG_IER_ADDR, dlab);

    // dlab = CH438ReadReg(offsetadd[num]|REG_LCR_ADDR);
    // dlab |= 0x80;		/* //置LCR寄存器DLAB位为1 */
    // CH438WriteReg(offsetadd[num]|REG_LCR_ADDR, dlab);

    // bandspeed = Fpclk/16/value;
    // CH438WriteReg(offsetadd[num]|REG_DLL_ADDR, (uint8_t)bandspeed);
    // CH438WriteReg(offsetadd[num]|REG_DLM_ADDR, (uint8_t)(bandspeed>>8));
    // dlab &= 0x7F;		/* //置IIR寄存器DLAB位为0 */
    // CH438WriteReg(offsetadd[num]|REG_LCR_ADDR, dlab);
    // CH438WriteReg(offsetadd[num]|REG_FCR_ADDR,BIT_FCR_RECVTG1 | BIT_FCR_RECVTG0 | BIT_FCR_FIFOEN );
    // CH438WriteReg(offsetadd[num]|REG_LCR_ADDR,BIT_LCR_WORDSZ1 | BIT_LCR_WORDSZ0 );
    // CH438WriteReg(offsetadd[num]|REG_IER_ADDR,BIT_IER_IELINES | BIT_IER_IETHRE | BIT_IER_IERECV);
    // CH438WriteReg(offsetadd[num]|REG_MCR_ADDR,BIT_MCR_OUT2    | BIT_MCR_RTS     | BIT_MCR_DTR);
    // CH438WriteReg(offsetadd[num]|REG_FCR_ADDR,CH438ReadReg(offsetadd[num]|REG_FCR_ADDR)| BIT_FCR_TFIFORST|BIT_FCR_RFIFORST);

    uint16_t div;
    uint8_t DLL, DLM;

    /**************************************************************************
          设置CH438串口num的寄存器
**************************************************************************/
    div = (Fpclk >> 4) / value;
    DLM = div >> 8;
    DLL = div & 0xff;
    CH438WriteReg(ChipNum, offsetadd[num] | REG_LCR_ADDR, BIT_LCR_DLAB); /* 设置DLAB为1 */
    CH438WriteReg(ChipNum, offsetadd[num] | REG_DLL_ADDR, DLL);          /* 设置波特率 */
    CH438WriteReg(ChipNum, offsetadd[num] | REG_DLM_ADDR, DLM);

    CH438WriteReg(ChipNum, offsetadd[num] | REG_FCR_ADDR, BIT_FCR_RECVTG1 | BIT_FCR_RECVTG0 | BIT_FCR_FIFOEN); /* 设置FIFO模式，触发点为16字节 */

    CH438WriteReg(ChipNum, offsetadd[num] | REG_LCR_ADDR, BIT_LCR_WORDSZ1 | BIT_LCR_WORDSZ0); /* 字长8位，1位停止位、无校验 */ /* 设置DLAB为0 */

    CH438WriteReg(ChipNum, offsetadd[num] | REG_IER_ADDR, BIT_IER_IERECV); /* 使能中断 */ //| BIT_IER_IETHRE  BIT_IER_IEMODEM | BIT_IER_IELINES |

    CH438WriteReg(ChipNum, offsetadd[num] | REG_MCR_ADDR, BIT_MCR_OUT2); //| BIT_MCR_RTS     | BIT_MCR_DTR );              /* 允许中断输出,DTR,RTS为1 */

    CH438WriteReg(ChipNum, offsetadd[num] | REG_FCR_ADDR, CH438ReadReg(ChipNum, offsetadd[num] | REG_FCR_ADDR) | BIT_FCR_TFIFORST | BIT_FCR_RFIFORST); /* 清空FIFO中的数据 */
}


