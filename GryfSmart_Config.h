#ifndef GryfSmart_Config_h
#define GryfSmart_Config_h

/*
*     GPIO CONFIG
*/

/*
*     IP CONFIG
*/

#define DHCP_ENABLE
// #define STATIC_IP
// #define STATIC_IP_WITH_DHCP_ADJUSMENT

// #define IP_FROM_CONFIG
// #define IP_ADDR {192, 168, 40, 95} // Work only when IP_FROM_CONFIG is defined
// #define SN_ADDR {255, 255, 255, 0}
// #define GW_ADDR {192, 168, 40, 1}

/*
*     COMMUNICATION CONFIG
*/

#define UDP_BROADCAST_HANDLER
#define UDP_PORT 6000

#endif // !GryfSmart_Config_h
