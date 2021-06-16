#ifndef __UPSTEPS_H
#define __UPSTEPS_H
#include "sys.h"
#include "MoveWheelchair.h"
#define IN3 PBout(0)
#define IN4 PBout(1)

#define halt 1
#define down 2
#define up   3

#define Up_up 13  // 小轮下降的时间

void delay_s(u16 time);
void UpStep_Motor(int i);
void UpStep_Init(void);
void ClickUpLadder(void);
#endif
