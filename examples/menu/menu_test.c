#include "../../sprinkio.h"

int main() {
  uart_init();
  system_init();
  lcd_init();
  rotary_encoder_init();
  button_init();
  menu_init();
  return 0;
}