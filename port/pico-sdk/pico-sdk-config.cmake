add_library(PICO_SDK_FILES STATIC)

target_link_libraries(PICO_SDK_FILES
  pico_stdlib
  hardware_watchdog
  hardware_flash
)
