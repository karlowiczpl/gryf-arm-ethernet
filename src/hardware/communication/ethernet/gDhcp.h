#ifndef GDHCP_H
#define GDHCP_H

#include <stdint.h>

#include "wizchip_conf.h"

#include "ethernet_config.h"

#define DHCP_MAX_RETRY_COUNT 5

extern uint8_t ethernet_buf[ETHERNET_BUF_MAX_SIZE];
extern wiz_NetInfo net_info;

void setup_ip();

static void dhcp_init();
static void wizchip_ip_rental();
static void wizchip_dhcp_assign();
static void wizchip_dhcp_conflict();
static void set_mac_addres();

#endif // !GDHCP_H
