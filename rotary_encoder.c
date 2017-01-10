#include "sprinkio.h"

volatile uint64_t rotary_encoder_value;
volatile uint64_t rotary_encoder_state;
volatile uint8_t rotary_encoder_last_encoded;
unsigned int last_interrupt_time;

void rotary_encoder_isr() {
  unsigned int interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200) {
    uint64_t state;
    uint8_t MSB = ROTARY_ENCODER_PIN_A_LEV();
    uint8_t LSB = ROTARY_ENCODER_PIN_B_LEV();
    uint8_t encoded = (MSB << 1) | LSB;
    uint8_t sum = (rotary_encoder_last_encoded << 2) | encoded;
    // calculate rotary encoder value
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
      rotary_encoder_value++; // increment rotary encoder value
    }
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
      rotary_encoder_value--; // decrement rotary encoder value
    }
    // calculate rotary encoder state
    state = rotary_encoder_value / 3;
    if (state - rotary_encoder_state == 1) {
      update_input_event(IE_ROTARY_ENC_RIGHT); // set rotary encoder right flag
    } else if (rotary_encoder_state - state == 1) {
      update_input_event(IE_ROTARY_ENC_LEFT); // set rotary encoder left flag
    }
    rotary_encoder_state = state;
    rotary_encoder_last_encoded = encoded;
  }
}

void rotary_encoder_init() {
  rotary_encoder_value = 0;
  rotary_encoder_last_encoded = 0;
  ROTARY_ENCODER_PIN_A_EN();
  ROTARY_ENCODER_PIN_B_EN();
  pullUpDnControl(ROTARY_ENCODER_GPIO_A, PUD_UP); // enable pull-up resistor
  pullUpDnControl(ROTARY_ENCODER_GPIO_B, PUD_UP); // enable pull-up resistor
  wiringPiISR(ROTARY_ENCODER_GPIO_A, INT_EDGE_BOTH, rotary_encoder_isr);
  wiringPiISR(ROTARY_ENCODER_GPIO_B, INT_EDGE_BOTH, rotary_encoder_isr);
}
