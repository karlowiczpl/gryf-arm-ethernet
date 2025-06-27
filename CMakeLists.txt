set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(PORT_DIR ${CMAKE_SOURCE_DIR}/port)
set(PICO_SDK_DIR ${LIB_DIR}/pico-sdk)

set(ENABLE_PROGRAMS OFF CACHE BOOL "Build mbedtls programs")
set(ENABLE_TESTING OFF CACHE BOOL "Build mbedtls testing")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(WIZNET_CHIP W5500)
add_definitions(
    -D_WIZCHIP_=${WIZNET_CHIP}
    -DDEVICE_BOARD_NAME=${BOARD_NAME}
)
add_definitions(
    -DMBEDTLS_CONFIG_FILE="${PORT_DIR}/mbedtls/ssl_config.h"
    -DSET_TRUSTED_CERT_IN_SAMPLES
)

cmake_minimum_required(VERSION 3.12)

include(${PICO_SDK_DIR}/external/pico_sdk_import.cmake)
include(${PORT_DIR}/pico-sdk/pico-sdk-config.cmake)
include(${PORT_DIR}/ioLibrary_Driver/wiznet_config.cmake)
include(${PORT_DIR}/FreeRTOS-Kernel/freertos_config.cmake)
include(${SRC_DIR}/hardware/hardware_include.cmake)
include(${SRC_DIR}/abstract/abstract_include.cmake)

project(ARM_GRYF_ETHERNET C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)

pico_sdk_init()

add_executable(${PROJECT_NAME}
  ${SRC_DIR}/main.c
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
  PICO_SDK_FILES
  FREERTOS_CONFIG

  hardware_files
  abstract_files
)

add_library(GRYF_SMART_CONFIG INTERFACE)
target_include_directories(GRYF_SMART_CONFIG INTERFACE 
  ${CMAKE_CURRENT_LIST_DIR}/
)

add_subdirectory(${LIB_DIR}/mbedtls)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
