#ifndef _BSP_IIC_H
#define _BSP_IIC_H

#include "main.h"

//IO閺傜懓鎮滅拋鍓х枂
#define SDA_IN()                    \
    {                               \
        GPIOB->CRH &= 0XFFFFFF0F;   \
        GPIOB->CRH |= 8 << (4 * 1); \
    }
#define SDA_OUT()                   \
    {                               \
        GPIOB->CRH &= 0XFFFFFF0F;   \
        GPIOB->CRH |= 3 << (4 * 1); \
    }

//IO閹垮秳缍旈崙鑺ユ殶
#define IIC_SCL  PBout(8)  //SCL
#define IIC_SDA  PBout(9)  //SDA
#define READ_SDA PBin(9)   //鏉堟挸鍙哠DA

void IIC_Init(void);
uint8_t IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Read_Byte(unsigned char ack);
uint8_t IIC_Write(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
uint8_t IIC_Read(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);

#endif
