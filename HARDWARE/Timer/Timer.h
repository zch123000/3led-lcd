/*********************************************************************************************************
* 模块名称：Timer.h
* 摘    要：Timer模块
* 当前版本：1.0.0
* 作    者：SZLY(COPYRIGHT 2018 - 2020 SZLY. All rights reserved.)
* 完成日期：2020年01月01日 
* 内    容：
* 注    意：                                                                  
**********************************************************************************************************
* 取代版本：
* 作    者：
* 完成日期：
* 修改内容：
* 修改文件：
*********************************************************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "DataType.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              API函数声明
*********************************************************************************************************/
void  InitTimer(void);      //初始化Timer模块

u8    Get2msFlag(void);     //获取2ms标志位的值
void  Clr2msFlag(void);     //清除2ms标志位

u8    Get1SecFlag(void);    //获取1s标志位的值
void  Clr1SecFlag(void);    //清除1s标志位


 
#endif
