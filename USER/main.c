

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "adc.h"

#include "MoveWheelchair.h"
#include "UpSteps.h"
#include "getup.h"

#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

#include "bsp_iic.h"
#include "bsp_exti.h"

//// 时间函数 输入参数 time  单位秒（s）
//void delay_s(u16 time)
//{
//   u16 i=0;
//     time = time * 1000;
//   while(time--)
//   {
//      i=8000;  //自己定义
//      while(i--) ;
//   }
//}

int main(void)
{
    key_init();
    Adc_Init();
    uart_init3(9600);
    uart_init1(9600);

    SysTick_Init(72);
    UpStep_Init();
    HelpGetUp_Init();
    Wheelchair_Init();
    TIM2_CH1_PWM_Init(500, 72 - 1);
    TIM3_CH2_PWM_Init(500, 72 - 1);  //频率是2Kh

    MPU_Init();
    mpu_dmp_init();
    mpu_exti_init();

    while (1)
    {
        //            printf("%d",DATA);
        //            delay_ms(50);
        //            Rocker_mode();

        //// 调试时间函数 delay_s  输入参数 time   单位秒（s）
        //        gpio_init();
        //        GPIO_SetBits( GPIOC, GPIO_Pin_13);
        //        delay_s(10);
        //        GPIO_ResetBits( GPIOC, GPIO_Pin_13);
        //        delay_s(10);
    }
}
