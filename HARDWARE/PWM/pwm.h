// ====================== pwm.h 修改 ======================
#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

// 新增多定时器支持
void PWM_Init(void);
void PWM_SetDutyCycle_TIM2(uint16_t duty);
void PWM_SetDutyCycle_TIM3(uint16_t duty);
void PWM_SetDutyCycle_TIM4(uint16_t duty);
void PWM_DisableAll(void);
	
#endif
