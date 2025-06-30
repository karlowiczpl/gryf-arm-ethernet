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

// #ifdef HTTP_SERVER_HANDLER
//   static uint8_t g_http_send_buf[1025 * 12] = {0};
//   static uint8_t g_http_recv_buf[HTTP_BUF_MAX_SIZE] = {0};
//   static uint8_t g_http_socket_num_list[] = {0, 1, 2, 3};
// #endif /* ifdef HTTP_SERVER_HANDLER */

//   #ifdef HTTP_SERVER_HANDLER
//     httpServer_init(g_http_send_buf, g_http_recv_buf, HTTP_SOCKET_MAX_NUM, g_http_socket_num_list);
//     
//     reg_httpServer_webContent("index.html", index_page);
//     reg_httpServer_webContent("web_configuration.html", web_configuration_page);
//     reg_httpServer_webContent("set-ip", "OK");
//   #endif /* ifdef HTTP_SERVER_HANDLER */
// }

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

// char* read_tcp() 
// {
//   uint8_t tcp_sn = 0;
//   int32_t ret;
//   uint16_t size = 0;
//   uint8_t destip[4];
//
//   switch (getSn_SR(tcp_sn)) 
//   {
//     case SOCK_ESTABLISHED:
//       if(getSn_IR(tcp_sn) & Sn_IR_CON) 
//       {
//         getSn_DIPR(tcp_sn, destip);
//         uint16_t destport = getSn_DPORT(tcp_sn);
//         setSn_IR(tcp_sn, Sn_IR_CON);
//       }
//       if((size = getSn_RX_RSR(tcp_sn)) > 0) 
//       {
//         ret = recv(tcp_sn, ethernet_buf, size); 
//         if (ret <= 0)      return NULL;
//
//         size = (uint16_t)ret;
//         ethernet_buf[size] = '\0';
//
//         return ethernet_buf;
//       }
//       break;
//     case SOCK_CLOSE_WAIT:
//       if((ret = disconnect(tcp_sn)) != SOCK_OK)     return NULL;
//       break;
//     case SOCK_INIT:
//       if((ret = listen(tcp_sn)) != SOCK_OK)     return NULL;
//       break;
//     case SOCK_CLOSED:
//       ret = socket(tcp_sn, Sn_MR_TCP, TCP_PORT, Sn_MR_ND);
//       if(ret < 0)   return NULL;
//       break;
//     default:
//       break;
//   }
//
//   if (tcp_sn < SOCKET_MAX_TCP) 
//   {
//       tcp_sn++;
//   } 
//   else 
//   {
//       tcp_sn = SOCKET_MIN_TCP;
//   }
//
//   return NULL;
// }
