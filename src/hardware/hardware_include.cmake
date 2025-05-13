add_library(hardware_files STATIC)

target_sources(hardware_files PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/communication/tcp.c
  ${CMAKE_CURRENT_LIST_DIR}/communication/uart.c
)

target_include_directories(hardware_files PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/communication
)

target_link_libraries(hardware_files PUBLIC
  ETHERNET_FILES
  IOLIBRARY_FILES
  TIMER_FILES
)
