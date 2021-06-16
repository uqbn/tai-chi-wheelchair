#ifndef _pwm_H
#define _pwm_H

#include "sys.h"

void TIM3_CH2_PWM_Init(u16 per, u16 psc);
void TIM2_CH1_PWM_Init(u16 per, u16 psc);

#endif
