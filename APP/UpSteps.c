

#include "UpSteps.h"
/**************************************
 * 文件名  ：UpSteps.c
 * 描述    ：帮助轮椅跨台阶         
*********************************************************/

//管脚初始化
void UpStep_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能PB端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_0);
}
//电机的正反转
void UpStep_Motor(int i)
{
    switch (i)
    {
    case (halt):
        IN3 = 0;
        IN4 = 0;
        break;  //
    case (down):
        IN3 = 1;
        IN4 = 0;
        break;  //此时轮子开始回收，轮椅失去支撑
    case (up):
        IN3 = 0;
        IN4 = 1;
        break;  //此时轮子开始放下去，轮椅得到支撑
    }
}
//一键上梯
void ClickUpLadder()
{
    UpStep_Motor(up);  //此时轮子开始放下去，轮椅得到支撑
    delay_s(Up_up);
    UpStep_Motor(halt);  //停止电机运动
    Set_Pwm(400, 400);

    delay_s(3);  //目前设置停止时间为2s
    Set_Pwm(0, 0);

    UpStep_Motor(down);  //此时轮子开始回收，轮椅失去支撑
    delay_s(5);

    Set_Pwm(400, 400);
    delay_s(5);
}
void delay_s(u16 time)
{
    u16 i = 0;
    time = time * 1000;
    while (time--)
    {
        i = 8000;
        while (i--)
            ;
    }
}
