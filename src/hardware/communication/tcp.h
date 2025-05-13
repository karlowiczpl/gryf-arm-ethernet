#ifndef TCP_HARDWARE_H
#define TCP_HARDWARE_H

#include <stdint.h>

#define PLL_SYS_KHZ (133 * 1000)
#define ETHERNET_BUF_MAX_SIZE 512
#define DEFAULT_PORT 4510

void setup_tcp();
char* read_tcp();
void set_ip_addr(uint8_t* ip);
void set_tcp_port(int port);

#endif // !TCP_HARDWARE_H

