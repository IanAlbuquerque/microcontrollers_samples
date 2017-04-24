#include "lcd.h"

void LCD_display(char* string)
{
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  Lcd_Out(1,1,string);
  //Lcd_Cmd(_LCD_SHIFT_LEFT);
}

void LCD_setup()
{
  Lcd_Init();
}
