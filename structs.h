#ifndef STRUCTS_H
#define STRUCTS_H

#include "sprinkio.h"

typedef struct {
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
} sptime_t;

typedef struct {
  uint8_t day_of_week; // current day of week
  uint8_t day;
  uint8_t month;
  uint8_t year;
} spdate_t;

typedef struct {
  uint8_t num; // zone number bit field
  uint8_t days_of_week; // days of week bit field
  uint8_t duration; // decimal duration
  bool moisture_sensor; // moisture sensor available
  sptime_t start_time; // zone start time
} spzone_t;

typedef bool spmode_t;

struct menu_element {
  const char* text;
  uint8_t type;
  bool is_active;
  uint8_t value;
  const char** options;
  uint8_t option_indx;
  uint8_t option_length;
  bool is_options_limit; // options array describes option limits
  bool is_option_active;
  bool is_option_selected;
  struct menu* next_menu;
  struct menu_element* prev_element;
  struct menu_element* next_element;
};

struct menu {
  const char* title;
  void (*action)(void);
  struct menu_element* current_element;
};

#endif
