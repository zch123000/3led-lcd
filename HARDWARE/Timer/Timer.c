/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "Timer.h"
#include "stm32f4xx_conf.h"
#include "lsens.h"
/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/
static  u8  s_i2msFlag  = FALSE;    //将2ms标志位的值设置为FALSE


/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
static  void  ConfigTimer2(u16 arr, u16 psc);  //配置TIM2

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称：ConfigTimer2
* 函数功能：配置TIM2 
* 输入参数：arr-自动重装值，psc-预分频器值
* 输出参数：void
* 返 回 值：void
* 创建日期：2018年01月01日
* 注    意：PCLK1（APB1总线时钟）= HCLK/4 = 45MHz（APB1 timer clock=90MHz）
*********************************************************************************************************/
static  void ConfigTimer2(u16 arr, u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//TIM_TimeBaseStructure用于存放定时器的参数
  NVIC_InitTypeDef NVIC_InitStructure;           //NVIC_InitStructure用于存放NVIC的参数

  //使能RCC相关时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //使能TIM2的时钟
  
  //配置TIM2
  TIM_TimeBaseStructure.TIM_Period        = arr;  //设置自动重装载值              
  TIM_TimeBaseStructure.TIM_Prescaler     = psc;  //设置预分频器值              
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       //设置时钟分割：tDTS = tCK_INT
  TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //设置向上计数模式
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);               //根据参数初始化定时器
 
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );                     //使能定时器的更新中断

  //配置NVIC
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;               //中断通道号
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     //设置抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;            //设置子优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               //使能中断
  NVIC_Init(&NVIC_InitStructure);                               //根据参数初始化NVIC
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2，2位抢占优先级，2位子优先级
                                                                
  TIM_Cmd(TIM2, ENABLE);                                        //使能定时器  
}

/*********************************************************************************************************
* 函数名称：TIM2_IRQHandler
* 函数功能：TIM2中断服务函数 
* 输入参数：void
* 输出参数：void
* 返 回 值：void
* 创建日期：2018年01月01日
* 注    意：每毫秒进入一次中断服务函数
*********************************************************************************************************/
void TIM2_IRQHandler(void)  
{  
  static  u16 s_iCnt2 = 0;                            //定义一个静态变量s_iCnt2作为2ms计数器

  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)   //判断定时器更新中断是否发生
  {
    TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);     //清除定时器更新中断标志
  }   
    
  s_iCnt2++;            //2ms计数器的计数值加1
                                
  if(s_iCnt2 >= 2)      //2ms计数器的计数值大于或等于2
  {                                                   
    s_iCnt2 = 0;        //重置2ms计数器的计数值为0
    s_i2msFlag = TRUE;  //将2ms标志位的值设置为TRUE 
				
  }
}


/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称：InitTimer
* 函数功能：初始化Timer模块 
* 输入参数：void
* 输出参数：void
* 返 回 值：void
* 创建日期：2018年01月01日
* 注    意：在RCC中，APB1 timer clock=90MHz，APB2 timer clock=180MHz，其中TIM2/3/4/5/6/7/12/13/14在APB1上，
*           TIM1/8/9/10/11在APB2上
*********************************************************************************************************/
void InitTimer(void)
{
  ConfigTimer2(999, 89);  //90Mhz/(89+1)=1MHz（对应1us），由0计数到999为1000*1us=1ms
}

/*********************************************************************************************************
* 函数名称：Get2msFlag
* 函数功能：获取2ms标志位的值  
* 输入参数：void
* 输出参数：void
* 返 回 值：s_i2msFlag-2ms标志位的值
* 创建日期：2018年01月01日
* 注    意：
*********************************************************************************************************/
u8  Get2msFlag(void)
{
  return(s_i2msFlag);     //返回2ms标志位的值
}

/*********************************************************************************************************
* 函数名称：Clr2msFlag
* 函数功能：清除2ms标志位  
* 输入参数：void
* 输出参数：void
* 返 回 值：void
* 创建日期：2018年01月01日
* 注    意：
*********************************************************************************************************/
void  Clr2msFlag(void)
{
  s_i2msFlag = FALSE;     //将2ms标志位的值设置为FALSE 
}
