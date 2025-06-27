#ifndef GDHCP_H
#define GDHCP_H

#include <stdint.h>

#define PLL_SYS_KHZ (133 * 1000)

extern void setup_ethernet();

static void setup_dhcp();

#endif // !GDHCP_H
