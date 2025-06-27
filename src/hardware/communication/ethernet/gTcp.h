#ifndef TCP_HARDWARE_H
#define TCP_HARDWARE_H

#include <stdint.h>

#define PLL_SYS_KHZ (133 * 1000)
#define ETHERNET_BUF_MAX_SIZE 512

#define TCP_PORT 4510

#define DHCP_RETRY_COUNT 5
#define DNS_RETRY_COUNT 5

// #define DHCP_HANDLER
// #define DNS_HANDLER

#define SOCKET_MIN_TCP 0
#define SOCKET_MAX_TCP 3

#define HTTP_SERVER_HANDLER

#define SOCKET_MIN_HTTP 4
#define SOCKET_MAX_HTTP 6
#define SOCKET_HTTP_LIST {0, 1, 2, 3}

#define HTTP_SOCKET_MAX_NUM 4

#define HTTP_PORT 80

#define SOCKET_DHCP 7

#define SOCKET_DNS 11

#define HTTP_BUF_MAX_SIZE (1024 * 2)

void setup_tcp();
char* read_tcp();
void http_server_run();

void set_ethernet_properties(uint8_t* ip, uint8_t* gw, uint8_t* sn);

static inline void set_clock_khz();
static void wizchip_dhcp_assign();
static void wizchip_dhcp_conflict();
static void repeating_timer_callback();
static void wizchip_dhcp_dns_init();
static void repeating_timer_callback();

inline static void wizchip_static_init();
inline static void wizchip_ip_rental();

#endif // !TCP_HARDWARE_H

