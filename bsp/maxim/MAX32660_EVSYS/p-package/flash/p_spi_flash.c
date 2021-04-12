#include "p_spi_flash.h"

#include <rtthread.h>
#include <rtdebug.h>
#include <rtdevice.h>
#include <rthw.h>

#include "drv_spi.h"

//#include "spi_flash.h"
//#include "spi_flash_sfud.h"

#include "board.h"

void p_spi_flash_init(void) {
  // attach
  rt_hw_spi_device_attach("spi0", "spi00", -1);

  rt_kprintf("flash spi bus initialized.\n");
  
  RT_ASSERT(RT_NULL != rt_sfud_flash_probe("W25Q128", "spi10"));
  
  rt_kprintf("flash initialized.\n");
}
