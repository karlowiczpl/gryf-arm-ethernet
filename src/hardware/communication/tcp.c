#include <stdint.h>

#include <wizchip_conf.h>
#include <port_common.h>
#include <w5x00_spi.h>
#include <socket.h>

#include "tcp.h"

inline void set_clock_khz(void);

int port = DEFAULT_PORT;
uint8_t sn = 0;
int32_t ret;
uint16_t size = 0;
uint8_t destip[4];
uint16_t destport;

uint8_t ethernet_buf[ETHERNET_BUF_MAX_SIZE] = {0};
wiz_NetInfo net_info = { 
    .mac = {0, 0, 0, 0, 0, 0},
    .ip = {192, 168, 40, 33},                    
    .sn = {255, 255, 255, 0},                  
    .gw = {192, 168, 40, 1},                   
    .dns = {168, 126, 63, 1},                
    .dhcp = NETINFO_STATIC
};
inline void setup_tcp()
{
  set_clock_khz();
  wizchip_spi_initialize();
  wizchip_cris_initialize();
  wizchip_reset();
  wizchip_initialize();
  wizchip_check();

  network_initialize(net_info);
}
inline void set_ip_addr(uint8_t* ip)
{
  for(int i = 0; i < 4; i++)
  {
    net_info.ip[i] = ip[i];
    net_info.gw[i] = ip[i];
  }
  net_info.gw[3] = 1;
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
void set_tcp_port(int p)
{
  port = p;
}
void set_sn(uint8_t s)
{
  sn = s;
}
char* read_tcp() 
{
  switch (getSn_SR(sn)) 
  {
    case SOCK_ESTABLISHED:
      if (getSn_IR(sn) & Sn_IR_CON) {
        getSn_DIPR(sn, destip);
        destport = getSn_DPORT(sn);
        setSn_IR(sn, Sn_IR_CON);
      }
      if ((size = getSn_RX_RSR(sn)) > 0) {
        ret = recv(sn, ethernet_buf, size); 
        if (ret <= 0)      return NULL;

        size = (uint16_t)ret;
        ethernet_buf[size] = '\0';

        return ethernet_buf;
      }
      break;
    case SOCK_CLOSE_WAIT:
      if ((ret = disconnect(sn)) != SOCK_OK)
        return NULL;
      break;
    case SOCK_INIT:
      if ((ret = listen(sn)) != SOCK_OK)
        return NULL;
      break;
    case SOCK_CLOSED:
      if ((ret = socket(sn, Sn_MR_TCP, port, Sn_MR_ND)) != sn)
        return NULL;
      break;
    default:
      break;
  }

  if (sn < 8) 
  {
      sn++;
  } 
  else 
  {
      sn = 0;
  }

  return NULL;
}

