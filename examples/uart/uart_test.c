#include "../../sprinkio.h"

uint8_t character = 'a';

int main() {
  uart_init();
  system_init();
  write_atmel(character);
  return 0;
}
