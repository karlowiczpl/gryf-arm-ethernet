add_library(hardware_files STATIC)

set(ETHERNET_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/communication/ethernet/gDhcp.c
  ${CMAKE_CURRENT_LIST_DIR}/communication/ethernet/gHttp.c
  ${CMAKE_CURRENT_LIST_DIR}/communication/ethernet/gTcp.c
  ${CMAKE_CURRENT_LIST_DIR}/communication/ethernet/gEth.c
  ${CMAKE_CURRENT_LIST_DIR}/communication/ethernet/gUtp.c
)

target_sources(hardware_files PUBLIC
  ${ETHERNET_SOURCES}

  ${CMAKE_CURRENT_LIST_DIR}/communication/uart.c
  ${CMAKE_CURRENT_LIST_DIR}/cpu/cpu.c
  ${CMAKE_CURRENT_LIST_DIR}/eeprom/eeprom.c
)

target_include_directories(hardware_files PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/communication
  ${CMAKE_CURRENT_LIST_DIR}/communication/ethernet
  ${CMAKE_CURRENT_LIST_DIR}/cpu
  ${CMAKE_CURRENT_LIST_DIR}/eeprom
)

target_link_libraries(hardware_files PUBLIC
  PICO_SDK_FILES
  ETHERNET_FILES
  IOLIBRARY_FILES
  TIMER_FILES
  GRYF_SMART_CONFIG 
  DHCP_FILES
  DNS_FILES
  FREERTOS_CONFIG
  HTTPSERVER_FILES
  LOOPBACK_FILES
)
