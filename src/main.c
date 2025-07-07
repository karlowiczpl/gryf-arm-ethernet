#include <boards/pico.h>
#include <hardware/gpio.h>
#include <pico.h>
#include <pico/stdio.h>
#include <pico/time.h>
#include <stdint.h>
#include <stdio.h>

#include <pico/stdlib.h>

#include "eeprom.h"
#include "gEth.h"
#include "gUtp.h"
#include "hardware/pio.h"
// #include "blink.pio.h"

static void ethernet_task()
{
  stdio_init_all();

  read_data_from_eeprom();
  setup_ethernet();

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
  gpio_put(PICO_DEFAULT_LED_PIN, 1);

  sleep_ms(1000);

  while(1)
  {
    char* input = read_broadcast_udp();
    if(input[0] != '\0')    
    {
      send_to_udp(input);

      printf("%s\n", input);
    }

  }
}


int main()
{
  ethernet_task();
}
