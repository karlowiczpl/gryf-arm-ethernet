#ifndef UART_HARDWARE_H
#define UART_HARDWARE_H

#include <stdint.h>

#define UART_BUF_MAX_SIZE 512
#define UART_PIN_1 0
#define UART_PIN_2 1
#define UART_ID uart0
#define BAUDRATE 115200

void setup_uart();
char* read_uart();
void send_to_uart(char* command);

#endif // !UART_HARDWARE_H
