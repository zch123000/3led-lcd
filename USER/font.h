#ifndef __FONT_H
#define __FONT_H

#include <stdint.h>  // ȷ��������׼��������

/* ����ṹ�嶨�� */
typedef struct {
    uint8_t width;     // �ַ���ȣ����أ�
    uint8_t height;    // �ַ��߶ȣ����أ�
    const uint16_t *data;  // ��ģ����ָ�루16λ��ʽ��
} FontDef;

/* ����ȫ��������� */
extern const FontDef Font_8x16;  // ע�����Ʊ����ϸ�һ��

#endif
