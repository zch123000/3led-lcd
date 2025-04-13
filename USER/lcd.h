#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx.h"
#include "DataType.h"  // ȷ������u16/u8����

/* ��ɫ���壨RGB565��ʽ�� */
#define WHITE         0xFFFF
#define BLACK         0x0000
#define RED           0xF800
#define GREEN         0x07E0
#define BLUE          0x001F

/* LCD�ֱ��� */
#define LCD_WIDTH     240
#define LCD_HEIGHT    320

/* �������� */
void LCD_Init(void);  // ��ʼ��LCD
void LCD_Clear(u16 color);  // ����
void LCD_ShowString(u16 x, u16 y, u16 color, u16 bg_color, const char *str, u8 size);  // ��ʾ�ַ���
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u16 color, u16 bg_color, u8 size);  // ��ʾ����
void LCD_DrawWaveform(u16 x, u16 y, u16 width, u16 height, u16 *buffer, u16 len, u16 max_val, u16 color);  // ���Ʋ���

#endif
