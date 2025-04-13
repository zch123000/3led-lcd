#include "lsens.h"
#include "delay.h"
#include "adc3.h"
#include <stdio.h>
#include <math.h>

#define ADC_FULL_SCALE 4000   
#define SAMPLING_INTERVAL_MS 1  // 3秒采样间隔
static u32 last_output_time = 0;  // 上次输出时间（毫秒）
static u32 adc_accumulate = 0;    // ADC值累加器
static u16 sampling_count = 0;    // 采样次数计数器

// 初始化光敏传感器（PF7，ADC3通道5，模拟输入模式）
void Lsens_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    
    // 配置为模拟输入（ADC必需模式，禁止上下拉）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;       
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;    
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    
    Adc3_Init();  // 初始化ADC3
}

// 获取光敏传感器值（持续采集，间隔输出，逻辑反转）
u8 Lsens_Get_Val(void) {
    u16 adc_value;           // 变量声明在块开头（C89要求）
    u32 current_time;        
    static u8 last_result = 0;  // 静态变量保存上次有效值
    
    adc_value = Get_Adc3(ADC_Channel_5);  // 持续采集ADC值
    adc_accumulate += adc_value;
    sampling_count++;
    
    current_time = SystemCoreClock / 1000;
    
    // 达到间隔时计算平均值并更新上次有效值（关键：反转逻辑）
    if (current_time - last_output_time >= SAMPLING_INTERVAL_MS && sampling_count > 0) {
        float avg = (float)adc_accumulate / sampling_count;
        // 反转逻辑：ADC值越小（光线越强），百分比越大（0-100%）
        last_result = (u8)((1.0f - avg / ADC_FULL_SCALE) * 100 + 0.5f);  
        
        printf("ADC AVG: %d%% (RAW AVG: %d)\r\n", 100-last_result, (u32)avg);
        adc_accumulate = 0;
        sampling_count = 0;
        last_output_time = current_time;
    }
    
    return last_result;  // 返回最新有效值或上次值（持续更新）
}
