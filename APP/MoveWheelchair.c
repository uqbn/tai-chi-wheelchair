#include "MoveWheelchair.h"
/**************************************
 * 文件名  ：MoveWheelchair.c
 * 描述    ：帮助轮椅跨台阶         
*********************************************************/
void Wheelchair_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能PB端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能PB端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_12);
}
//取绝对值
int myabs(int a)
{
    int temp;
    if (a < 0)
        temp = -a;
    else
        temp = a;
    return temp;
}
//pwm波
void Set_Pwm(int moto1, int moto2)
{
    //    if(moto1 || moto2 ==0){
    //        Move_Stop =0;
    //    }else
    //    {
    if (moto1 > 0)
    {
        Move_AIN3 = 1;
        Move_AIN2 = 0;
    }
    else
    {
        Move_AIN3 = 0;
        Move_AIN2 = 1;
    }
    PWMA = myabs(moto1);

    if (moto2 > 0)
    {
        Move_BIN3 = 0;
        Move_BIN2 = 1;
    }
    else
    {
        Move_BIN3 = 1;
        Move_BIN2 = 0;
    }
    PWMB = myabs(moto2);
    //    }
}
void Wheelchair_Brake(int i)
{
    switch (i)
    {
    case (1):
        Move_Stop = 0;
        break;
    case (2):
        Move_Stop = 1;
        break;
    }
}
//轮椅整体的运动方向
void Wheelchair_Move(uint8_t i)
{
    switch (i)
    {
    case (0):
        Set_Pwm(0, 0);
        break;  // 电机停止
    case (1):
        Set_Pwm(400, 400);
        break;  // 电机正转
    case (2):
        Set_Pwm(-400, -400);
        break;  // 电机反转
    case (3):
        Set_Pwm(300, 400);
        break;  // 左转
    case (4):
        Set_Pwm(400, 300);
        break;  // 右转
    }
}
void Wheelchair_BMove(int i)
{
    switch (i)
    {
    case (1):
        Move_BIN3 = 1;
        Move_BIN2 = 0;
        break;  //电机正转
    case (2):
        Move_BIN3 = 0;
        Move_BIN2 = 1;
        break;  //电机反转
    case (3):
        Move_BIN3 = 1;
        Move_BIN2 = 1;
        break;  //电机停止运动
    }
}
//void Wheelchair_Move2(int i)
//{
//    switch(i){
//        case(1):Move_IN4=1;Move_IN5=0;TIM_SetCompare1(TIM2,300);break ;//电机正转
//        case(2):Move_IN4=0;Move_IN5=1;TIM_SetCompare1(TIM2,300);break ;//电机反转
//        case(3):Move_IN4=1;Move_IN5=1;break;//电机停止运动
//    }
//}
////电机正转
//void Wheelchair_Forward()
//{
//    Move_IN3=1;
//    Move_IN2=0;
//    TIM_SetCompare1(TIM1,299);
//}
////电机反转
//void Wheelchair_Reversal()
//{
//    Move_IN3=0;
//    Move_IN2=1;
//    //TIM_SetCompare1(TIM1,299);
//}
