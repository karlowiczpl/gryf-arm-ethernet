set(WIZNET-PICO-C_SDK_VERSION_MAJOR 2)
set(WIZNET-PICO-C_SDK_VERSION_MINOR 0)
set(WIZNET-PICO-C_SDK_VERSION_REVISION 0)
set(WIZNET-PICO-C_SDK_VERSION_STRING "${WIZNET-PICO-C_SDK_VERSION_MAJOR}.${WIZNET-PICO-C_SDK_VERSION_MINOR}.${WIZNET-PICO-C_SDK_VERSION_REVISION}")

message(STATUS "WIZNET-PICO-C SDK version is ${WIZNET-PICO-C_SDK_VERSION_STRING}")

set(WIZNET_DIR ${CMAKE_SOURCE_DIR}/lib/ioLibrary_Driver)
set(PICO_SDK_DIR ${CMAKE_CURRENT_LIST_DIR}/pico-sdk)

add_library(ETHERNET_FILES STATIC)

target_sources(ETHERNET_FILES PUBLIC
  ${WIZNET_DIR}/Ethernet/socket.c
  ${WIZNET_DIR}/Ethernet/wizchip_conf.c
  ${WIZNET_DIR}/Ethernet/W5500/w5500.c
)
target_include_directories(ETHERNET_FILES PUBLIC
  ${WIZNET_DIR}/Ethernet
  ${WIZNET_DIR}/Ethernet/W5500
)

add_library(IOLIBRARY_FILES STATIC)

target_sources(IOLIBRARY_FILES PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src/w5x00_spi.c
  ${CMAKE_CURRENT_LIST_DIR}/src/w5x00_gpio_irq.c
)
target_include_directories(IOLIBRARY_FILES PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/inc
  ${WIZNET_DIR}/Ethernet
)

target_link_libraries(IOLIBRARY_FILES PUBLIC
  pico_stdlib
  hardware_pio
  hardware_spi
  hardware_dma
  hardware_clocks
)

add_library(TIMER_FILES STATIC)

target_sources(TIMER_FILES PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/timer/timer.c
)

target_include_directories(TIMER_FILES PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/timer
)

target_link_libraries(TIMER_FILES PUBLIC
  pico_stdlib
)

# DHCP FILES

add_library(DHCP_FILES STATIC)

target_sources(DHCP_FILES PUBLIC
        ${WIZNET_DIR}/Internet/DHCP/dhcp.c
)

target_include_directories(DHCP_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/DHCP
)

# DNS
add_library(DNS_FILES STATIC)

target_sources(DNS_FILES PUBLIC
        ${WIZNET_DIR}/Internet/DNS/dns.c
        )

target_include_directories(DNS_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/DNS
        )

# HTTP Server
add_library(HTTPSERVER_FILES STATIC)

target_sources(HTTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Internet/httpServer/httpParser.c
        ${WIZNET_DIR}/Internet/httpServer/httpServer.c
        ${WIZNET_DIR}/Internet/httpServer/httpUtil.c
        )

target_include_directories(HTTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/httpServer
        )

# Loopback
add_library(LOOPBACK_FILES STATIC)

target_sources(LOOPBACK_FILES PUBLIC
        ${WIZNET_DIR}/Application/loopback/loopback.c
        )

target_include_directories(LOOPBACK_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Application/loopback
        )

