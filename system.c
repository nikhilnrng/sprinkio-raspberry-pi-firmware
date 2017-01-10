#include "sprinkio.h"

bool system_init() {
  uart_init();
  wiringPiSetup();
  if (!bcm2835_init()) {
    return false;
  }
  lcd_init();
  rotary_encoder_init();
  button_init();
  return true;
}
