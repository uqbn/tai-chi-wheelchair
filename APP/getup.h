#ifndef __GETUP_H
#define __GETUP_H
#include "sys.h"
#include "pwm.h"
#define ENA  PBout(7)  //鐢垫満浣胯兘淇″彿
#define DIR1 PBout(6)  //鐢垫満1鏂瑰悜淇″彿

#define rise    1
#define decline 2

void HelpGetUp_Up(void);
void HelpGetUp_Down(void);
void HelpGetUp_Init(void);
void HelpGetUp_Move(int i);
#endif
