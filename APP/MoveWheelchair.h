#ifndef __MOVEWHEELCHAIR_H
#define __MOVEWHEELCHAIR_H

#include "sys.h"
#include "pwm.h"
#define Move_AIN3 PBout(12)  //反转
#define Move_AIN2 PBout(13)  //正转
#define Move_BIN3 PBout(14)  //反转
#define Move_BIN2 PBout(15)  //正转
#define Move_Stop PAout(12)  //正转

#define PWMB TIM1->CCR4  //PA11
#define PWMA TIM1->CCR1  //PA8
void Set_Pwm(int moto1, int moto2);
void Wheelchair_Init(void);
//轮椅整体运动反向
void Wheelchair_Move(uint8_t i);
//单个电机的运动
void Wheelchair_BMove(int i);

#endif
