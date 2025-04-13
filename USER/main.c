#include "led.h"
#include "SysTick.h"
#include "RCC.h"
#include "Timer.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "key.h"
#include "tm_stm32f4_ili9341.h"
#include <math.h>
#include "sys.h"
#include "lsens.h"
#include "adc3.h"

#define SENSOR_PIN GPIO_Pin_7
#define SENSOR_GPIO_PORT GPIOF
#define SENSOR_RCC RCC_AHB1Periph_GPIOF
#define DUTY_CHANGE_TRIGGER 5  // 占空比变化5次触发

/* 呼吸模式 */
typedef enum {
    MODE_ALL = 0,   
    MODE_1_2,       
    MODE_1_3,       
    MODE_2_3        
} BreathMode;

/* 波形参数 */
#define WAVE_WIDTH     100
#define WAVE_HEIGHT    80
#define WAVE_X         20
#define WAVE_Y         120
#define DISPLAY_CYCLES 2
#define TOTAL_WIDTH    (WAVE_WIDTH * DISPLAY_CYCLES)
#define ERASE_WIDTH    2

static uint16_t prev_wave_y[TOTAL_WIDTH];
static BreathMode g_current_mode = MODE_ALL;
static uint16_t g_pwm_val = 0;
static uint16_t last_pwm_val = 0;  // 记录上一次占空比值
static uint8_t g_dir = 1;
static float g_breath_period = 8.0f;
__IO uint32_t TM_Time = 0;
static uint8_t duty_change_count = 0;  // 占空比变化计数器

const char* mode_str[] = {"MODE: ALL", "MODE: 1+2", "MODE: 1+3", "MODE: 2+3"};

// 自定义画点函数
void Custom_DrawPixel(int x, int y, uint16_t color) {
    TM_ILI9341_DrawPixel(x, y, color);
}

// 擦除上一次波形
void ErasePrevWave() {
    int i, w, y;
    for (i = 0; i < TOTAL_WIDTH; i++) {
        if (i != WAVE_WIDTH - 1) {
            Custom_DrawPixel(WAVE_X + i, prev_wave_y[i], ILI9341_COLOR_BLACK);
        }
    }
    for (i = 0; i < TOTAL_WIDTH - 1; i++) {
        if (prev_wave_y[i] != prev_wave_y[i + 1] && (i + 1) % WAVE_WIDTH != 0) {
            int start_y = (prev_wave_y[i] < prev_wave_y[i + 1]) ? prev_wave_y[i] : prev_wave_y[i + 1];
            int end_y = (prev_wave_y[i] > prev_wave_y[i + 1]) ? prev_wave_y[i] : prev_wave_y[i + 1];
            for (w = -ERASE_WIDTH; w <= ERASE_WIDTH; w++) {
                if (i + w >= 0 && i + w < TOTAL_WIDTH) {
                    for (y = start_y; y <= end_y; y++) {
                        Custom_DrawPixel(WAVE_X + i + w, y, ILI9341_COLOR_BLACK);
                    }
                }
            }
        }
    }
}

// 硬件初始化
void InitHardware(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    int i;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init(168);
    uart_init(115200);
    InitSysTick();
    InitRCC();
    InitTimer();
    LED_Init();
    PWM_Init();
    KEY_Init();
    
    // 传感器GPIO配置（模拟输入模式）
    RCC_AHB1PeriphClockCmd(SENSOR_RCC, ENABLE);
    GPIO_InitStruct.GPIO_Pin = SENSOR_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;       
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;    
    GPIO_Init(SENSOR_GPIO_PORT, &GPIO_InitStruct);
    
    Lsens_Init();  
    
    // LCD背光控制
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    GPIO_SetBits(GPIOD, GPIO_Pin_12);  // 打开背光
    
    TM_ILI9341_Init();
    TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_1);
    TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
    
    for (i = 0; i < TOTAL_WIDTH; i++) {
        prev_wave_y[i] = 0;
    }
}

// 更新呼吸灯占空比
static void UpdateBreathing(void) {
    static uint32_t tick_count = 0;
    const uint32_t total_ticks = g_breath_period * 1000 / 100;
    const uint16_t step = 100;
    
    last_pwm_val = g_pwm_val;  // 保存旧值
    
    if (g_dir) {
        if (g_pwm_val + step <= 5000) {
            g_pwm_val += step;
        } else {
            g_pwm_val = 5000;
            g_dir = 0;
        }
    } else {
        if (g_pwm_val >= step) {
            g_pwm_val -= step;
        } else {
            g_pwm_val = 0;
            g_dir = 1;
        }
    }
    tick_count++;
    if (tick_count >= total_ticks) {
        tick_count = 0;
    }
    
    // 检测占空比变化并计数
    if (g_pwm_val != last_pwm_val && duty_change_count < DUTY_CHANGE_TRIGGER) {
        duty_change_count++;
    }
    
    // 设置PWM占空比
    switch (g_current_mode) {
        case MODE_ALL:
            PWM_SetDutyCycle_TIM2(g_pwm_val);
            PWM_SetDutyCycle_TIM3(g_pwm_val);
            PWM_SetDutyCycle_TIM4(g_pwm_val);
            break;
        case MODE_1_2:
            PWM_SetDutyCycle_TIM2(g_pwm_val);
            PWM_SetDutyCycle_TIM3(g_pwm_val);
            PWM_SetDutyCycle_TIM4(0);
            break;
        case MODE_1_3:
            PWM_SetDutyCycle_TIM2(g_pwm_val);
            PWM_SetDutyCycle_TIM3(0);
            PWM_SetDutyCycle_TIM4(g_pwm_val);
            break;
        case MODE_2_3:
            PWM_SetDutyCycle_TIM2(0);
            PWM_SetDutyCycle_TIM3(g_pwm_val);
            PWM_SetDutyCycle_TIM4(g_pwm_val);
            break;
    }
}

// 处理模式切换
static void HandleModeSwitch(u8 key_val) {
    switch (key_val) {
        case KEY1_PRES: g_current_mode = MODE_1_2; break;
        case KEY2_PRES: g_current_mode = MODE_1_3; break;
        case KEY3_PRES: g_current_mode = MODE_2_3; break;
        case KEY4_PRES: g_current_mode = MODE_ALL; break;
    }
    g_pwm_val = 0;
    g_dir = 1;
    duty_change_count = 0;  // 重置计数器
    PWM_DisableAll();
}

// LCD显示更新
static void UpdateLCDDisplay(u8 adcx) {
    char str_buf[500];
    int i, cycle;
    float duty_ratio;
    int high_width;
    int high_y, low_y, joint_x;
    
    duty_ratio = (float)g_pwm_val / 5000.0f;
    high_width = (int)(WAVE_WIDTH * duty_ratio);
    high_y = WAVE_Y + WAVE_HEIGHT / 3;
    low_y = WAVE_Y + 2 * WAVE_HEIGHT / 3;
    joint_x = WAVE_X + WAVE_WIDTH - 1;
    
    // 显示占空比（实时更新）
    snprintf(str_buf, sizeof(str_buf), "Duty: %3d%%", g_pwm_val / 50);
    TM_ILI9341_Puts(10, 20, str_buf, &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    
    // 显示周期（实时更新）
    snprintf(str_buf, sizeof(str_buf), "Period: %.1fs", g_breath_period);
    TM_ILI9341_Puts(10, 40, str_buf, &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    
    // 显示模式（实时更新）
    TM_ILI9341_Puts(10, 60, (char*)mode_str[g_current_mode], &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    
    // 显示ADC值（持续更新）
	
    snprintf(str_buf, sizeof(str_buf), "ADC: %3d%%",adcx);
    TM_ILI9341_Puts(10, 80, str_buf, &TM_Font_7x10, ILI9341_COLOR_BLUE, ILI9341_COLOR_BLACK);
   
	 
	 // 波形绘制（实时更新）
    ErasePrevWave();
    for (cycle = 0; cycle < DISPLAY_CYCLES; cycle++) {
        int offset = cycle * WAVE_WIDTH;
        for (i = 0; i < high_width; i++) {
            prev_wave_y[offset + i] = high_y;
            Custom_DrawPixel(WAVE_X + offset + i, high_y, ILI9341_COLOR_YELLOW);
        }
        if (high_width > 0 && high_width < WAVE_WIDTH) {
            for (i = high_y; i <= low_y; i++) {
                Custom_DrawPixel(WAVE_X + offset + high_width, i, ILI9341_COLOR_YELLOW);
            }
        }
        for (i = high_width; i < WAVE_WIDTH; i++) {
            prev_wave_y[offset + i] = low_y;
            Custom_DrawPixel(WAVE_X + offset + i, low_y, ILI9341_COLOR_YELLOW);
        }
    }
    for (i = high_y; i <= low_y; i++) {
        Custom_DrawPixel(joint_x, i, ILI9341_COLOR_YELLOW);
    }
    TM_ILI9341_DrawRectangle(WAVE_X - 1, WAVE_Y - 1, WAVE_X + TOTAL_WIDTH, WAVE_Y + WAVE_HEIGHT, ILI9341_COLOR_WHITE);
}

int main(void) {
    u8 key;

    InitHardware();

    while (1) {
        key = KEY_Scan();
        if (key) {
            HandleModeSwitch(key);
            delay_ms(10);  // 按键去抖
        }

        UpdateBreathing();
        UpdateLCDDisplay(100-Lsens_Get_Val());  // 直接传递实时采集值
        
        delay_ms(4);  // 系统延时，维持实时响应
    }
}
