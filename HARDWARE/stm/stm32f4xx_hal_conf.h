/**
  ******************************************************************************
  * @file    stm32f4xx_hal_conf.h
  * @author  MCD Application Team
  * @version V1.2.6
  * @date    17-February-2017
  * @brief   HAL configuration file (优化版)
  ******************************************************************************
  * @attention
  * - 启用呼吸灯和LCD关键模块
  * - 修复时钟配置冲突
  * - 关闭未使用的外设以节省资源
  ******************************************************************************
  */

#ifndef __STM32F4xx_HAL_CONF_H
#define __STM32F4xx_HAL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* ########################## 模块启用配置 ############################## */
// 核心模块
#define HAL_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED

// 定时器模块（呼吸灯必需）
#define HAL_TIM_MODULE_ENABLED

// LCD相关模块
#define HAL_LTDC_MODULE_ENABLED      // 启用LTDC控制器
#define HAL_DMA2D_MODULE_ENABLED     // 启用DMA2D图形加速
#define HAL_SDRAM_MODULE_ENABLED     // 启用SDRAM支持

// 其他必要模块
#define HAL_ADC_MODULE_ENABLED       // 光敏传感器需要
#define HAL_UART_MODULE_ENABLED      // 调试输出需要

/* ########################## 时钟配置 ################################# */
// 外部晶振配置（根据开发板实际晶振修改）
#if !defined(HSE_VALUE)
  #define HSE_VALUE    (8000000U)    // 默认8MHz晶振
#endif

// 内部时钟配置
#if !defined(HSI_VALUE)
  #define HSI_VALUE    (16000000U)   // 16MHz内部RC
#endif

// 系统时钟配置（在SystemClock_Config()中实现）
#define VDD_VALUE          (3300U)   // 供电电压
#define TICK_INT_PRIORITY  (0x0FU)   // SysTick中断优先级（最低）

/* ########################## 外设参数配置 ############################# */
// SPI CRC功能关闭
#define USE_SPI_CRC         0U

// 缓存配置（提高性能）
#define PREFETCH_ENABLE              1
#define INSTRUCTION_CACHE_ENABLE     1
#define DATA_CACHE_ENABLE            1

/* ########################## 头文件包含 ############################### */
// 根据启用的模块自动包含对应头文件
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
  #include "stm32f4xx_hal_tim.h"     // PWM关键头文件
#endif

#ifdef HAL_LTDC_MODULE_ENABLED
  #include "stm32f4xx_hal_ltdc.h"    // LCD控制器
#endif

#ifdef HAL_DMA2D_MODULE_ENABLED
  #include "stm32f4xx_hal_dma2d.h"   // 图形加速
#endif

#ifdef HAL_ADC_MODULE_ENABLED
  #include "stm32f4xx_hal_adc.h"     // 光敏传感器
#endif

/* ########################## 调试配置 ################################# */
// 关闭所有调试冻结宏（防止定时器被锁定）
#undef __HAL_DBGMCU_FREEZE_TIM2
#undef __HAL_DBGMCU_FREEZE_TIM3
#undef __HAL_DBGMCU_FREEZE_TIM4

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_CONF_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/