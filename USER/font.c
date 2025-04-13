#include "font.h"

/* 8x16 ASCII字模数据（示例） */
static const uint16_t Font8x16_Data[] = {
    /* 字符 '0' (ASCII 48) */
    0x0000, 0x7E00, 0xFF00, 0xC300, 0xC300, 0xC300, 0xC300, 0xC300,
    0xC300, 0xC300, 0xC300, 0xC300, 0xFF00, 0x7E00, 0x0000, 0x0000,

    /* 字符 '1' (ASCII 49) */
    0x0000, 0x0C00, 0x1C00, 0x3C00, 0x6C00, 0x0C00, 0x0C00, 0x0C00,
    0x0C00, 0x0C00, 0x0C00, 0x0C00, 0xFF00, 0xFF00, 0x0000, 0x0000,

    /* 其他字符数据... */
    /* 注意：每个字符占用 16 个 uint16_t 元素 */
};

/* 字体定义（兼容Keil C89初始化方式） */
const FontDef Font_8x16 = { 
    8,                 // width
    16,                // height
    Font8x16_Data      // data指针
};