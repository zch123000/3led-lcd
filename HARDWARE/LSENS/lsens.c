#include "lsens.h"
#include "delay.h"
#include "adc3.h"
#include <stdio.h>
#include <math.h>

#define ADC_FULL_SCALE 4000   
#define SAMPLING_INTERVAL_MS 1  // 3��������
static u32 last_output_time = 0;  // �ϴ����ʱ�䣨���룩
static u32 adc_accumulate = 0;    // ADCֵ�ۼ���
static u16 sampling_count = 0;    // ��������������

// ��ʼ��������������PF7��ADC3ͨ��5��ģ������ģʽ��
void Lsens_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    
    // ����Ϊģ�����루ADC����ģʽ����ֹ��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;       
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;    
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    
    Adc3_Init();  // ��ʼ��ADC3
}

// ��ȡ����������ֵ�������ɼ������������߼���ת��
u8 Lsens_Get_Val(void) {
    u16 adc_value;           // ���������ڿ鿪ͷ��C89Ҫ��
    u32 current_time;        
    static u8 last_result = 0;  // ��̬���������ϴ���Чֵ
    
    adc_value = Get_Adc3(ADC_Channel_5);  // �����ɼ�ADCֵ
    adc_accumulate += adc_value;
    sampling_count++;
    
    current_time = SystemCoreClock / 1000;
    
    // �ﵽ���ʱ����ƽ��ֵ�������ϴ���Чֵ���ؼ�����ת�߼���
    if (current_time - last_output_time >= SAMPLING_INTERVAL_MS && sampling_count > 0) {
        float avg = (float)adc_accumulate / sampling_count;
        // ��ת�߼���ADCֵԽС������Խǿ�����ٷֱ�Խ��0-100%��
        last_result = (u8)((1.0f - avg / ADC_FULL_SCALE) * 100 + 0.5f);  
        
        printf("ADC AVG: %d%% (RAW AVG: %d)\r\n", 100-last_result, (u32)avg);
        adc_accumulate = 0;
        sampling_count = 0;
        last_output_time = current_time;
    }
    
    return last_result;  // ����������Чֵ���ϴ�ֵ���������£�
}
