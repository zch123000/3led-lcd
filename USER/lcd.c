#include "lcd.h"
#include "font.h"
#include "delay.h"     // 确保包含延时函数头文件
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h" 
/* FSMC地址定义（假设使用Bank1, NE4，A6接RS） */
#define LCD_BASE        ((u32)(0x6C000000 | 0x0000007E))
#define LCD_REG         (*((volatile u16 *)LCD_BASE))
#define LCD_RAM         (*((volatile u16 *)(LCD_BASE + 0x02)))

/* ILI9341指令定义 */
#define ILI9341_RESET         0x01
#define ILI9341_SLEEP_OUT     0x11
#define ILI9341_DISPLAY_ON    0x29
#define ILI9341_COLUMN_ADDR   0x2A
#define ILI9341_PAGE_ADDR     0x2B
#define ILI9341_MEM_WRITE     0x2C

/* 私有函数声明 */
static void LCD_WriteCmd(u16 cmd);
static void LCD_WriteData(u16 data);
static void LCD_SetWindow(u16 x0, u16 y0, u16 x1, u16 y1);

/******************************
 * LCD底层驱动（FSMC接口）
 ******************************/
static void LCD_WriteCmd(u16 cmd) {
    LCD_REG = cmd;
}

static void LCD_WriteData(u16 data) {
    LCD_RAM = data;
}

/* 设置显示窗口（坐标范围） */
static void LCD_SetWindow(u16 x0, u16 y0, u16 x1, u16 y1) {
    LCD_WriteCmd(ILI9341_COLUMN_ADDR);
    LCD_WriteData(x0 >> 8); LCD_WriteData(x0 & 0xFF);
    LCD_WriteData(x1 >> 8); LCD_WriteData(x1 & 0xFF);
    
    LCD_WriteCmd(ILI9341_PAGE_ADDR);
    LCD_WriteData(y0 >> 8); LCD_WriteData(y0 & 0xFF);
    LCD_WriteData(y1 >> 8); LCD_WriteData(y1 & 0xFF);
    
    LCD_WriteCmd(ILI9341_MEM_WRITE);
}

/******************************
 * LCD初始化
 ******************************/
void LCD_Init(void) {
    // 示例：ILI9341初始化序列
    LCD_WriteCmd(0xCF);  // Power control B
    LCD_WriteData(0x00);
    LCD_WriteData(0x83);
    LCD_WriteData(0x30);
    // ...（其他初始化命令）
    LCD_Clear(WHITE);  // 清屏为白色，验证是否显示
	// 在LCD_Init()中添加背光控制
#define LCD_BL_GPIO_PORT  GPIOD
#define LCD_BL_PIN       GPIO_Pin_12
GPIO_SetBits(LCD_BL_GPIO_PORT, LCD_BL_PIN);  // 开启背光
}

/******************************
 * 清屏函数
 ******************************/
void LCD_Clear(u16 color) {
    u32 i;
    LCD_SetWindow(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1);
    for (i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        LCD_WriteData(color);
    }
}

/******************************
 * 显示字符串（需实现PutChar函数）
 ******************************/
void LCD_ShowString(u16 x, u16 y, u16 color, u16 bg_color, const char *str, u8 size) {
    while (*str) {
        if (x > LCD_WIDTH - size) { 
            x = 0; 
            y += size; 
        }
        // PutChar(x, y, *str, color, bg_color, size); // 需实现字符绘制函数
        x += size / 2;
        str++;
    }
}

/******************************
 * 绘制动态波形（简化实现）
 ******************************/
void LCD_DrawWaveform(u16 x, u16 y, u16 width, u16 height, u16 *buffer, u16 len, u16 max_val, u16 color) {
    u16 i;
    for (i = 0; i < len; i++) {
        u16 val = buffer[i];
        u16 pos_y = y + height - (val * height / max_val);
        u16 pos_x = x + (i * width / len);
        
        /* 绘制点（实际项目中建议优化为画线或DMA） */
        LCD_SetWindow(pos_x, pos_y, pos_x, pos_y);
        LCD_WriteData(color);
    }
}

// 文件末尾添加空行以消除警告
