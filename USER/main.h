/* main.h */
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_it.h"
#include "sys.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated resources */
#define USART2_INSTANCE                   USART2
#define USART2_TX_PIN                     GPIO_PIN_2
#define USART2_TX_GPIO_PORT               GPIOA
#define USART2_RX_PIN                     GPIO_PIN_3
#define USART2_RX_GPIO_PORT               GPIOA

/* Exported macro ------------------------------------------------------------*/
#define ARRAY_SIZE(x)                     (sizeof(x) / sizeof((x)[0]))

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
TIM_OC_InitTypeDef sConfigOC = {0};
sConfigOC.OCMode = TIM_OCMODE_PWM1;      // PWM 模式 1
sConfigOC.Pulse = 0;                     // 初始占空比 0
sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);  // 通道 1 对应 PA5
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); 
extern char uart_rx_buffer[];
extern uint8_t uart_rx_index;
extern uint8_t uart_rx_finished;
extern float g_breath_period;
#define UART_RX_BUFF_SIZE 50
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */