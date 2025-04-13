#include "font.h"

/* 8x16 ASCII��ģ���ݣ�ʾ���� */
static const uint16_t Font8x16_Data[] = {
    /* �ַ� '0' (ASCII 48) */
    0x0000, 0x7E00, 0xFF00, 0xC300, 0xC300, 0xC300, 0xC300, 0xC300,
    0xC300, 0xC300, 0xC300, 0xC300, 0xFF00, 0x7E00, 0x0000, 0x0000,

    /* �ַ� '1' (ASCII 49) */
    0x0000, 0x0C00, 0x1C00, 0x3C00, 0x6C00, 0x0C00, 0x0C00, 0x0C00,
    0x0C00, 0x0C00, 0x0C00, 0x0C00, 0xFF00, 0xFF00, 0x0000, 0x0000,

    /* �����ַ�����... */
    /* ע�⣺ÿ���ַ�ռ�� 16 �� uint16_t Ԫ�� */
};

/* ���嶨�壨����Keil C89��ʼ����ʽ�� */
const FontDef Font_8x16 = { 
    8,                 // width
    16,                // height
    Font8x16_Data      // dataָ��
};