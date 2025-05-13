set(FREERTOS_DIR ${LIB_DIR}/FreeRTOS-Kernel)

add_library(FREERTOS_CONFIG STATIC)
include(${FREERTOS_DIR}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

target_include_directories(FREERTOS_CONFIG PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(FREERTOS_CONFIG PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/freertos_hooks.c
)
target_link_libraries(FREERTOS_CONFIG
  FreeRTOS-Kernel
)
