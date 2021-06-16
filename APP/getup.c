#include "getup.h"
/**************************************
 * 文件名  ：getup.c
 * 描述    ：辅助起身                                                                                                      
*********************************************************/
//管脚初始化
void HelpGetUp_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能PB端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_7);

    // GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    // GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOB, &GPIO_InitStructure);
    // GPIO_SetBits(GPIOB,GPIO_Pin_8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_6);
}
void HelpGetUp_Move(int i)
{
    switch (i)
    {
    case (rise):
        ENA = 0;
        DIR1 = 0;
        TIM_SetCompare2(TIM3, 299);
        break;  //电机正转
    case (decline):
        ENA = 1;
        DIR1 = 0;
        TIM_SetCompare2(TIM3, 299);
        break;  //电机反转
    }
}
//辅助起身，支架开始上升
void HelpGetUp_Up(void)
{
    ENA = 0;
    DIR1 = 0;
    TIM_SetCompare1(TIM3, 299);
}
//起身完毕，支架开始下降
void HelpGetUp_Down(void)
{
    ENA = 1;
    DIR1 = 0;
    TIM_SetCompare2(TIM3, 299);
}
