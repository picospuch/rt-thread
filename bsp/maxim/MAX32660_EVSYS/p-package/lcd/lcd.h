#ifndef __LCD_H
#define __LCD_H		

#include "lcd_type.h"

void LCD_Fill(u16t xsta,u16t ysta,u16t xend,u16t yend,u16t color);//指定区域填充颜色
void LCD_DrawPoint(u16t x,u16t y,u16t color);//在指定位置画一个点
void LCD_DrawLine(u16t x1,u16t y1,u16t x2,u16t y2,u16t color);//在指定位置画一条线
void LCD_DrawRectangle(u16t x1, u16t y1, u16t x2, u16t y2,u16t color);//在指定位置画一个矩形
void Draw_Circle(u16t x0,u16t y0,u8t r,u16t color);//在指定位置画一个圆

void LCD_ShowChinese(u16t x,u16t y,u8t *s,u16t fc,u16t bc,u8t sizey,u8t mode);//显示汉字串
void LCD_ShowChinese12x12(u16t x,u16t y,u8t *s,u16t fc,u16t bc,u8t sizey,u8t mode);//显示单个12x12汉字
void LCD_ShowChinese16x16(u16t x,u16t y,u8t *s,u16t fc,u16t bc,u8t sizey,u8t mode);//显示单个16x16汉字
void LCD_ShowChinese24x24(u16t x,u16t y,u8t *s,u16t fc,u16t bc,u8t sizey,u8t mode);//显示单个24x24汉字
void LCD_ShowChinese32x32(u16t x,u16t y,u8t *s,u16t fc,u16t bc,u8t sizey,u8t mode);//显示单个32x32汉字

void LCD_ShowChar(u16t x,u16t y,u8t num,u16t fc,u16t bc,u8t sizey,u8t mode);//显示一个字符
void LCD_ShowString(u16t x,u16t y,const u8t *p,u16t fc,u16t bc,u8t sizey,u8t mode);//显示字符串
u32t mypow(u8t m,u8t n);//求幂
void LCD_ShowIntNum(u16t x,u16t y,u16t num,u8t len,u16t fc,u16t bc,u8t sizey);//显示整数变量
void LCD_ShowFloatNum1(u16t x,u16t y,float num,u8t len,u16t fc,u16t bc,u8t sizey);//显示两位小数变量

void LCD_ShowPicture(u16t x,u16t y,u16t length,u16t width,const u8t pic[]);//显示图片

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#endif
