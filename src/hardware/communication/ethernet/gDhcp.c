#include "gDhcp.h"

#include "GryfSmart_Config.h"

#include "wizchip_conf.h"
#include <port_common.h>
#include <w5x00_spi.h>
#include <socket.h>

#ifdef DHCP_ENABLE
  wiz_NetInfo net_info = {
    .mac = {0, 0, 0, 0, 0, 0},
    .ip = {192, 168, 0, 95},
    .sn = {255, 255, 255, 0},
    .gw = {192, 168, 0, 1},
    .dns = {0, 0, 0, 0},
    .dhcp = NETINFO_DHCP,
  };
#else
  wiz_NetInfo net_info = {
    .mac = {0, 0, 0, 0, 0, 0},
    .ip = {192, 168, 0, 95},
    .sn = {255, 255, 255, 0},
    .gw = {192, 168, 0, 1},
    .dns = {0, 0, 0, 0},
    .dhcp = NETINFO_STATIC,
  };
#endif /* ifdef DHCP_HANDLER */

void setup_dhcp()
{
}

void set_clock_khz(void) 
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

