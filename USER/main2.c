#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc3.h"
#include "lsens.h"

// �޸ĺ�����
int main2(void)
{ 
  u8 adcx;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//��ʼ��LCD
	Lsens_Init(); 			//��ʼ������������
 
    
    while(1)
    {
        adcx = Lsens_Get_Val();
        printf("ADC����ֵ��: %d \r\n", adcx);
        LED0 =!LED0;
    
        delay_ms(1000);	
    }
}
