#include "lcd.h"
#include "keyboard.h"

// LCD Connections
sbit LCD_EN at RE0_bit;
sbit LCD_RS at RE1_bit;

sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_EN_Direction at TRISE0_bit;
sbit LCD_RS_Direction at TRISE1_bit;

sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

// KEYBOARD CONNECTIONS
sbit COL_1 at RB0_bit;
sbit COL_2 at RB1_bit;
sbit COL_3 at RB2_bit;
sbit COL_4 at RB3_bit;

sbit ROW_1 at RB4_bit;
sbit ROW_2 at RB5_bit;
sbit ROW_3 at RB6_bit;
sbit ROW_4 at RB7_bit;

int main()
{
  char str[2] = "";
  // Config for ADCON1 = 0x05
  // AN7 = D
  // AN6 = D
  // AN5 = D
  // AN4 = D
  // AN3 = VREF+
  // AN2 = D
  // AN1 = A
  // AN0 = A
  // VREF+ = AN3
  // VREF- = VSS
  // C/R = 2/1
  ADCON1 = 0x06;

  TRISB = 0xF0;
  TRISE = 0x00;
  TRISD = 0x00;

  LCD_setup();
  KEYBOARD_setup();

  LCD_display("starting...");
  delay_ms(2000);
  while(1) 
  {
    str[0] = KEYBOARD_getKeyPressed();
    LCD_display(str);
    delay_ms(100);
  }

}