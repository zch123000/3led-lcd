#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"

// ʵ��LED���ӣ�PA5=��ɫ(TIM2_CH1), PA6=��ɫ(TIM3_CH1), PB8=��ɫ(TIM4_CH3)
#define LED_R PAout(5)    // ��ɫLED��TIM2_CH1
#define LED_G PAout(6)    // ��ɫLED��TIM3_CH1
#define LED_B PBout(8)    // ��ɫLED��TIM4_CH3
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 
void LED_Init(void);       // ��ʼ��LED��PWM���ƣ�

void LEDFlicker(u16 cnt); // LED��˸��״ָ̬ʾ��

#endif
