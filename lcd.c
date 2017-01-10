#include "sprinkio.h"

/**
 * Write a pointer character to the LCD
 */
static void write_pointer() {
  write_lcd('>');
}

/**
 * Write a space character to the LCD
 */
static void write_space() {
  write_lcd(' ');
}

/**
 * Write a colon character to the LCD
 */
static void write_colon() {
  write_lcd(':');
  write_space();
}

void lcd_init() {
  lcd_command(LCD_DISPLAY_ON);
  lcd_command(LCD_CLEAR_SCREEN);
}

/**
 * Write any byte to the LCD
 */
void write_lcd(uint8_t data) {
  UART_SELECT_EN();
  UART_LCD_EN();
  uart_write(data);
  // UART_ATMEL_EN();
}

/** 
 * Write a string to the LCD
 */
void write_lcd_s(const char *s) {
  uint16_t indx = 0;
  // add string to buffer
  while (indx < strlen((char *) s)) {
    write_lcd((uint8_t) s[indx++]);
  }
}

/**
 * Write a menu to the LCD
 */
void write_lcd_menu(struct menu* m) {
  lcd_clear_menu();
  lcd_set_cursor_row(1);
  write_lcd_s(m->title); // menu title always 20 characters
  uint8_t line = 2;
  struct menu_element* mep = m->current_element;
  while (mep != NULL && line <= 4) {
    // set cursor position
    lcd_set_cursor_row(line);
    
    // write pointer if element is active
    if (mep->is_active) write_pointer();
    else write_space();

    // write menu element text
    write_lcd_s(mep->text); 

    // write label elements if applicable
    if (mep->type == ME_LABEL) {
      write_colon();
      if (mep->is_options_limit) {
        char str_val[2];
        sprintf(str_val, "%d", mep->value);
        printf("Value: %d\n", mep->value);
        write_lcd_s(str_val);
      } else {
        write_lcd_s(mep->options[mep->option_indx]);
      }
    }

    // write display elements if applicable
    if (mep->type == ME_DISPLAY) {
      write_colon();
      write_lcd_s(mep->options[mep->option_indx]);
    }
    
    // increment menu element pointer and line
    mep = mep->next_element;

    line++;
  }
  // UART_ATMEL_EN();
}

/**
 * Write a command to the LCD
 */
void lcd_command(uint8_t cmd) {
  write_lcd(LCD_COMMAND_PREFIX);
  write_lcd(cmd);
  delay(2);
}

/**
 * Set LCD cursor to the start of the given row
 */
void lcd_set_cursor_row(uint8_t row) {
  lcd_command(LCD_SET_CURSOR);
  if (row == 1) write_lcd(LCD_POS_START_LINE_1);
  else if (row == 2) write_lcd(LCD_POS_START_LINE_2);
  else if (row == 3) write_lcd(LCD_POS_START_LINE_3);
  else write_lcd(LCD_POS_START_LINE_4);
  delay(1);
}

/**
 * Clear menu currently printed on LCD
 */
void lcd_clear_menu() {
  lcd_command(LCD_CLEAR_SCREEN);
}
