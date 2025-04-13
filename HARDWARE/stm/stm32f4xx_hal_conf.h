/**
  ******************************************************************************
  * @file    stm32f4xx_hal_conf.h
  * @author  MCD Application Team
  * @version V1.2.6
  * @date    17-February-2017
  * @brief   HAL configuration file (�Ż���)
  ******************************************************************************
  * @attention
  * - ���ú����ƺ�LCD�ؼ�ģ��
  * - �޸�ʱ�����ó�ͻ
  * - �ر�δʹ�õ������Խ�ʡ��Դ
  ******************************************************************************
  */

#ifndef __STM32F4xx_HAL_CONF_H
#define __STM32F4xx_HAL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* ########################## ģ���������� ############################## */
// ����ģ��
#define HAL_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED

// ��ʱ��ģ�飨�����Ʊ��裩
#define HAL_TIM_MODULE_ENABLED

// LCD���ģ��
#define HAL_LTDC_MODULE_ENABLED      // ����LTDC������
#define HAL_DMA2D_MODULE_ENABLED     // ����DMA2Dͼ�μ���
#define HAL_SDRAM_MODULE_ENABLED     // ����SDRAM֧��

// ������Ҫģ��
#define HAL_ADC_MODULE_ENABLED       // ������������Ҫ
#define HAL_UART_MODULE_ENABLED      // ���������Ҫ

/* ########################## ʱ������ ################################# */
// �ⲿ�������ã����ݿ�����ʵ�ʾ����޸ģ�
#if !defined(HSE_VALUE)
  #define HSE_VALUE    (8000000U)    // Ĭ��8MHz����
#endif

// �ڲ�ʱ������
#if !defined(HSI_VALUE)
  #define HSI_VALUE    (16000000U)   // 16MHz�ڲ�RC
#endif

// ϵͳʱ�����ã���SystemClock_Config()��ʵ�֣�
#define VDD_VALUE          (3300U)   // �����ѹ
#define TICK_INT_PRIORITY  (0x0FU)   // SysTick�ж����ȼ�����ͣ�

/* ########################## ����������� ############################# */
// SPI CRC���ܹر�
#define USE_SPI_CRC         0U

// �������ã�������ܣ�
#define PREFETCH_ENABLE              1
#define INSTRUCTION_CACHE_ENABLE     1
#define DATA_CACHE_ENABLE            1

/* ########################## ͷ�ļ����� ############################### */
// �������õ�ģ���Զ�������Ӧͷ�ļ�
#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32f4xx_hal_rcc.h"
#endif

#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32f4xx_hal_gpio.h"
#endif

#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32f4xx_hal_dma.h"
#endif

#ifdef HAL_TIM_MODULE_ENABLED
  #include "stm32f4xx_hal_tim.h"     // PWM�ؼ�ͷ�ļ�
#endif

#ifdef HAL_LTDC_MODULE_ENABLED
  #include "stm32f4xx_hal_ltdc.h"    // LCD������
#endif

#ifdef HAL_DMA2D_MODULE_ENABLED
  #include "stm32f4xx_hal_dma2d.h"   // ͼ�μ���
#endif

#ifdef HAL_ADC_MODULE_ENABLED
  #include "stm32f4xx_hal_adc.h"     // ����������
#endif

/* ########################## �������� ################################# */
// �ر����е��Զ���꣨��ֹ��ʱ����������
#undef __HAL_DBGMCU_FREEZE_TIM2
#undef __HAL_DBGMCU_FREEZE_TIM3
#undef __HAL_DBGMCU_FREEZE_TIM4

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_CONF_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/