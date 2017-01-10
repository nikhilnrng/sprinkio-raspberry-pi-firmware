#include "../../sprinkio.h"

int main () {
  uart_init();
  system_init();
  lcd_init();

  lcd_command(LCD_LINE_1_COL_1);
  write_lcd_s("Hello World\0");
  lcd_command(LCD_LINE_1_COL_1);
  write_lcd_s("Goodbye\0");

  return 0;
}
