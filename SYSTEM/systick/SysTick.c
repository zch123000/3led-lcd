#include "SysTick.h"
#include "stm32f4xx.h"
#include "sys.h"
static volatile  uint32_t TM_Time = 0;  // 定义时基变量  // 系统滴答计数器（1ms递增）

/*-----------------------------------------------------------
  Function: InitSysTick
  Description: 初始化SysTick定时器，配置为1ms中断
  Input: 无
  Output: 无
-----------------------------------------------------------*/
void InitSysTick(void) {
    // 系统时钟频率检查（假设HCLK=180MHz）
    if (SysTick_Config(SystemCoreClock / 1000)) { 
        // 错误处理：如果SysTick配置失败，进入死循环
        while (1);
    }
    
    // 设置SysTick中断优先级（低于按键中断）
    NVIC_SetPriority(SysTick_IRQn, 0x0F);  // 优先级15（最低）
}

/*-----------------------------------------------------------
  Function: SysTick_GetTime
  Description: 获取当前系统时间（单位：ms）
  Input: 无
  Output: 当前时间戳（uint32_t）
-----------------------------------------------------------*/
uint32_t SysTick_GetTime(void) {
    return TM_Time;  // 直接返回计数器值
}

/*-----------------------------------------------------------
  Function: SysTick_Handler
  Description: SysTick中断服务函数（自动触发）
  Input: 无
  Output: 无
  Note: 函数名必须与启动文件一致（STM32标准命名）
-----------------------------------------------------------*/
void SysTick_Handler(void) {
    static uint32_t tick = 0;
    if (++tick >= 1000) {  // 每1ms触发一次
        TM_Time++;
        tick = 0;
    }
}

/*-----------------------------------------------------------
  Function: DelayNms
  Description: 阻塞式精确延时（单位：ms）
  Input: nms - 延时毫秒数
  Output: 无
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
