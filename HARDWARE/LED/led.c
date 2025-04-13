#include "led.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
									  
////////////////////////////////////////////////////////////////////////////////// 	 

//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10设置高，灯灭

}


void LEDFlicker(u16 cnt) { // 函数名改为LEDFlicker（大写F）
  static u16 s_iCnt;    //定义静态变量s_iCnt作为计数器
  static u16 a_iCnt;
  a_iCnt = 0;
  s_iCnt++;             //计数器的计数值加1
  
  if (s_iCnt >= cnt) {     //计数器的计数值大于cnt 
    a_iCnt = 1;
    //LED状态取反，实现LED闪烁
    GPIO_WriteBit(GPIOG, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOG, GPIO_Pin_13)));    
  }
  if (a_iCnt == 1 && s_iCnt >= 2 * cnt) {     //计数器的计数值大于cnt 
    s_iCnt = 0;         //重置计数器的计数值为0
    //LED状态取反，实现LED闪烁
    GPIO_WriteBit(GPIOG, GPIO_Pin_14, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOG, GPIO_Pin_14)));    
  }
}



