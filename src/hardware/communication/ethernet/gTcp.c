#include <hardware/regs/clocks.h>
#include <pico/time.h>
#include <stdint.h>

#include <wizchip_conf.h>
#include <port_common.h>
#include <w5x00_spi.h>
#include <socket.h>

#include "gTcp.h"
#include "timer.h"
#include "cpu.h"

#include "GryfSmart_Config.h"

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
