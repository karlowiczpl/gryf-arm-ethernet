#include <hardware/regs/clocks.h>
#include <pico/time.h>
#include <stdint.h>

#include <wizchip_conf.h>
#include <port_common.h>
#include <w5x00_spi.h>
#include <socket.h>

#include <dhcp.h>
#include <dns.h>
#include <httpServer.h>
#include <httpParser.h>

#include "gTcp.h"
#include "httpUtil.h"
#include "timer.h"
#include "cpu.h"

#include "GryfSmart_Config.h"

#include "web/index.h"
#include "web/ethernet.h"

#include "stdio.h"

static volatile uint16_t g_msec_cnt = 0;

uint8_t ethernet_buf[ETHERNET_BUF_MAX_SIZE] = {0};

#ifdef HTTP_SERVER_HANDLER
  static uint8_t g_http_send_buf[1025 * 12] = {0};
  static uint8_t g_http_recv_buf[HTTP_BUF_MAX_SIZE] = {0};
  static uint8_t g_http_socket_num_list[] = {0, 1, 2, 3};
#endif /* ifdef HTTP_SERVER_HANDLER */

#ifdef DHCP_ENABLE
  wiz_NetInfo net_info = { 
      .mac = {0, 0, 0, 0, 0, 0},
      .ip = {192, 168, 40, 33},                    
      .sn = {255, 255, 255, 0},                  
      .gw = {192, 168, 40, 1},                   
      .dns = {8, 8, 8, 8},                
      .dhcp = NETINFO_STATIC
  };
#else
  wiz_NetInfo net_info = { 
      .mac = {0, 0, 0, 0, 0, 0},
      .ip = {192, 168, 0, 33},                    
      .sn = {255, 255, 255, 0},                  
      .gw = {192, 168, 0, 1},                   
      .dns = {168, 126, 63, 1},                
      .dhcp = NETINFO_DHCP
  };
#endif /* if !DHCP_ENABLE  */

void setup_tcp()
{
  set_clock_khz();
  wizchip_spi_initialize();
  wizchip_cris_initialize();

  wizchip_reset();
  wizchip_initialize();
  wizchip_check();

  wizchip_delay_ms(2000);

  wizchip_1ms_timer_initialize(repeating_timer_callback);

  wizchip_dhcp_dns_init();

  #ifdef DHCP_HANDLER
    wizchip_ip_rental();
  #endif /* ifdef DHCP_HANDLER */

  #ifdef HTTP_SERVER_HANDLER
    httpServer_init(g_http_send_buf, g_http_recv_buf, HTTP_SOCKET_MAX_NUM, g_http_socket_num_list);
    
    reg_httpServer_webContent("index.html", index_page);
    reg_httpServer_webContent("web_configuration.html", web_configuration_page);
    reg_httpServer_webContent("set-ip", "OK");
  #endif /* ifdef HTTP_SERVER_HANDLER */
}

inline void http_server_run()
{
  #ifdef HTTP_SERVER_HANDLER
  for(uint8_t i = 0; i < HTTP_SOCKET_MAX_NUM; i++)
  {
    st_http_request test;

    httpServer_run(i);


    // uint16_t x = read_userReg_webContent(PTYPE_JSON, g_http_recv_buf, 0, 2048);
    // if(x)
    // {
    //   printf("dsajhdklsajkldjlkajsd: %d\n", x);
    // }
  }
  
  #endif /* ifdef HTTP_SERVER_HANDLER */
}

static void repeating_timer_callback()
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
static void wizchip_dhcp_dns_init()
{
  #ifdef DHCP_HANDLER
    DHCP_init(SOCKET_DHCP, ethernet_buf);

    reg_dhcp_cbfunc(wizchip_dhcp_assign, wizchip_dhcp_assign, wizchip_dhcp_conflict);
  #endif /* ifdef DHCP_HANDLER */
  #ifndef DNS_HANDLER
    DNS_init(SOCKET_DNS, ethernet_buf);
  #endif /* ifndef DNS_HANDLER */
}
inline static void wizchip_ip_rental()
{
  uint8_t retval = 0;
  uint8_t g_dhcp_get_ip_flag = 0;
  uint8_t dhcp_retry = 0;

  while(1)
  {
    retval = DHCP_run();

    switch (retval)
    {
      case DHCP_IP_LEASED:
        return;
      break;
      case DHCP_FAILED:
        g_dhcp_get_ip_flag = 0;
        dhcp_retry++;
        
        if(dhcp_retry > DHCP_RETRY_COUNT)
        {
          DHCP_stop();

          wizchip_static_init();
        }
      break;
    }
  }
}

inline static void wizchip_static_init()
{

}
inline void set_ethernet_properties(uint8_t* ip, uint8_t* gw, uint8_t* sn)
{
  for(int i = 0; i < 4; i++)
  {
    net_info.ip[i] = ip[i];
    net_info.gw[i] = gw[i];
    net_info.sn[i] = sn[i];
  }
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
char* read_tcp() 
{
  uint8_t tcp_sn = 0;
  int32_t ret;
  uint16_t size = 0;
  uint8_t destip[4];

  switch (getSn_SR(tcp_sn)) 
  {
    case SOCK_ESTABLISHED:
      if(getSn_IR(tcp_sn) & Sn_IR_CON) 
      {
        getSn_DIPR(tcp_sn, destip);
        uint16_t destport = getSn_DPORT(tcp_sn);
        setSn_IR(tcp_sn, Sn_IR_CON);
      }
      if((size = getSn_RX_RSR(tcp_sn)) > 0) 
      {
        ret = recv(tcp_sn, ethernet_buf, size); 
        if (ret <= 0)      return NULL;

        size = (uint16_t)ret;
        ethernet_buf[size] = '\0';

        return ethernet_buf;
      }
      break;
    case SOCK_CLOSE_WAIT:
      if((ret = disconnect(tcp_sn)) != SOCK_OK)     return NULL;
      break;
    case SOCK_INIT:
      if((ret = listen(tcp_sn)) != SOCK_OK)     return NULL;
      break;
    case SOCK_CLOSED:
      ret = socket(tcp_sn, Sn_MR_TCP, TCP_PORT, Sn_MR_ND);
      if(ret < 0)   return NULL;
      break;
    default:
      break;
  }

  if (tcp_sn < SOCKET_MAX_TCP) 
  {
      tcp_sn++;
  } 
  else 
  {
      tcp_sn = SOCKET_MIN_TCP;
  }

  return NULL;
}
void wizchip_dhcp_assign(void)
{
  getIPfromDHCP(net_info.ip);
  getGWfromDHCP(net_info.gw);
  getSNfromDHCP(net_info.sn);
  getDNSfromDHCP(net_info.dns);

  net_info.dhcp = NETINFO_DHCP;

  network_initialize(net_info);
}
void wizchip_dhcp_conflict(void)
{
  reset_all();
}
