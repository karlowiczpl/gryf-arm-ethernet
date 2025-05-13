#include <stdint.h>

#include <pico/stdlib.h>
#include <stdio.h>

#include "uart.h"

uint8_t uart_buf[UART_BUF_MAX_SIZE] = {0};

void setup_uart()
{
  gpio_init(UART_PIN_1);
  gpio_init(UART_PIN_2);

  gpio_set_function(UART_PIN_1, GPIO_FUNC_UART);
  gpio_set_function(UART_PIN_2, GPIO_FUNC_UART);

  uart_init(UART_ID, BAUDRATE);
}
char* read_uart()
{
  uint8_t length = 0;

  while(uart_is_readable(UART_ID) && length <= UART_BUF_MAX_SIZE)
  {
    char c = uart_getc(UART_ID);
    if(c == '\0' || c == '\n' || c == '\r')
    {
      uart_buf[length] = '\0';
      return (char*)uart_buf;
    }
    uart_buf[length++] = c;
  }

  return NULL;
}
void send_to_uart(char *command)
{
  static char buffor[50];
  snprintf(buffor, sizeof(buffor), "%s\n\r", command);
  uart_puts(UART_ID, command);
}
