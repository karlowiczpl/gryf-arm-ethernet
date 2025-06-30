#ifndef GETH_H
#define GETH_H

#include <stdint.h>

#include "ethernet_config.h"

extern uint8_t ethernet_buf[ETHERNET_BUF_MAX_SIZE];

void setup_ethernet();

static void set_clock_khz();
void repeating_timer_callback();

#endif // !GETH_H
