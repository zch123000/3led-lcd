#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc3.h"
#include "lsens.h"

// 修改函数名
int main2(void)
{ 
  u8 adcx;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED 
 	LCD_Init();					//初始化LCD
	Lsens_Init(); 			//初始化光敏传感器
 
    
    while(1)
    {
        adcx = Lsens_Get_Val();
        printf("ADC的数值是: %d \r\n", adcx);
        LED0 =!LED0;
    
        delay_ms(1000);	
    }
}
