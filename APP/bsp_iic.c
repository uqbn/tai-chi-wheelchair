#include "bsp_iic.h"
#include "delay.h"

#define BSP_IIC  1
#define SOFT_IIC 2

#define IIC_MODE SOFT_IIC

#if IIC_MODE == SOFT_IIC

void IIC_DELAY(uint8_t nus)
{
    delay_us(nus);
}
/**************************实现函数********************************************
*函数原型:        void IIC_Init(void)
*功　　能:        初始化I2C对应的接口引脚。
*******************************************************************************/
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能PB端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;  //端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;        //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //50M
    GPIO_Init(GPIOB, &GPIO_InitStructure);                  //根据设定参数初始化GPIOB
}
/**************************实现函数********************************************
*函数原型:        void IIC_Start(void)
*功　　能:        产生IIC起始信号
*******************************************************************************/
uint8_t IIC_Start(void)
{
    SDA_OUT();  //sda线输出
    IIC_SDA = 1;
    if (!READ_SDA)
        return 0;
    IIC_SCL = 1;
    IIC_DELAY(4);
    IIC_SDA = 0;  //START:when CLK is high,DATA change form high to low
    if (READ_SDA)
        return 0;
    IIC_DELAY(4);
    IIC_SCL = 0;  //钳住I2C总线，准备发送或接收数据
    return 1;
}
/**************************实现函数********************************************
*函数原型:        void IIC_Stop(void)
*功　　能:        //产生IIC停止信号
*******************************************************************************/
void IIC_Stop(void)
{
    SDA_OUT();  //sda线输出
    IIC_SCL = 0;
    IIC_SDA = 0;  //STOP:when CLK is high DATA change form low to high
    IIC_DELAY(4);
    IIC_SCL = 1;
    IIC_SDA = 1;  //发送I2C总线结束信号
    IIC_DELAY(4);
}

/**************************实现函数********************************************
*函数原型:        uint8_t IIC_Wait_Ack(void)
*功　　能:        等待应答信号到来 
//返回值：1，接收应答失败
//        0，接收应答成功
*******************************************************************************/
uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN();  //SDA设置为输入
    IIC_SDA = 1;
    IIC_DELAY(4);
    IIC_SCL = 1;
    IIC_DELAY(4);
    while (READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 50)
        {
            IIC_Stop();
            return 0;
        }
        IIC_DELAY(4);
    }
    IIC_SCL = 0;  //时钟输出0
    return 1;
}

/**************************实现函数********************************************
*函数原型:        void IIC_Ack(void)
*功　　能:        产生ACK应答
*******************************************************************************/
void IIC_Ack(void)
{
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 0;
    IIC_DELAY(4);
    IIC_SCL = 1;
    IIC_DELAY(4);
    IIC_SCL = 0;
}

/**************************实现函数********************************************
*函数原型:        void IIC_NAck(void)
*功　　能:        产生NACK应答
*******************************************************************************/
void IIC_NAck(void)
{
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 1;
    IIC_DELAY(4);
    IIC_SCL = 1;
    IIC_DELAY(4);
    IIC_SCL = 0;
}
/**************************实现函数********************************************
*函数原型:        void IIC_Send_Byte(uint8_t txd)
*功　　能:        IIC发送一个字节
*******************************************************************************/
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL = 0;  //拉低时钟开始数据传输
    for (t = 0; t < 8; t++)
    {
        IIC_SDA = (txd & 0x80) >> 7;
        txd <<= 1;
        IIC_DELAY(4);
        IIC_SCL = 1;
        IIC_DELAY(4);
        IIC_SCL = 0;
        IIC_DELAY(1);
    }
}

/**************************实现函数********************************************
*函数原型:        uint8_t IIC_Read_Byte(unsigned char ack)
*功　　能:        //读1个字节，ack=1时，发送ACK，ack=0，发送nACK 
*******************************************************************************/
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    SDA_IN();  //SDA设置为输入
    for (i = 0; i < 8; i++)
    {
        IIC_SCL = 0;
        IIC_DELAY(4);
        IIC_SCL = 1;
        receive <<= 1;
        if (READ_SDA)
            receive++;
        IIC_DELAY(4);
    }
    if (ack)
        IIC_Ack();  //发送ACK
    else
        IIC_NAck();  //发送nACK
    return receive;
}
/**************************实现函数********************************************
*函数原型:        uint8_t i2cWrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
*功　　能:        
*******************************************************************************/
uint8_t IIC_Write(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
    int16_t i;
    if (!IIC_Start())
        return 1;
    IIC_Send_Byte((addr << 1) | 0);
    if (!IIC_Wait_Ack())
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    for (i = 0; i < len; i++)
    {
        IIC_Send_Byte(data[i]);
        if (!IIC_Wait_Ack())
        {
            IIC_Stop();
            return 0;
        }
    }
    IIC_Stop();
    return 0;
}
/**************************实现函数********************************************
*函数原型:        uint8_t i2cRead(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
*功　　能:        
*******************************************************************************/
uint8_t IIC_Read(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    if (!IIC_Start())
        return 1;
    IIC_Send_Byte((addr << 1) | 0);
    if (!IIC_Wait_Ack())
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte((addr << 1) | 1);
    IIC_Wait_Ack();
    while (len)
    {
        if (len == 1)
            *buf = IIC_Read_Byte(0);
        else
            *buf = IIC_Read_Byte(1);
        buf++;
        len--;
    }
    IIC_Stop();
    return 0;
}
#endif
