#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"

// 实际LED连接：PA5=红色(TIM2_CH1), PA6=绿色(TIM3_CH1), PB8=蓝色(TIM4_CH3)
#define LED_R PAout(5)    // 红色LED，TIM2_CH1
#define LED_G PAout(6)    // 绿色LED，TIM3_CH1
#define LED_B PBout(8)    // 蓝色LED，TIM4_CH3
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 
void LED_Init(void);       // 初始化LED（PWM控制）

void LEDFlicker(u16 cnt); // LED闪烁（状态指示）

#endif
