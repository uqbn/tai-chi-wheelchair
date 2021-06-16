

#include "key.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "control.h"
#include "UpSteps.h"

void key_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(key_gpio | up_step, ENABLE);

    GPIO_InitStructure.GPIO_Pin = key_pin;
    GPIO_InitStructure.GPIO_Mode = key_mode;
    GPIO_InitStructure.GPIO_Speed = kye_speed;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = up_pin;
    GPIO_InitStructure.GPIO_Mode = up_mode;
    GPIO_InitStructure.GPIO_Speed = up_speed;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    EXTI_Config();
}

void EXTI_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    /*config for NVIC*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn | EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = EXTI_EN;
    EXTI_Init(&EXTI_InitStructure);
}

// 模式的转换
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        if (mode_Blurtooch_flag == 0 && mode_Manual_flag == 1)
        {
            mode_Blurtooch_flag = 1;
            mode_Manual_flag = 0;
        }
        else if (mode_Blurtooch_flag == 1 && mode_Manual_flag == 0)
        {
            mode_Blurtooch_flag = 0;
            mode_Manual_flag = 1;
        }
        //                mode_Blurtooch_flag = -mode_Blurtooch_flag;
        //                mode_Manual_flag    = -mode_Manual_flag;
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

// 一键上梯
void EXTI3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        if (mode_Manual_flag)
        {
            ClickUpLadder();
        }
    }
}
