#ifndef MENU_H
#define MENU_H

#include "sprinkio.h"

#define NUM_MENUS

// input events
#define IE_NO_EVENT 0x01
#define IE_BUTTON_PRESS 0x02
#define IE_ROTARY_ENC_LEFT 0x03
#define IE_ROTARY_ENC_RIGHT 0x04

// menu element types
#define ME_NAV 0x01 // navigation to submenu field label
#define ME_LABEL 0x02 // user editable field label
#define ME_DISPLAY 0x03 // information display element
#define ME_ACTION 0x04 // action field element

// option limit array indices
#define OPTION_START 0
#define OPTION_END 1
#define OPTION_STEP 2

// on off option indices
#define OPTION_ON 0
#define OPTION_OFF 1

// yes no option indices
#define OPTION_YES 0
#define OPTION_NO 1

// network settings indices
#define NS_CONNECTED 0
#define NS_DISCONNECTED 1

void menu_init();
void build_all_menus();
void update_input_event(uint8_t event);
void menu_loop();

#endif
