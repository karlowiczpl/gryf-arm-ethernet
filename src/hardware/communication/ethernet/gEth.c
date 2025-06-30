#include <stdint.h>
#include <stdbool.h>

#include <timer.h>
#include <wizchip_conf.h>
#include <port_common.h>
#include <w5x00_spi.h>
#include <socket.h>

#include "hardware/timer.h"

#include "gEth.h"
#include "gDhcp.h"
#include "gUtp.h"

#include "GryfSmart_Config.h"

static volatile uint16_t g_msec_cnt = 0;

uint8_t ethernet_buf[ETHERNET_BUF_MAX_SIZE] = {0};

void setup_ethernet()
{
  set_clock_khz();
  wizchip_spi_initialize();
  wizchip_cris_initialize();

  wizchip_reset();
  wizchip_initialize();
  wizchip_check();

  wizchip_delay_ms(2000);

  wizchip_1ms_timer_initialize(repeating_timer_callback);

  setup_ip();
  setup_udp(); 
}

void set_clock_khz() 
{
  set_sys_clock_khz(PLL_SYS_KHZ, true);

  clock_configure(
    clk_peri,
    0,                                                
    CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
    PLL_SYS_KHZ * 1000,
    PLL_SYS_KHZ * 1000
  );
}

void repeating_timer_callback()
{
  g_msec_cnt++; 

  if(g_msec_cnt >= 1000 - 1)
  {
    g_msec_cnt = 0;

    #ifdef DHCP_HANDLER
      DHCP_time_handler();
    #endif /* ifdef DHCP */
    #ifdef DNS_HANDLER
      DNS_time_handler();
    #endif /* ifdef DNS_HANDLER */
  }
}
