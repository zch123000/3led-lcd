#ifndef __ADC3_H
#define __ADC3_H	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 

//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
 							   
void Adc3_Init(void); 				//ADC通道初始化
u16  Get_Adc3(u8 ch); 				//获得某个通道值 
u16 Get_Adc_Average(u8 ch,u8 times);//得到某个通道给定次数采样的平均值  
#endif 















