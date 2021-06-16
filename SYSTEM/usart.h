

#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "sys.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "receivedata.h"

#define USART_REC_LEN 200  //定义最大接收字节数 200
#define EN_USART1_RX  1    //使能（1）/禁止（0）串口1接收

extern u8 USART_RX_BUF[USART_REC_LEN];  //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART_RX_STA;                //接收状态标记
//如果想串口中断接收，请不要注释以下宏定义

void uart_init1(u32 bound);
void uart_init3(u32 bound);

void gpio_init(void);

void USART3_IRQHandler(void);
void USART1_IRQHandler(void);

#endif
