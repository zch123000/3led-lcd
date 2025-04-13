#include "key.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"

void KEY_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
}

u8 KEY_Scan(void) {
    static u8 key_up = 1;  // 按键松开标志

    if (key_up && (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1 ||
                   GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1 ||
                   GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 1 ||
                   GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == 1)) {
        delay_ms(10);  // 消抖
        key_up = 0;
        if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1) return KEY1_PRES;
        if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1) return KEY2_PRES;
        if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 1) return KEY3_PRES;
        if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == 1) return KEY4_PRES;
    } else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0 &&
               GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0 &&
               GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0 &&
               GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == 0) {
        key_up = 1;
    }
    return 0;
}
