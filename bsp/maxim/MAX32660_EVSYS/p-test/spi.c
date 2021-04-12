#include <stdio.h>
#include <time.h>

#include <rtthread.h>
#include <rtdevice.h>

int main(void)
{
  char s[100] = "hello";
  char r[100] = {0};
  
  struct rt_spi_device *spi_lcd_dev;
  
  // attach
  rt_hw_spi_device_attach("spi1", "spi10", 7);

  // find
  spi_lcd_dev = (struct rt_spi_device *)rt_device_find("spi10");

  RT_ASSERT(spi_lcd_dev != RT_NULL);
  
  // configure
  struct rt_spi_configuration cfg;
  cfg.data_width = 8;
  cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
  cfg.max_hz = 2 * 1000 * 1000;                           /* 4M */
  
  rt_spi_configure(spi_lcd_dev, &cfg);

  rt_kprintf("spi_lcd_init ok");

  rt_kprintf("%s\n", s);

  rt_spi_send(spi_lcd_dev, s, 6);
    
  rt_spi_recv(spi_lcd_dev, r, 6);

  rt_kprintf("spi send and recv");
  
  rt_kprintf("%s\n", s);
  
  while(1) {
    rt_thread_mdelay(500);
  }
}
