
#include "control.h"

#include "UpSteps.h"
#include "MoveWheelchair.h"

#include "usart.h"

uint8_t Bluetooch_mode_Flag;  // 蓝牙模式下电机的运动标志
uint8_t Manual_mode_Flag;     // 手动模式下电机的运动标志

motor_mode_t motor_mode;

bool control_mode;

int mode_Blurtooch_flag = none;  // 蓝牙模式  0--不使用蓝牙模式，1--使用蓝牙模式
int mode_Manual_flag = do;       // 手动模式  0--不使用手动模式，1--使用手动模式

/*
*            函 数 名：Bluetooch_movable
*            入口参数：Flag
*            功    能：蓝牙模式下的控制
    */
void Bluetooch_movable(uint8_t Flag)
{
    switch (Flag)
    {
    case stop:
        Wheelchair_Move(stop);
        break;  // motor_move = stop
    case forward:
        Wheelchair_Move(forward);
        break;  // motor_move = forward
    case back:
        Wheelchair_Move(back);
        break;  // motor_move = back
    case left:
        Wheelchair_Move(left);
        break;  // motor_move = left
    case right:
        Wheelchair_Move(right);
        break;  // motor_move = right
    case one_button:
        ClickUpLadder();
        break;  // motor_move = one_button
    }
}

/*
*            函 数 名：Manual_movable
*            入口参数：Flag
*            功    能：手动模式下的控制
    */
void Manual_movable(uint8_t Flag)
{
    switch (Flag)
    {
    case stop:
        Wheelchair_Move(stop);
        break;  // motor_move = stop
    case forward:
        Wheelchair_Move(forward);
        break;  // motor_move = forward
    case back:
        Wheelchair_Move(back);
        break;  // motor_move = back
    case left:
        Wheelchair_Move(left);
        break;  // motor_move = left
    case right:
        Wheelchair_Move(right);
        break;  // motor_move = right
    case one_button:
        ClickUpLadder();
        break;  // motor_move = one_button
    }
}

#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

float pitch, roll, yaw;
int16_t gyro[3];

void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        mpu_dmp_get_data(&pitch, &roll, &yaw);
        MPU_Get_Gyro(gyro);
    }
    EXTI_ClearITPendingBit(EXTI_Line12);
    Angle_Control(pitch, roll);
}

void Angle_Control(float pitch, float roll)
{
    static int Check_out = 0;
    float Pitch, Roll;
    Pitch = pitch - Final_Value_Pitch;
    Roll = roll - Final_Value_Roll;
    // 取绝对值
    if (Pitch < zero || Roll < zero)
    {
        if (Pitch < zero)
        {
            Pitch = -Pitch;
        }
        if (Roll < zero)
        {
            Roll = -Roll;
        }
    }
    if (Pitch <= Angle_Limit && Roll <= Angle_Limit)
    {
        Check_out = Check_out_Send;
    }
    // 判断是否为摔倒，若是，则停止一切电机，并给手机发消息，若不是，则不会进入
    if ((Pitch > Angle_Limit || Roll > Angle_Limit) && Check_out == 1)
    {
        Wheelchair_Move(stop);
        USART_SendData(USART1, Send_data);
        Check_out = Check_out_Rec;
        //USART1_IRQHandler();
    }
}
