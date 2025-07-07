#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include <wizchip_conf.h>
#include <port_common.h>
#include <w5x00_spi.h>
#include <socket.h>
#include <loopback.h>
#include <w5500.h>

#include "gUtp.h"
#include "ethernet_config.h"
#include "gEth.h"

uint8_t broadcast_ip[4];
uint8_t broadcast_ip_seted = 0;

void setup_udp()
{
  #ifdef UDP_BROADCAST_HANDLER
    socket(SOCKET_UDP, Sn_MR_UDP, UDP_PORT, 0);
  #endif /* ifdef UDP_BROADCAST_HANDLER */
}

void send_to_udp(uint8_t* msg)
{
  size_t len = strlen((char*)msg);
  if(len < 2) return;

  if(!broadcast_ip_seted) 
  {
    calculate_broadcast_ip(net_info.ip, net_info.sn, broadcast_ip);
  }

  sendto(SOCKET_UDP, msg, len, broadcast_ip, UDP_PORT);
}

uint8_t* read_broadcast_udp()
{
  uint8_t size;
  uint8_t destip[4];
  uint16_t desport;
  int32_t ret;

  switch (getSn_SR(SOCKET_UDP)) 
  {
    case SOCK_UDP:
      if((size = getSn_RX_RSR(SOCKET_UDP)) > 0)
      {
        ret = recvfrom(SOCKET_UDP, ethernet_buf, size, destip, (uint16_t*)&desport);

        if (ret > 0) 
        {
          ethernet_buf[ret] = '\0';
          return ethernet_buf;
        }
      }
      break;

    case SOCK_CLOSED:
      setup_udp();
      break;

    default:
      break;
  }

  ethernet_buf[0] = '\0';
  return ethernet_buf;
}

inline void calculate_broadcast_ip(const uint8_t* ip, const uint8_t* sn, uint8_t* buffer)
{
  if(!broadcast_ip_seted)
  {
    for(uint8_t i = 0; i < 4; i++)
    {
      buffer[i] = ~sn[i];
      buffer[i] |= ip[i];
    }
    broadcast_ip_seted = 1;
  }
}
