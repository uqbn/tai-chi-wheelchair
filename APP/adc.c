

#include "adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "control.h"

int adc1, adc2, adc3, adc4, adc5, adc6, adc7;

float motor_movex, motor_movey;

motor_t motor;

void Adc_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div4);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    ADC_DeInit(ADC1);

    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1))
        ;
}

u16 Get_Adc(u8 ch)
{
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ch, 2, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ch, 3, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ch, 4, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ch, 5, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ch, 6, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ch, 7, ADC_SampleTime_1Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
        ;
    return ADC_GetConversionValue(ADC1);
}
u16 Get_Adc_Average(u8 ch, u8 times)
{
    u32 temp_val = 0;
    u8 t;
    for (t = 0; t < times; t++)
    {
        temp_val += Get_Adc(ch);
        //        delay_ms(5);
    }
    return temp_val / times;
}

int get_adc(u8 dex)
{
    int over;
    while (1)
    {
        switch (dex)
        {
        case 0x01:
            over = adc1;
            break;
        case 0x02:
            over = adc2;
            break;
        case 0x03:
            over = adc3;
            break;
        case 0x04:
            over = adc4;
            break;
        case 0x05:
            over = adc5;
            break;
        case 0x06:
            over = adc6;
            break;
        case 0x07:
            over = adc7;
            break;
        }
        return over;
    }
}

u16 adc_data(u8 ch)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    adc1 = Get_Adc_Average(ch, 10);
    return adc1;
}

u16 Port_Ain(u8 port)
{
    u8 chl;

    switch (port)
    {
    case 0:
        chl = ADC_Channel_1;
        break;
    case 1:
        chl = ADC_Channel_2;
        break;
    }
    return (adc_data(chl));
}

void Rocker_mode()
{
    motor_movex = Port_Ain(motor_forwardandback);  // ADC1的值
    motor_movey = Port_Ain(motor_leftandright);    // ADC2的值
    if (mode_Manual_flag)
    {
        if (motor_movex > limit_up || motor_movex < limit_down)
        {
            if (motor_movex < limit_down)
            {
                // 电机正转，轮椅前进
                Manual_mode_Flag = forward;
            }
            else if (motor_movex > limit_up)
            {
                // 电机反转，轮椅后退
                Manual_mode_Flag = back;
            }
        }
        else if (motor_movey > limit_up || motor_movey < limit_down)
        {
            if (motor_movey < limit_down)
            {
                // 电机正转，轮椅左转
                Manual_mode_Flag = left;
            }
            else if (motor_movey > limit_up)
            {
                // 电机正转，轮椅右转
                Manual_mode_Flag = right;
            }
        }
        else
        {
            // 电机停止，轮椅原地不动
            Manual_mode_Flag = stop;
        }
        Manual_movable(Manual_mode_Flag);
    }
}
