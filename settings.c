#include "sprinkio.h"

uint8_t dow;
sptime_t sptime;
spdate_t date;
spzone_t zone;
spmode_t mode;

extern struct menu_element mm_zone_status, mm_setup_zone, mm_network_settings, mm_manual_zone_control, mm_setup_mode;
extern struct menu_element sz_zone_number, sz_days_of_week, sz_start_time, sz_duration, sz_moisture_sensor, sz_back, sz_action;
extern struct menu_element sdow_sunday, sdow_monday, sdow_tuesday, sdow_wednesday, sdow_thursday, sdow_friday, sdow_saturday, sdow_back, sdow_action;
extern struct menu_element st_hour, st_minute, st_second, st_back, st_action;
extern struct menu_element ns_status, ns_ip_address, ns_back;
extern struct menu_element mzc_zone_1, mzc_zone_2, mzc_zone_3, mzc_zone_4, mzc_zone_5, mzc_zone_6, mzc_zone_7, mzc_zone_8, mzc_back, mzc_action;
extern struct menu_element sm_water_saver, sm_back, sm_action;

static void print_dow(uint8_t dow) {
  printf("Days of week: ");
  char str[9];
  int i;
  for (i = 0; i < 8; i++) {
      sprintf(&str[i], "%d", !!((dow << i) & 0x80));
  }
  printf(str);
  printf("\n");
}

static void print_zone_num(uint8_t z) {
  printf("Zone: ");
  char str[9];
  int i;
  for (i = 0; i < 8; i++) {
      sprintf(&str[i], "%d", !!((z << i) & 0x80));
  }
  printf(str);
  printf("\n");
}

static void print_time(sptime_t* time) {
  printf("Time:\n");
  printf("Hour: %d\n", time->hour);
  printf("Minute: %d\n", time->minute);
  printf("Second: %d\n", time->second);
}

static void print_zone(spzone_t* zone) {
  print_zone_num(zone->num);
  print_dow(zone->days_of_week);
  printf("Duration: %d\n", zone->duration);
  printf("Moisture Sensor: %d\n", zone->moisture_sensor);
  print_time(&(zone->start_time));
}

void compile_zone() {
  zone.num = BIT(sz_zone_number.value - 1);
  zone.days_of_week = dow;
  zone.duration = sz_duration.value;
  if (sz_moisture_sensor.option_indx == OPTION_YES) zone.moisture_sensor = true;
  else zone.moisture_sensor = false;
  zone.start_time = sptime;
  print_zone(&zone);
  send_zone_settings();
}

void compile_days_of_week() {
  dow = 0x00;
  if (sdow_sunday.option_indx == OPTION_ON) dow |= SUNDAY;
  if (sdow_monday.option_indx == OPTION_ON) dow |= MONDAY;
  if (sdow_tuesday.option_indx == OPTION_ON) dow |= TUESDAY;
  if (sdow_wednesday.option_indx == OPTION_ON) dow |= WEDNESDAY;
  if (sdow_thursday.option_indx == OPTION_ON) dow |= THURSDAY;
  if (sdow_friday.option_indx == OPTION_ON) dow |= FRIDAY;
  if (sdow_saturday.option_indx == OPTION_ON) dow |= SATURDAY;
  print_dow(dow);
}

void compile_time() {
  sptime.hour = st_hour.value;
  sptime.minute = st_minute.value;
  sptime.second = st_second.value;

  print_time(&sptime);
}

void compile_zone_control() {
  if (mzc_zone_1.option_indx == OPTION_ON) send_zone_control(CMD_RUN_ZONE_1);
  else send_zone_control(CMD_STOP_ZONE_1);
  if (mzc_zone_2.option_indx == OPTION_ON) send_zone_control(CMD_RUN_ZONE_2);
  else send_zone_control(CMD_STOP_ZONE_2);
  if (mzc_zone_3.option_indx == OPTION_ON) send_zone_control(CMD_RUN_ZONE_3);
  else send_zone_control(CMD_STOP_ZONE_3);
  if (mzc_zone_4.option_indx == OPTION_ON) send_zone_control(CMD_RUN_ZONE_4);
  else send_zone_control(CMD_STOP_ZONE_4);
  if (mzc_zone_5.option_indx == OPTION_ON) send_zone_control(CMD_RUN_ZONE_5);
  else send_zone_control(CMD_STOP_ZONE_5);
  if (mzc_zone_6.option_indx == OPTION_ON) send_zone_control(CMD_RUN_ZONE_6);
  else send_zone_control(CMD_STOP_ZONE_6);
  if (mzc_zone_7.option_indx == OPTION_ON) send_zone_control(CMD_RUN_ZONE_7);
  else send_zone_control(CMD_STOP_ZONE_7);
  if (mzc_zone_8.option_indx == OPTION_ON) send_zone_control(CMD_RUN_ZONE_8);
  else send_zone_control(CMD_STOP_ZONE_8);

  printf("zone control compiling\n");
}

void compile_mode() {

  printf("mode compiling\n");
}

void send_zone_settings() {
  printf("Sending zone setup information...\n");

  write_atmel(CMD_SETUP_MODE);
  write_atmel(CMD_SETUP_ZONE);
  write_atmel(CMD_ZONE_NUM);
  write_atmel(zone.num);
  write_atmel(CMD_ZONE_DAYS_OF_WEEK);
  write_atmel(zone.days_of_week);
  write_atmel(CMD_ZONE_DURATION);
  write_atmel(zone.duration);
  write_atmel(CMD_ZONE_MOISTURE_SENSOR);
  write_atmel(zone.moisture_sensor);

  write_atmel(CMD_ZONE_TIME);
  write_atmel(CMD_TIME_SECOND);
  write_atmel(sptime.second);
  write_atmel(CMD_TIME_MINUTE);
  write_atmel(sptime.minute);
  write_atmel(CMD_TIME_HOUR);
  write_atmel(sptime.hour);
  write_atmel(CMD_TIME_END);


  write_atmel(CMD_ZONE_END);

  printf("Zone setup information sent...\n");
}

void send_zone_control(uint8_t zone) {
  write_atmel(CMD_UPDATE_ZONE);
  write_atmel(zone);
}

void send_current_time() {
  printf("Compiling time setup information...\n");

  get_time(&sptime);
  print_time(&sptime);

  printf("Sending time setup information...\n");
  write_atmel(CMD_SETUP_MODE);
  write_atmel(CMD_SETUP_TIME);
  write_atmel(CMD_TIME_SECOND);
  write_atmel(sptime.second);
  write_atmel(CMD_TIME_MINUTE);
  write_atmel(sptime.minute);
  write_atmel(CMD_TIME_HOUR);
  write_atmel(sptime.hour);
  write_atmel(CMD_TIME_END);

  printf("Time setup information sent...\n");
}
