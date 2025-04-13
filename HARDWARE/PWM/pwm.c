#include "pwm.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

// 定时器初始化：TIM2/TIM3/TIM4 用于LED PWM控制
void PWM_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    TIM_OCInitTypeDef TIM_OCStruct;

    // 1. 使能定时器和GPIO时钟
    RCC_APB1PeriphClockCmd(
        RCC_APB1Periph_TIM2 | 
        RCC_APB1Periph_TIM3 | 
        RCC_APB1Periph_TIM4, 
        ENABLE
    );
    RCC_AHB1PeriphClockCmd(
        RCC_AHB1Periph_GPIOA | 
        RCC_AHB1Periph_GPIOB, 
        ENABLE
    );

    // 2. 配置LED对应GPIO为复用功能
    // PA5 (LED_R, TIM2_CH1)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);  // PA5 映射到 TIM2_CH1

    // PA6 (LED_G, TIM3_CH1)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);  // PA6 映射到 TIM3_CH1

    // PB8 (LED_B, TIM4_CH3)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);  // PB8 映射到 TIM4_CH3

    // 3. 配置定时器时基（100Hz，10ms周期）
    TIM_BaseStruct.TIM_Prescaler = 84 - 1;       // 预分频器：84MHz/84=1MHz（假设系统时钟84MHz，根据实际系统调整）
    TIM_BaseStruct.TIM_Period = 10000 - 1;       // 自动重装值：1MHz/10000=100Hz
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_BaseStruct);
    TIM_TimeBaseInit(TIM3, &TIM_BaseStruct);
    TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);

    // 4. 配置PWM通道（模式1，高电平有效）
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCStruct.TIM_Pulse = 0;  // 初始占空比0%

    // TIM2_CH1 (PA5)
    TIM_OC1Init(TIM2, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // TIM3_CH1 (PA6)
    TIM_OC1Init(TIM3, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // TIM4_CH3 (PB8)
    TIM_OC3Init(TIM4, &TIM_OCStruct);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    // 5. 启动定时器
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

    // 6. 初始关闭所有LED（占空比0%）
    PWM_DisableAll();
}

// 设置TIM2占空比（LED_R, TIM2_CH1）
void PWM_SetDutyCycle_TIM2(uint16_t duty) {
    if (duty > 10000) duty = 10000;
    TIM_SetCompare1(TIM2, duty);
}

// 设置TIM3占空比（LED_G, TIM3_CH1）
void PWM_SetDutyCycle_TIM3(uint16_t duty) {
    if (duty > 10000) duty = 10000;
    TIM_SetCompare1(TIM3, duty);
}

// 设置TIM4占空比（LED_B, TIM4_CH3）
void PWM_SetDutyCycle_TIM4(uint16_t duty) {
    if (duty > 10000) duty = 10000;
    TIM_SetCompare3(TIM4, duty);  // CH3对应Compare3寄存器
}

// 关闭所有PWM输出（占空比0%）
void PWM_DisableAll(void) {
    TIM_SetCompare1(TIM2, 0);
    TIM_SetCompare1(TIM3, 0);
    TIM_SetCompare3(TIM4, 0);
}
