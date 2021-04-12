#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#include "board.h"

#include "lcd_type.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#define LCD_W 240
#define LCD_H 240

#define DC 8

//-----------------LCD端口定义----------------

#define LCD_RES_Clr()
#define LCD_RES_Set()

#define LCD_DC_Clr() rt_pin_write(DC, PIN_LOW)
#define LCD_DC_Set() rt_pin_write(DC, PIN_HIGH)

#define LCD_BLK_Clr()
#define LCD_BLK_Set()



void delay_ms(unsigned int ms);//不准确延时函数
void LCD_GPIO_Init(void);
int lcd_spi_init(void);

void LCD_Writ_Bus(u8t dat);//模拟SPI时序
void LCD_WR_DATA8(u8t dat);//写入一个字节
void LCD_WR_DATA(u16t dat);//写入两个字节

void LCD_WR_N_DATA(void *dat, int len);

void LCD_WR_REG(u8t dat);//写入一个指令
void LCD_Address_Set(u16t x1,u16t y1,u16t x2,u16t y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif
