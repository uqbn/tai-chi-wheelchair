
#include "usart.h"
#include "control.h"

//串口设置
void uart_init1(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);  //使能USART1，GPIOA时钟

    //USART1_TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  //PA9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);           //初始化GPIOB.10

    //USART1_RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //初始化GPIOB.11

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                            //根据指定的参数初始化VIC寄存器

    //USART 初始化设置

    USART_InitStructure.USART_BaudRate = bound;                                      //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                              //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                  //收发模式

    USART_Init(USART1, &USART_InitStructure);       //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //开启串口接受中断
    USART_Cmd(USART1, ENABLE);                      //使能串口1
}

// 串口接收
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        USART_SendData(USART1, Send_data);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

// 蓝牙串口端口配置
void uart_init3(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_APB2Periph_GPIOB, ENABLE);  //使能USART1，GPIOA时钟
                                                                                   //    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
                                                                                   //
                                                                                   //    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
                                                                                   //    // 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）
                                                                                   //    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
                                                                                   //    // 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能

    //USART3_TX   GPIOB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);           //初始化GPIOB.10

    //USART3_RX      GPIOB.11初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;             //PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);                 //初始化GPIOB.11

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                            //根据指定的参数初始化VIC寄存器

    //USART 初始化设置

    USART_InitStructure.USART_BaudRate = bound;                                      //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                              //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                  //收发模式

    USART_Init(USART3, &USART_InitStructure);       //初始化串口3
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  //开启串口接受中断
    USART_Cmd(USART3, ENABLE);                      //使能串口3
}

// 蓝牙接收
void USART3_IRQHandler(void)
{
    uint8_t Rec_Data;
    uint8_t bluetooth_Data;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        Rec_Data = USART_ReceiveData(USART3);
        bluetooth_Data = Rec_Data;
        if (mode_Blurtooch_flag)
        {
            if (bluetooth_Data == 'S')
            {
                // 前进
                Bluetooch_mode_Flag = stop;
            }
            else if (bluetooth_Data == 'F')
            {
                // 前进
                Bluetooch_mode_Flag = forward;
            }
            else if (bluetooth_Data == 'B')
            {
                // 后退
                Bluetooch_mode_Flag = back;
            }
            else if (bluetooth_Data == 'L')
            {
                // 左转
                Bluetooch_mode_Flag = left;
            }
            else if (bluetooth_Data == 'R')
            {
                // 右转
                Bluetooch_mode_Flag = right;
            }
            else if (bluetooth_Data == 'X')
            {
                // 一键上梯
                Bluetooch_mode_Flag = one_button;
            }
            //            USART_SendData(USART3,Rec_Data);

            Bluetooch_movable(Bluetooch_mode_Flag);
        }
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}

//#define led_rcc   RCC_APB2Periph_GPIOC

//#define led_rcc   RCC_APB2Periph_GPIOA

//#define led_gpio  GPIOC

//#define led_pin1  GPIO_Pin_13
//#define led_pin2  GPIO_Pin_1
//#define led_pin3  GPIO_Pin_2
//#define led_pin4  GPIO_Pin_3

//#define led_mode  GPIO_Mode_Out_PP

//#define led_speed GPIO_Speed_50MHz
//void gpio_init()
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//
//    RCC_APB2PeriphClockCmd( led_rcc, ENABLE);
//
//    GPIO_InitStructure.GPIO_Pin = led_pin1 | led_pin2 | led_pin3 | led_pin4;
//    GPIO_InitStructure.GPIO_Mode = led_mode;
//    GPIO_InitStructure.GPIO_Speed = led_speed;
//
//    GPIO_Init( led_gpio, &GPIO_InitStructure);
//
//
//}
