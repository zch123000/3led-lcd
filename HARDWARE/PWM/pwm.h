// ====================== pwm.h �޸� ======================
#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

// �����ඨʱ��֧��
void PWM_Init(void);
void PWM_SetDutyCycle_TIM2(uint16_t duty);
void PWM_SetDutyCycle_TIM3(uint16_t duty);
void PWM_SetDutyCycle_TIM4(uint16_t duty);
void PWM_DisableAll(void);
	
#endif
