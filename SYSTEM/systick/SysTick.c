#include "SysTick.h"
#include "stm32f4xx.h"
#include "sys.h"
static volatile  uint32_t TM_Time = 0;  // ����ʱ������  // ϵͳ�δ��������1ms������

/*-----------------------------------------------------------
  Function: InitSysTick
  Description: ��ʼ��SysTick��ʱ��������Ϊ1ms�ж�
  Input: ��
  Output: ��
-----------------------------------------------------------*/
void InitSysTick(void) {
    // ϵͳʱ��Ƶ�ʼ�飨����HCLK=180MHz��
    if (SysTick_Config(SystemCoreClock / 1000)) { 
        // ���������SysTick����ʧ�ܣ�������ѭ��
        while (1);
    }
    
    // ����SysTick�ж����ȼ������ڰ����жϣ�
    NVIC_SetPriority(SysTick_IRQn, 0x0F);  // ���ȼ�15����ͣ�
}

/*-----------------------------------------------------------
  Function: SysTick_GetTime
  Description: ��ȡ��ǰϵͳʱ�䣨��λ��ms��
  Input: ��
  Output: ��ǰʱ�����uint32_t��
-----------------------------------------------------------*/
uint32_t SysTick_GetTime(void) {
    return TM_Time;  // ֱ�ӷ��ؼ�����ֵ
}

/*-----------------------------------------------------------
  Function: SysTick_Handler
  Description: SysTick�жϷ��������Զ�������
  Input: ��
  Output: ��
  Note: �����������������ļ�һ�£�STM32��׼������
-----------------------------------------------------------*/
void SysTick_Handler(void) {
    static uint32_t tick = 0;
    if (++tick >= 1000) {  // ÿ1ms����һ��
        TM_Time++;
        tick = 0;
    }
}

/*-----------------------------------------------------------
  Function: DelayNms
  Description: ����ʽ��ȷ��ʱ����λ��ms��
  Input: nms - ��ʱ������
  Output: ��
-----------------------------------------------------------*/
void DelayNms(uint32_t nms) {
    uint32_t start_time = SysTick_GetTime();
    while ((SysTick_GetTime() - start_time) < nms);
}


void SysTick_Init(void) {
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while(1);
    }
}
