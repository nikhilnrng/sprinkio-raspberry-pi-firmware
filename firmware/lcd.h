#ifndef LCD_H
#define LCD_H

#include "sprinkio.h"

// LCD commands
#define LCD_COMMAND_PREFIX 0xFE
#define LCD_DISPLAY_ON 0x41
#define LCD_DISPLAY_OFF 0x42
#define LCD_SET_CURSOR 0x45
#define LCD_CURSOR_HOME 0x46
#define LCD_UNDERLINE_CURSOR_ON 0x47
#define LCD_UNDERLINE_CURSOR_OFF 0x48
#define LCD_MOVE_CURSOR_RIGHT 0x49
#define LCD_MOVE_CURSOR_LEFT 0x4A
#define LCD_BLINKING_CURSOR_ON 0x4B
#define LCD_BLINKING_CURSOR_OFF 0x4C
#define LCD_BACKSPACE 0x4E
#define LCD_CLEAR_SCREEN 0x51
#define LCD_SET_CONTRAST 0x52
#define LCD_SET_BACKLIGHT_BRIGHTNESS 0x53
#define LCD_LOAD_CUSTOM_CHARACTER 0x54
#define LCD_RIGHT_TO_LEFT 0x55
#define LCD_LEFT_TO_RIGHT 0x56

// LCD display positions
#define LCD_POS_START_LINE_1 0x00
#define LCD_POS_START_LINE_2 0x40
#define LCD_POS_START_LINE_3 0x14
#define LCD_POS_START_LINE_4 0x54
#define LCD_POS_START_LINE(N) LCD_POS_START_LINE_ ## N

#define LCD_POS_END_LINE_1 0x13
#define LCD_POS_END_LINE_2 0x53
#define LCD_POS_END_LINE_3 0x27
#define LCD_POS_END_LINE_4 0x67
#define LCD_POS_END_LINE(N) LCD_POS_END_LINE_ ## N

void lcd_init();
void write_lcd(uint8_t data);
void write_lcd_s(const char *s);
void write_lcd_menu(struct menu* m);
void lcd_command(uint8_t cmd);
void lcd_set_cursor_row(uint8_t row);
void lcd_clear_menu();

#endif
