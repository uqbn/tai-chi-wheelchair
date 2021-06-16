

#ifndef __ADC_H
#define __ADC_H

#include "sys.h"
#include "delay.h"
#include "stm32f10x_adc.h"

extern int adc1, adc2, adc3, adc4, adc5, adc6, adc7;
//extern u16 adc_data( u8 ch );
u16 Port_Ain(u8 port);

typedef enum
{
    motor_forwardandback,
    motor_leftandright,
} motor_t;

void Adc_Init(void);
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 chl, u8 times);
int get_adc(u8 dex);

void Rocker_mode(void);

#define limit_up   3400
#define limit_down 700

#endif
