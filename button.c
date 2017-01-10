#include "sprinkio.h"

uint8_t toggle;
unsigned int last_interrupt_time;

/**
 * Button press interrupt service handler
 */
void button_isr() {
  unsigned int interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200) {
    if (++toggle == 2) toggle = 0; // toggle between 0 and 1
    update_input_event(IE_BUTTON_PRESS); // set input event flag
  }
  last_interrupt_time = interrupt_time;
}

/**
 * Initialize button
 */
void button_init() {
  toggle = 0;
  last_interrupt_time = 0;
  BUTTON_EN(); // set button GPIO to input
  pullUpDnControl(BUTTON_GPIO, PUD_UP); // enable pull-up resistor
  wiringPiISR(BUTTON_GPIO, INT_EDGE_RISING, button_isr); // enable interrupts
}
