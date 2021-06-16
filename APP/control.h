#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"

void Bluetooch_movable(uint8_t Flag);
void Manual_movable(uint8_t Flag);
void Angle_Control(float pitch, float roll);

typedef enum
{
    stop,
    forward,
    back,
    left,
    right,
    one_button,  // 一键上梯
} motor_mode_t;  // 电机移动功能列表

typedef enum
{
    manual,
    bluetooth,
} bool;

extern uint8_t Bluetooch_mode_Flag;  // 蓝牙模式下电机的运动标志
extern uint8_t Manual_mode_Flag;     // 手动模式下电机的运动标志

extern motor_mode_t motor_mode;
extern int mode_Blurtooch_flag;  // 蓝牙模式状态标志位，0--不是蓝牙模式，1--是蓝牙模式
extern int mode_Manual_flag;     // 手动模式状态标志位，0--不是手动模式，1--是手动模式

#define do 1
#define none 0

#define Send_data 'S'  // 发送的数据

#define zero        0  // 绝对值
#define Angle_Limit 60  // 角度上限

#define Final_Value_Pitch 1.2  // 俯仰角的终值
#define Final_Value_Roll  2.3  // 航向角的终值

#define Check_out_Send 1
#define Check_out_Rec  0

#endif
