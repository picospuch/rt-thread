#include "lcd_init.h"

#include <rtthread.h>
#include <rtdebug.h>
#include <rtdevice.h>
#include <rthw.h>

#include "board.h"
#include "mxc_delay.h"

#include "drv_spi.h"

static struct rt_spi_device *spi_lcd_dev;

void delay_ms(unsigned int ms)
{
  mxc_delay(ms * 1000);
}

int lcd_spi_init(void) {
  // attach
  rt_hw_spi_device_attach("spi0", "spi00", 7);

  // find
  spi_lcd_dev = (struct rt_spi_device *)rt_device_find("spi00");

  RT_ASSERT(spi_lcd_dev != RT_NULL);
  
  // configure
  struct rt_spi_configuration cfg;
  cfg.data_width = 8;
  cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
  cfg.max_hz = 2 * 1000 * 1000;                           /* 4M */
  
  rt_spi_configure(spi_lcd_dev, &cfg);

  rt_kprintf("spi_lcd_init ok");
  
  return RT_EOK;
}

void LCD_GPIO_Init(void) {
  rt_pin_mode(DC, PIN_MODE_OUTPUT);
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8t dat) 
{	
  rt_spi_send(spi_lcd_dev, &dat, 1);
}

void LCD_WR_N_DATA(void *dat, int len) {
  rt_spi_send(spi_lcd_dev, dat, len);
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8t dat)
{
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16t dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8t dat)
{
	LCD_DC_Clr();//写命令
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16t x1,u16t y1,u16t x2,u16t y2)
{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
}


/******************************************************************************
      函数说明：LCD初始化函数
      入口数据：无
      返回值：  无
******************************************************************************/
void LCD_Init(void)
{
  LCD_GPIO_Init();
  lcd_spi_init();
  
	LCD_RES_Clr();
	delay_ms(100);
	LCD_RES_Set();
	delay_ms(100);
	LCD_BLK_Set();
	delay_ms(100);
	
	LCD_WR_REG(0xEF);
	LCD_WR_REG(0xEB);
	LCD_WR_DATA8(0x14); 
	
  LCD_WR_REG(0xFE);			 
	LCD_WR_REG(0xEF); 

	LCD_WR_REG(0xEB);	
	LCD_WR_DATA8(0x14); 

	LCD_WR_REG(0x84);			
	LCD_WR_DATA8(0x40); 

	LCD_WR_REG(0x85);			
	LCD_WR_DATA8(0xFF); 

	LCD_WR_REG(0x86);			
	LCD_WR_DATA8(0xFF); 

	LCD_WR_REG(0x87);			
	LCD_WR_DATA8(0xFF);

	LCD_WR_REG(0x88);			
	LCD_WR_DATA8(0x0A);

	LCD_WR_REG(0x89);			
	LCD_WR_DATA8(0x21); 

	LCD_WR_REG(0x8A);			
	LCD_WR_DATA8(0x00); 

	LCD_WR_REG(0x8B);			
	LCD_WR_DATA8(0x80); 

	LCD_WR_REG(0x8C);			
	LCD_WR_DATA8(0x01); 

	LCD_WR_REG(0x8D);			
	LCD_WR_DATA8(0x01); 

	LCD_WR_REG(0x8E);			
	LCD_WR_DATA8(0xFF); 

	LCD_WR_REG(0x8F);			
	LCD_WR_DATA8(0xFF); 


	LCD_WR_REG(0xB6);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x20);

	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC8);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x68);
	else LCD_WR_DATA8(0xA8);

	LCD_WR_REG(0x3A);			
	LCD_WR_DATA8(0x05); 


	LCD_WR_REG(0x90);			
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08); 

	LCD_WR_REG(0xBD);			
	LCD_WR_DATA8(0x06);
	
	LCD_WR_REG(0xBC);			
	LCD_WR_DATA8(0x00);	

	LCD_WR_REG(0xFF);			
	LCD_WR_DATA8(0x60);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x04);

	LCD_WR_REG(0xC3);			
	LCD_WR_DATA8(0x13);
	LCD_WR_REG(0xC4);			
	LCD_WR_DATA8(0x13);

	LCD_WR_REG(0xC9);			
	LCD_WR_DATA8(0x22);

	LCD_WR_REG(0xBE);			
	LCD_WR_DATA8(0x11); 

	LCD_WR_REG(0xE1);			
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x0E);

	LCD_WR_REG(0xDF);			
	LCD_WR_DATA8(0x21);
	LCD_WR_DATA8(0x0c);
	LCD_WR_DATA8(0x02);

	LCD_WR_REG(0xF0);   
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x26);
 	LCD_WR_DATA8(0x2A);

 	LCD_WR_REG(0xF1);    
 	LCD_WR_DATA8(0x43);
 	LCD_WR_DATA8(0x70);
 	LCD_WR_DATA8(0x72);
 	LCD_WR_DATA8(0x36);
 	LCD_WR_DATA8(0x37);  
 	LCD_WR_DATA8(0x6F);


 	LCD_WR_REG(0xF2);   
 	LCD_WR_DATA8(0x45);
 	LCD_WR_DATA8(0x09);
 	LCD_WR_DATA8(0x08);
 	LCD_WR_DATA8(0x08);
 	LCD_WR_DATA8(0x26);
 	LCD_WR_DATA8(0x2A);

 	LCD_WR_REG(0xF3);   
 	LCD_WR_DATA8(0x43);
 	LCD_WR_DATA8(0x70);
 	LCD_WR_DATA8(0x72);
 	LCD_WR_DATA8(0x36);
 	LCD_WR_DATA8(0x37); 
 	LCD_WR_DATA8(0x6F);

	LCD_WR_REG(0xED);	
	LCD_WR_DATA8(0x1B); 
	LCD_WR_DATA8(0x0B); 

	LCD_WR_REG(0xAE);			
	LCD_WR_DATA8(0x77);
	
	LCD_WR_REG(0xCD);			
	LCD_WR_DATA8(0x63);		


	LCD_WR_REG(0x70);			
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x0F); 
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x03);

	LCD_WR_REG(0xE8);			
	LCD_WR_DATA8(0x34);

	LCD_WR_REG(0x62);			
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xED);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xEF);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);

	LCD_WR_REG(0x63);			
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xF3);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);

	LCD_WR_REG(0x64);			
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x29);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x07);

	LCD_WR_REG(0x66);			
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xCD);
	LCD_WR_DATA8(0x67);
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);

	LCD_WR_REG(0x67);			
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x32);
	LCD_WR_DATA8(0x98);

	LCD_WR_REG(0x74);			
	LCD_WR_DATA8(0x10);	
	LCD_WR_DATA8(0x85);	
	LCD_WR_DATA8(0x80);
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x4E);
	LCD_WR_DATA8(0x00);					
	
  LCD_WR_REG(0x98);			
	LCD_WR_DATA8(0x3e);
	LCD_WR_DATA8(0x07);

	LCD_WR_REG(0x35);	
	LCD_WR_REG(0x21);

	LCD_WR_REG(0x11);
	delay_ms(120);
	LCD_WR_REG(0x29);
	delay_ms(20);
} 
