#ifndef SETTINGS_H
#define SETTINGS_H

#include "sprinkio.h"

// USART command characters
#define CMD_SETUP_MODE '~'
#define CMD_SENSOR_STATUS '?'
#define CMD_UPDATE_ZONE '!'
#define CMD_NO_ACTION 0xFF

// setup command modes
#define CMD_SETUP_TIME 0x01 // enter setup time mode
#define CMD_SETUP_DATE 0x02 // enter setup date mode
#define CMD_SETUP_ZONE 0x03 // enter setup zone mode
#define CMD_SETUP_WATER_MODE 0x04 // enter setup water mode
#define CMD_SETUP_START 0x05 // enter setup mode started
#define CMD_SETUP_END 0x06 // setup mode ended
#define CMD_SETUP_ERROR 0x07 // unrecognized command

// setup time commands
#define CMD_TIME_SECOND 0x11 // receive seconds
#define CMD_TIME_MINUTE 0x12 // receive minutes
#define CMD_TIME_HOUR 0x13 // receive hours
#define CMD_TIME_START 0x14 // setup time started
#define CMD_TIME_END 0x15 // setup time ended
#define CMD_TIME_VALID 0x16 // time valid
#define CMD_TIME_INVALID 0x17 // time invalid
#define CMD_TIME_ERROR 0x18 // unrecognized command

// setup date commands
#define CMD_DATE_DAY 0x21 // receive day
#define CMD_DATE_MONTH 0x22 // receive month
#define CMD_DATE_YEAR 0x23 // receive year
#define CMD_DATE_START 0x24 // setup date started
#define CMD_DATE_END 0x25 // setup date ended
#define CMD_DATE_VALID 0x26 // date valid
#define CMD_DATE_INVALID 0x27 // date invalid
#define CMD_DATE_ERROR 0x28 // uncrecognized command

// setup zone commands
#define CMD_ZONE_NUM 0x31 // receive zone number
#define CMD_ZONE_DAYS_OF_WEEK 0x32 // receive watering days
#define CMD_ZONE_DURATION 0x33 // receive watering duration
#define CMD_ZONE_MOISTURE_SENSOR 0x34 // receive moisture sensor boolean
#define CMD_ZONE_TIME 0x35 // receive watering start time
#define CMD_ZONE_START 0x36 // setup zone started
#define CMD_ZONE_END 0x37 // setup zone ended
#define CMD_ZONE_VALID 0x38 // zone valid
#define CMD_ZONE_INVALID 0x39 // zone invalid
#define CMD_ZONE_ERROR 0x40 // unrecognized command

// setup mode commands
#define CMD_MODE_WATER_SAVE 0x41 // receive water save mode boolean
#define CMD_MODE_START 0x42 // setup mode started
#define CMD_MODE_END 0x43 // setup mode ended
#define CMD_MODE_VALID 0x44 // mode valid
#define CMD_MODE_INVALID 0x45 // mode invalid
#define CMD_MODE_ERROR 0x46 // unrecognized command

// USART zone run codes
#define CMD_RUN_ZONE_1 0x01
#define CMD_RUN_ZONE_2 0x02
#define CMD_RUN_ZONE_3 0x03
#define CMD_RUN_ZONE_4 0x04
#define CMD_RUN_ZONE_5 0x05
#define CMD_RUN_ZONE_6 0x06
#define CMD_RUN_ZONE_7 0x07
#define CMD_RUN_ZONE_8 0x08

// USART zone stop codes
#define CMD_STOP_ZONE_1 0x11
#define CMD_STOP_ZONE_2 0x12
#define CMD_STOP_ZONE_3 0x13
#define CMD_STOP_ZONE_4 0x14
#define CMD_STOP_ZONE_5 0x15
#define CMD_STOP_ZONE_6 0x16
#define CMD_STOP_ZONE_7 0x17
#define CMD_STOP_ZONE_8 0x18

#define SUNDAY BIT(0)
#define MONDAY BIT(1)
#define TUESDAY BIT(2)
#define WEDNESDAY BIT(3)
#define THURSDAY BIT(4)
#define FRIDAY BIT(5)
#define SATURDAY BIT(6)

void compile_zone();
void compile_days_of_week();
void compile_time();
void compile_zone_control();
void compile_mode();
void send_zone_settings();
void send_zone_control(uint8_t zone);
void send_current_time();

#endif
