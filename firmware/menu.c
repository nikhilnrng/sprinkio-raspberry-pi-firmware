#include "sprinkio.h"

uint8_t input_event;
struct menu* current_menu;

// main menu titles
const char MT_MM[] = " Sprinkio Main Menu ";
const char MT_MM_ZONE_STATUS[] = "View Zone Status";
const char MT_MM_SETUP_ZONE[] = "Setup Zone";
const char MT_MM_NETWORK_SETTINGS[] = "Network Settings";
const char MT_MM_MANUAL_ZONE_CNTRL[] = "Manual Zone Control";
const char MT_MM_SETUP_MODE[] = "Setup Mode";

// view zone status titles
char MT_ZS[] = " Select Zone Number ";
char MT_ZS_ZONE_NUMBER[] = "Zone Number";

// setup zone titles
char MT_SZ[] = " Enter Zone Details ";
char MT_SZ_ZONE_NUMBER[] = "Zone Number";
char MT_SZ_DAYS_OF_WEEK[] = "Days of Week";
char MT_SZ_START_TIME[] = "Start Time";
char MT_SZ_DURATION[] = "Duration";
char MT_SZ_MOISTURE_SENSOR[] = "Moisture Snsr";

// setup days of week
char MT_SDOW[] = " Enter Days of Week ";
char MT_SDOW_SUNDAY[] = "Sunday";
char MT_SDOW_MONDAY[] = "Monday";
char MT_SDOW_TUESDAY[] = "Tuesday";
char MT_SDOW_WEDNESDAY[] = "Wednesday";
char MT_SDOW_THURSDAY[] = "Thursday";
char MT_SDOW_FRIDAY[] = "Friday";
char MT_SDOW_SATURDAY[] = "Saturday";

// setup time titles
char MT_ST[] = " Enter a Time ";
char MT_ST_HOUR[] = "Hour";
char MT_ST_MINUTE[] = "Minute";
char MT_ST_SECOND[] = "Second";

// network settings titles
char MT_NS[] = "  Network Settings  ";
char MT_NS_STATUS[] = "Status";
char MT_NS_IP_ADDRESS[] = "IP Address";

// manual zone control titles
char MT_MZC[] = "    Zone Control    ";
char MT_MZC_ZONE_1[] = "Zone 1";
char MT_MZC_ZONE_2[] = "Zone 2";
char MT_MZC_ZONE_3[] = "Zone 3";
char MT_MZC_ZONE_4[] = "Zone 4";
char MT_MZC_ZONE_5[] = "Zone 5";
char MT_MZC_ZONE_6[] = "Zone 6";
char MT_MZC_ZONE_7[] = "Zone 7";
char MT_MZC_ZONE_8[] = "Zone 8";

// setup mode titles
char MT_SM[] = "     Setup Mode     ";
char MT_SM_WATER_SAVER[] = "Water Saver";

char MT_BACK[] = "Back >";
char MT_ENTER[] = "Enter >";
char MT_SET[] = "Set >";

// view zone status titles
const char* OPTION_DURATION[] = {"1", "60", "1"}; // start, end, step
const char* OPTION_ZONE[] = {"1", "8", "1"}; // start, end, step
const char* OPTION_HOUR[] = {"0", "23", "1"}; // start, end, step
const char* OPTION_MIN[] = {"0", "59", "1"}; // start, end, step
const char* OPTION_SEC[] = {"0", "59", "1"}; // start, end, step
const char* OPTION_ON_OFF[] = {"ON", "OFF"};
const char* OPTION_YES_NO[] = {"YES", "NO"};
const char* OPTION_NETWORK_STATUS[] = {"CONNECTED", "DISCONNECTED"};
const char* OPTION_IP_ADDRESS[] = {"172.20.10.6"};

struct menu_element mm_zone_status, mm_setup_zone, mm_network_settings, mm_manual_zone_control, mm_setup_mode;
struct menu_element sz_zone_number, sz_days_of_week, sz_start_time, sz_duration, sz_moisture_sensor, sz_back, sz_action;
struct menu_element sdow_sunday, sdow_monday, sdow_tuesday, sdow_wednesday, sdow_thursday, sdow_friday, sdow_saturday, sdow_back, sdow_action;
struct menu_element st_hour, st_minute, st_second, st_back, st_action;
struct menu_element ns_status, ns_ip_address, ns_back;
struct menu_element mzc_zone_1, mzc_zone_2, mzc_zone_3, mzc_zone_4, mzc_zone_5, mzc_zone_6, mzc_zone_7, mzc_zone_8, mzc_back, mzc_action;
struct menu_element sm_water_saver, sm_back, sm_action;

// menus
struct menu main_menu;
struct menu zone_status;
struct menu setup_zone;
struct menu setup_days_of_week;
struct menu setup_time;
struct menu network_settings;
struct menu manual_zone_control;
struct menu setup_mode;

/** 
 * Initialize menu
 */
void menu_init() {
  input_event = IE_NO_EVENT;
  build_all_menus();
  current_menu = &main_menu;
  write_lcd_menu(current_menu);
  menu_loop();
}

static void build_menu_label_element(struct menu_element* menu_element, 
  const char* text, const char** options, uint8_t option_length, bool is_options_limit,
  struct menu_element* prev_element, struct menu_element* next_element) {
  menu_element->text = text;
  menu_element->type = ME_LABEL;
  menu_element->is_active = false;
  menu_element->value = (uint8_t) atoi(options[0]);
  menu_element->options = options;
  menu_element->option_indx = 0;
  menu_element->option_length = option_length;
  menu_element->is_options_limit = is_options_limit;
  menu_element->is_option_active = false;
  menu_element->is_option_selected = false;
  menu_element->next_menu = NULL; // don't care
  menu_element->prev_element = prev_element;
  menu_element->next_element = next_element;
}

static void build_menu_display_element(struct menu_element* menu_element, 
  const char* text, const char** options, uint8_t option_indx, struct menu_element* next_element, 
  struct menu_element* prev_element) {
  menu_element->text = text;
  menu_element->type = ME_DISPLAY;
  menu_element->is_active = false; 
  menu_element->value = 0;
  menu_element->options = options;
  menu_element->option_indx = option_indx;
  menu_element->option_length = 0;
  menu_element->is_options_limit = false;
  menu_element->is_option_active = false;
  menu_element->is_option_selected = false;
  menu_element->next_menu = NULL;
  menu_element->prev_element = prev_element;
  menu_element->next_element = next_element;
}

static void build_menu_nav_element(struct menu_element* menu_element, 
  const char* text, struct menu* next_menu, struct menu_element* prev_element, 
  struct menu_element* next_element) {
  menu_element->text = text;
  menu_element->type = ME_NAV;
  menu_element->is_active = false; 
  menu_element->value = 0;
  menu_element->options = NULL;
  menu_element->option_indx = 0;
  menu_element->option_length = 0;
  menu_element->is_options_limit = false;
  menu_element->is_option_active = false;
  menu_element->is_option_selected = false;
  menu_element->next_menu = next_menu;
  menu_element->prev_element = prev_element;
  menu_element->next_element = next_element;
}

static void build_menu_action_element(struct menu_element* menu_element, 
  const char* text, struct menu_element* prev_element, 
  struct menu_element* next_element) {
  menu_element->text = text;
  menu_element->type = ME_ACTION;
  menu_element->is_active = false;
  menu_element->value = 0;
  menu_element->options = NULL;
  menu_element->option_indx = 0;
  menu_element->option_length = 0;
  menu_element->is_options_limit = 0;
  menu_element->is_option_active = false;
  menu_element->is_option_selected = false;
  menu_element->next_menu = NULL;
  menu_element->prev_element = prev_element;
  menu_element->next_element = next_element;
}

void build_menu(struct menu* menu, const char* title, 
  void (*action)(void), struct menu_element* current_element) {
  // store menu parameters
  menu->title = title;
  menu->action = action;
  menu->current_element = current_element;

  // activate first menu element
  menu->current_element->is_active = true;
}

static void build_main_menu() {
  // build main menu elements
  build_menu_nav_element(&mm_zone_status, MT_MM_ZONE_STATUS, &zone_status, NULL, &mm_setup_zone);
  build_menu_nav_element(&mm_setup_zone, MT_MM_SETUP_ZONE, &setup_zone, &mm_zone_status, &mm_network_settings);
  build_menu_nav_element(&mm_network_settings, MT_MM_NETWORK_SETTINGS, &network_settings, &mm_setup_zone, &mm_manual_zone_control);
  build_menu_nav_element(&mm_manual_zone_control, MT_MM_MANUAL_ZONE_CNTRL, &manual_zone_control, &mm_network_settings, &mm_setup_mode);
  build_menu_nav_element(&mm_setup_mode, MT_MM_SETUP_MODE, &setup_mode, &mm_manual_zone_control, NULL);

  // build main menu
  build_menu(&main_menu, MT_MM, 0, &mm_zone_status);
}

static void build_setup_zone_menu() {
  // build setup zone elements
  build_menu_label_element(&sz_zone_number, MT_SZ_ZONE_NUMBER, OPTION_ZONE, 0, true, NULL, &sz_days_of_week);
  build_menu_nav_element(&sz_days_of_week, MT_SZ_DAYS_OF_WEEK, &setup_days_of_week, &sz_zone_number, &sz_start_time);
  build_menu_nav_element(&sz_start_time, MT_SZ_START_TIME, &setup_time, &sz_days_of_week, &sz_duration);
  build_menu_label_element(&sz_duration, MT_SZ_DURATION, OPTION_DURATION, 0, true, &sz_start_time, &sz_moisture_sensor);
  build_menu_label_element(&sz_moisture_sensor, MT_SZ_MOISTURE_SENSOR, OPTION_YES_NO, 2, false, &sz_duration, &sz_action);
  build_menu_action_element(&sz_action, MT_SET, &sz_moisture_sensor, &sz_back);
  build_menu_nav_element(&sz_back, MT_BACK, &main_menu, &sz_action, NULL);

  // build setup zone menu
  build_menu(&setup_zone, MT_SZ, compile_zone, &sz_zone_number);
}

static void build_setup_days_of_week_menu() {
  // build setup days of week elements
  build_menu_label_element(&sdow_sunday, MT_SDOW_SUNDAY, OPTION_ON_OFF, 2, false, NULL, &sdow_monday);
  build_menu_label_element(&sdow_monday, MT_SDOW_MONDAY, OPTION_ON_OFF, 2, false, &sdow_sunday, &sdow_tuesday);
  build_menu_label_element(&sdow_tuesday, MT_SDOW_TUESDAY, OPTION_ON_OFF, 2, false, &sdow_monday, &sdow_wednesday);
  build_menu_label_element(&sdow_wednesday, MT_SDOW_WEDNESDAY, OPTION_ON_OFF, 2, false, &sdow_tuesday, &sdow_thursday);
  build_menu_label_element(&sdow_thursday, MT_SDOW_THURSDAY, OPTION_ON_OFF, 2, false, &sdow_wednesday, &sdow_friday);
  build_menu_label_element(&sdow_friday, MT_SDOW_FRIDAY, OPTION_ON_OFF, 2, false, &sdow_thursday, &sdow_saturday);
  build_menu_label_element(&sdow_saturday, MT_SDOW_SATURDAY, OPTION_ON_OFF, 2, false, &sdow_friday, &sdow_action);
  build_menu_action_element(&sdow_action, MT_SET, &sdow_saturday, &sdow_back);
  build_menu_nav_element(&sdow_back, MT_BACK, &setup_zone, &sdow_action, NULL);

  // build setup days of week menu
  build_menu(&setup_days_of_week, MT_SDOW, compile_days_of_week, &sdow_sunday);
}

static void build_setup_time_menu() {
  // build setup time elements
  build_menu_label_element(&st_hour, MT_ST_HOUR, OPTION_HOUR, 0, true, NULL, &st_minute);
  build_menu_label_element(&st_minute, MT_ST_MINUTE, OPTION_MIN, 0, true, &st_hour, &st_second);
  build_menu_label_element(&st_second, MT_ST_SECOND, OPTION_SEC, 0, true, &st_minute, &st_action);
  build_menu_action_element(&st_action, MT_SET, &st_second, &st_back);
  build_menu_nav_element(&st_back, MT_BACK, &setup_zone, &st_action, NULL);

  // build setup time menu
  build_menu(&setup_time, MT_ST, compile_time, &st_hour);
}

static void build_manual_zone_control_menu() {
  // build manual zone control menu elements
  build_menu_label_element(&mzc_zone_1, MT_MZC_ZONE_1, OPTION_ON_OFF, 2, false, NULL, &mzc_zone_2);
  build_menu_label_element(&mzc_zone_2, MT_MZC_ZONE_2, OPTION_ON_OFF, 2, false, &mzc_zone_1, &mzc_zone_3);
  build_menu_label_element(&mzc_zone_3, MT_MZC_ZONE_3, OPTION_ON_OFF, 2, false, &mzc_zone_2, &mzc_zone_4);
  build_menu_label_element(&mzc_zone_4, MT_MZC_ZONE_4, OPTION_ON_OFF, 2, false, &mzc_zone_3, &mzc_zone_5);
  build_menu_label_element(&mzc_zone_5, MT_MZC_ZONE_5, OPTION_ON_OFF, 2, false, &mzc_zone_4, &mzc_zone_6);
  build_menu_label_element(&mzc_zone_6, MT_MZC_ZONE_6, OPTION_ON_OFF, 2, false, &mzc_zone_5, &mzc_zone_7);
  build_menu_label_element(&mzc_zone_7, MT_MZC_ZONE_7, OPTION_ON_OFF, 2, false, &mzc_zone_6, &mzc_zone_8);
  build_menu_label_element(&mzc_zone_8, MT_MZC_ZONE_8, OPTION_ON_OFF, 2, false, &mzc_zone_7, &mzc_action);
  build_menu_action_element(&mzc_action, MT_ENTER, &mzc_zone_8, &mzc_back);
  build_menu_nav_element(&mzc_back, MT_BACK, &main_menu, &mzc_action, NULL);

  // build manual zone control menu
  build_menu(&manual_zone_control, MT_MZC, compile_zone_control, &mzc_zone_1);
}

static void build_setup_mode_menu() {
  // build setup mode menu elements
  build_menu_label_element(&sm_water_saver, MT_SM_WATER_SAVER, OPTION_ON_OFF, 2, false, NULL, &sm_back);
  build_menu_nav_element(&sm_back, MT_BACK, &main_menu, &sm_water_saver, NULL);

  // build setup mode menu
  build_menu(&setup_mode, MT_SM, compile_mode, &sm_water_saver);
}

void build_network_settings_menu() {
  // build network settings elements
  build_menu_display_element(&ns_status, MT_NS_STATUS, OPTION_NETWORK_STATUS, NS_CONNECTED, NULL, &ns_ip_address);
  build_menu_display_element(&ns_ip_address, MT_NS_IP_ADDRESS, OPTION_IP_ADDRESS, 0, &ns_status, &ns_back);
  build_menu_nav_element(&ns_back, MT_BACK, &main_menu, &ns_ip_address, NULL);

  build_menu(&network_settings, MT_NS, 0, &ns_status);
}

void build_all_menus() {
  build_main_menu();
  build_setup_zone_menu();
  build_setup_days_of_week_menu();
  build_setup_time_menu();
  build_manual_zone_control_menu();
  build_setup_mode_menu();
  build_network_settings_menu();
}

/**
 * Update input event field when event occurs
 */
void update_input_event(uint8_t event) {
  input_event = event;
}

/**
 * Update menu based on input events
 */
void menu_loop() {
  while (1) {
    while (input_event == IE_NO_EVENT); // wait for input event
    switch (input_event) {
      case IE_BUTTON_PRESS:
        printf("Button pressed\n");
        if (current_menu->current_element->type == ME_NAV) {
          printf("Redirecting menu\n");
          current_menu = current_menu->current_element->next_menu;
        } else if (current_menu->current_element->type == ME_LABEL) {
          if (!current_menu->current_element->is_option_active) {
            current_menu->current_element->is_option_active = true;
          } else {
            current_menu->current_element->is_option_selected = true;
            current_menu->current_element->is_option_active = false;
          }
        } else if (current_menu->current_element->type == ME_ACTION) {
          current_menu->action();
        }
        write_lcd_menu(current_menu);
        update_input_event(IE_NO_EVENT);
        break;
      case IE_ROTARY_ENC_LEFT:
        if (current_menu->current_element->type == ME_LABEL &&
          current_menu->current_element->is_option_active) {
          if (current_menu->current_element->is_options_limit) {
            uint8_t new_value = current_menu->current_element->value - (uint8_t) atoi(current_menu->current_element->options[OPTION_STEP]);
            if (new_value == 255 || new_value < (uint8_t) atoi(current_menu->current_element->options[OPTION_START])) break;
            current_menu->current_element->value = new_value;
          } else {
            uint8_t new_option_indx = current_menu->current_element->option_indx - 1;
            if (new_option_indx == 255) new_option_indx = 0;
            current_menu->current_element->option_indx = new_option_indx;
          }
          write_lcd_menu(current_menu);
          update_input_event(IE_NO_EVENT);
        } else {
          if (current_menu->current_element->prev_element == NULL) break;
          current_menu->current_element->is_active = false;
          current_menu->current_element = current_menu->current_element->prev_element;
          current_menu->current_element->is_active = true;
          write_lcd_menu(current_menu);
          update_input_event(IE_NO_EVENT);
        }
        break;
      case IE_ROTARY_ENC_RIGHT:
        if (current_menu->current_element->type == ME_LABEL &&
          current_menu->current_element->is_option_active) {
          if (current_menu->current_element->is_options_limit) {
            uint8_t new_value = current_menu->current_element->value + (uint8_t) atoi(current_menu->current_element->options[OPTION_STEP]);
            if (new_value > (uint8_t) atoi(current_menu->current_element->options[OPTION_END])) break;
            current_menu->current_element->value = new_value;
          } else {
            uint8_t new_option_indx = current_menu->current_element->option_indx + 1;
            if (new_option_indx == current_menu->current_element->option_length) 
              new_option_indx = current_menu->current_element->option_length - 1;
            current_menu->current_element->option_indx = new_option_indx;
          }
          write_lcd_menu(current_menu);
          update_input_event(IE_NO_EVENT);
        } else {
          if (current_menu->current_element->next_element == NULL) break;
          current_menu->current_element->is_active = false;
          current_menu->current_element = current_menu->current_element->next_element;
          current_menu->current_element->is_active = true;
          write_lcd_menu(current_menu);
          update_input_event(IE_NO_EVENT);
        }
        break;
    }
  }
}
