#ifndef GUTP_H
#define GUTP_H

#include <stdint.h>

#include "wizchip_conf.h"

#include "GryfSmart_Config.h"
#include "ethernet_config.h"

extern uint8_t ethernet_buf[ETHERNET_BUF_MAX_SIZE];
extern wiz_NetInfo net_info;

void setup_udp();
void send_to_udp(uint8_t* msg);
uint8_t* read_broadcast_udp();

static void calculate_broadcast_ip(const uint8_t* ip, const uint8_t* sn, uint8_t* bufer);

#endif // !GUTP_H
