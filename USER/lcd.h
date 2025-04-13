#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx.h"
#include "DataType.h"  // 确保包含u16/u8定义

/* 颜色定义（RGB565格式） */
#define WHITE         0xFFFF
#define BLACK         0x0000
#define RED           0xF800
#define GREEN         0x07E0
#define BLUE          0x001F

/* LCD分辨率 */
#define LCD_WIDTH     240
#define LCD_HEIGHT    320

/* 函数声明 */
void LCD_Init(void);  // 初始化LCD
void LCD_Clear(u16 color);  // 清屏
void LCD_ShowString(u16 x, u16 y, u16 color, u16 bg_color, const char *str, u8 size);  // 显示字符串
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u16 color, u16 bg_color, u8 size);  // 显示数字
void LCD_DrawWaveform(u16 x, u16 y, u16 width, u16 height, u16 *buffer, u16 len, u16 max_val, u16 color);  // 绘制波形

#endif
