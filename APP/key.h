#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

void key_init(void);
void EXTI_Config(void);

#define key_gpio RCC_APB2Periph_GPIOA

#define key_pin   GPIO_Pin_0
#define key_mode  GPIO_Mode_IPU
#define kye_speed GPIO_Speed_50MHz

#define up_step RCC_APB2Periph_GPIOB

#define up_pin   GPIO_Pin_3
#define up_mode  GPIO_Mode_IPU
#define up_speed GPIO_Speed_50MHz

#define EXTI_EN ENABLE
//#define EXTI_Line  EXTI_Line0

#endif
