#ifndef __FONT_H
#define __FONT_H

#include <stdint.h>  // 确保包含标准整数类型

/* 字体结构体定义 */
typedef struct {
    uint8_t width;     // 字符宽度（像素）
    uint8_t height;    // 字符高度（像素）
    const uint16_t *data;  // 字模数据指针（16位格式）
} FontDef;

/* 声明全局字体变量 */
extern const FontDef Font_8x16;  // 注意名称必须严格一致

#endif
