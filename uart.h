#ifndef UART_H
#define UART_H

#include "sprinkio.h"

#define BAUD 9600

#define UART_NO_DATA 0xFF

void uart_init();
void uart_write(uint8_t ch);
uint8_t uart_read();

#endif
