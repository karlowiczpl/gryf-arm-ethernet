#include <boards/pico.h>
#include <hardware/gpio.h>
#include <pico.h>
#include <pico/stdio.h>
#include <stdint.h>
#include <stdio.h>

#include <pico/stdlib.h>

#include "eeprom.h"
#include "gEth.h"
#include "gUtp.h"

static void ethernet_task()
{
  stdio_init_all();

  sleep_ms(3000);
  read_data_from_eeprom();
  setup_ethernet();

  while(1)
  {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    char* input = read_broadcast_udp();
    send_to_udp(input);
  }
}


int main()
{
  ethernet_task();
}
