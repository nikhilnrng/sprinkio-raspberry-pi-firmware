#include "sprinkio.h"

void write_atmel(uint8_t data) {
  UART_SELECT_EN();
  UART_ATMEL_EN();
  uart_write(data);
  delay(200);
}

uint8_t read_atmel() {
  return uart_read();
}
