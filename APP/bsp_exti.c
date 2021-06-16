

#include "bsp_exti.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"

void mpu_exti_init()
{
    //打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    //引脚初始化
    {
        GPIO_InitTypeDef GPIO_InitStruct;

        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;

        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    //中断线初始化
    {
        EXTI_InitTypeDef EXTI_InitStructure;

        EXTI_InitStructure.EXTI_Line = EXTI_Line12;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;

        EXTI_Init(&EXTI_InitStructure);
        //初始化中断线
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);
    }
    //NVIC初始化
    {
        NVIC_InitTypeDef NVIC_InitStructure;

        NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;       //使能外部中断通道
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //抢占优先级2，
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //子优先级0
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能外部中断通道

        NVIC_Init(&NVIC_InitStructure);
    }
}
