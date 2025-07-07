#include <stdint.h>
#include <wizchip_conf.h>
#include <port_common.h>
#include <w5x00_spi.h>
#include <socket.h>

#include <hardware/flash.h>

#include <dhcp.h>

#include "gDhcp.h"

#include "cpu.h"
#include "eeprom.h"

#include "GryfSmart_Config.h"

#ifdef DHCP_ENABLE
  wiz_NetInfo net_info = {
    .mac = {0, 0, 0, 0, 0, 0},
    .ip = {192, 168, 0, 95},
    .sn = {255, 255, 255, 0},
    .gw = {192, 168, 0, 1},
    .dns = {0, 0, 0, 0},
    .dhcp = NETINFO_DHCP,
  };
#endif /* ifdef DHCP_ENABLE */
#ifdef IP_FROM_CONFIG
  wiz_NetInfo net_info = {
    .mac = {0, 0, 0, 0, 0, 0},
    .ip = IP_ADDR,
    .sn = SN_ADDR,
    .gw = GW_ADDR,
    .dns = {0, 0, 0, 0},
    .dhcp = NETINFO_DHCP,
  };
#endif /* ifdef IP_FROM_CONFIG */
#if defined(STATIC_IP) || defined(STATIC_IP_WITH_DHCP_ADJUSMENT)
  wiz_NetInfo net_info = {
    .mac = {0, 0, 0, 0, 0, 0},
    .ip = {192, 168, 0, 95},
    .sn = {255, 255, 255, 0},
    .gw = {192, 168, 0, 1},
    .dns = {0, 0, 0, 0},
    .dhcp = NETINFO_STATIC,
  };
#endif /* ifdef  defined(STATIC_IP) || defined(STATIC_IP_WITH_DHCP_ADJUSMENT) */

void setup_ip()
{
  set_mac_addres();

#if defined(DHCP_ENABLE) || defined(STATIC_IP_WITH_DHCP_ADJUSMENT)
  dhcp_init();

  wizchip_ip_rental();
#else 
  #ifdef STATIC_IP
    const uint8_t* ip_addr = get_ip();
    const uint8_t* gw_addr = get_gw();
    const uint8_t* sn_addr = get_sn(); 

    for(uint8_t i = 0; i < 4; i++)
    {
      net_info.ip[i] = ip_addr[i]; 
      net_info.gw[i] = gw_addr[i]; 
      net_info.sn[i] = sn_addr[i]; 
    }
  #endif /* ifdef STATIC_IP */

  network_initialize(net_info);
#endif
}

inline void dhcp_init()
{
  DHCP_init(SOCKET_DHCP, ethernet_buf);

  reg_dhcp_cbfunc(wizchip_dhcp_assign, wizchip_dhcp_assign, wizchip_dhcp_conflict);
}

inline void wizchip_ip_rental()
{
  uint8_t retval = 0;
  uint8_t g_dhcp_get_ip_flag = 0;
  uint8_t dhcp_retry = 0;

  while(1)
  {
    retval = DHCP_run();

    switch(retval)
    {
      case DHCP_IP_LEASED:
        return;
      break;

      case DHCP_FAILED:
        g_dhcp_get_ip_flag = 0;
        dhcp_retry++;

        if(dhcp_retry > DHCP_MAX_RETRY_COUNT)
        {
          DHCP_stop();

          const uint8_t* ip_addr = get_ip();
          const uint8_t* gw_addr = get_gw();
          const uint8_t* sn_addr = get_sn(); 

          for(uint8_t i = 0; i < 4; i++)
          {
            net_info.ip[i] = ip_addr[i]; 
            net_info.gw[i] = gw_addr[i]; 
            net_info.sn[i] = sn_addr[i]; 
          }

          network_initialize(net_info);
        }
      break;
    }
  }
}

void wizchip_dhcp_assign()
{
  #ifdef DHCP_ENABLE
    getIPfromDHCP(net_info.ip);
    getGWfromDHCP(net_info.gw);
    getSNfromDHCP(net_info.sn);
    getDNSfromDHCP(net_info.dns);

    net_info.dhcp = NETINFO_DHCP;

    // update_eeprom_network_data(net_info.ip, net_info.gw, net_info.sn);
    network_initialize(net_info);
  #endif /* ifdef DHCP_ENABLE */

  #ifdef STATIC_IP_WITH_DHCP_ADJUSMENT
    getIPfromDHCP(net_info.ip);
    getGWfromDHCP(net_info.gw);
    getSNfromDHCP(net_info.sn);
    getDNSfromDHCP(net_info.dns);

    net_info.dhcp = NETINFO_STATIC;

    const uint8_t* ip_addr = get_ip();
    net_info.ip[3] = ip_addr[3];

    network_initialize(net_info);
  #endif /* ifdef STATIC_IP_WITH_DHCP_ADJUSMENT */
}
void wizchip_dhcp_conflict()
{
  reset_all();
}

inline void set_mac_addres()
{
  uint8_t unique_id[8];
  flash_get_unique_id(unique_id);

  net_info.mac[0] = 0x02;
  for(uint8_t i = 1; i < 6; i++)    net_info.mac[i] = unique_id[i];
}
