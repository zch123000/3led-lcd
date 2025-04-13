#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"

#define KEY1_PRES 1
#define KEY2_PRES 2
#define KEY3_PRES 3
#define KEY4_PRES 4

#define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define KEY3 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define KEY4 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)

void KEY_Init(void);
u8 KEY_Scan(void);

#endif
