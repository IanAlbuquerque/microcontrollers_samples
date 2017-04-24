#include "lcd.h"
#include "keyboard.h"
#include "interruption.h"
#include "sevenseg.h"

#define USING_LCD

#ifndef USING_LCD
  // SEVEN SEG CONNECTIONS
  sbit SEG_A at RD0_bit;
  sbit SEG_B at RD1_bit;
  sbit SEG_C at RD2_bit;
  sbit SEG_D at RD3_bit;
  sbit SEG_E at RD4_bit;
  sbit SEG_F at RD5_bit;
  sbit SEG_G at RD6_bit;
  sbit SEG_DOT at RD7_bit;

  sbit CTRL_1 at RA2_bit;
  sbit CTRL_2 at RA3_bit;
  sbit CTRL_3 at RA1_bit;
  sbit CTRL_4 at RA5_bit;

  sbit SEG_A_Direction at TRISD0_bit;
  sbit SEG_B_Direction at TRISD1_bit;
  sbit SEG_C_Direction at TRISD2_bit;
  sbit SEG_D_Direction at TRISD3_bit;
  sbit SEG_E_Direction at TRISD4_bit;
  sbit SEG_F_Direction at TRISD5_bit;
  sbit SEG_G_Direction at TRISD6_bit;
  sbit SEG_DOT_Direction at TRISD7_bit;

  sbit CTRL_1_Direction at TRISA2_bit;
  sbit CTRL_2_Direction at TRISA3_bit;
  sbit CTRL_3_Direction at TRISA1_bit;
  sbit CTRL_4_Direction at TRISA5_bit;
#else
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
#endif

// KEYBOARD CONNECTIONS
sbit COL_1 at RB0_bit;
sbit COL_2 at RB1_bit;
sbit COL_3 at RB2_bit;
sbit COL_4 at RB3_bit;

sbit ROW_1 at RB4_bit;
sbit ROW_2 at RB5_bit;
sbit ROW_3 at RB6_bit;
sbit ROW_4 at RB7_bit;

sbit COL_1_Direction at TRISB0_bit;
sbit COL_2_Direction at TRISB1_bit;
sbit COL_3_Direction at TRISB2_bit;
sbit COL_4_Direction at TRISB3_bit;

sbit ROW_1_Direction at TRISB4_bit;
sbit ROW_2_Direction at TRISB5_bit;
sbit ROW_3_Direction at TRISB6_bit;
sbit ROW_4_Direction at TRISB7_bit;


char keyboard_mapping[4][4] = {
                                {'1','2','3','+'},
                                {'4','5','6','-'},
                                {'7','8','9','*'},
                                {'C','0','=','/'}
                              };

 int x=0;
 int y=0;
 char calculator_operation = '+';                             

#ifdef USING_LCD
  void displayNumberOnLCD()
  {
    char str[5];
    str[0] = (x/1000)%10 + '0';
    str[1] = (x/100)%10 + '0';
    str[2] = (x/10)%10 + '0';
    str[3] = (x/1)%10 + '0';
    str[4] = '\0';
    LCD_display(str); 
  }
#endif

void processInputKey(char key_pressed)
{
   if(key_pressed == 'C')
  {
    x=0;
    y=0;
    #ifndef USING_LCD
      SEVENSEG_setDisplayClear();
    #endif
  }
  else if(key_pressed == '=')
  {
    switch(calculator_operation)
    {
      case '+':
        x = y + x;
        break;
      case '-':
        x = y - x;
        break;
      case '*':
        x = y * x;
        break;
      case '/':
        x = y / x;
        break;
    }
    SEVENSEG_setDisplayFromNumber(x);
  }
  else if(key_pressed == '+' || key_pressed == '-' || key_pressed == '*' || key_pressed == '/')
  {
    calculator_operation = key_pressed;
    y = x;
    x = 0;
    #ifndef USING_LCD
      SEVENSEG_setDisplayClear();
    #endif
  }
  else
  {
    x *= 10;
    x += key_pressed - '0';
    SEVENSEG_setDisplayFromNumber(x);
  }
}

void interruptionButtonsChanged(char portb_values)
{
  char key_pressed;

  if(portb_values != 0x0)
  {
    INTERRUPTION_disableRB();
    key_pressed = KEYBOARD_getKeyPressed();
    processInputKey(key_pressed);
    INTERRUPTION_enableRB();
  }
}

int main()
{
  ADCON1 = 0x06;

  KEYBOARD_setup(KEYBOARD_WRITE_COLS_READ_ROWS);
  KEYBOARD_setKeyMapping(keyboard_mapping);
  INTERRUPTION_setup();
  INTERRUPTION_setupRB(interruptionButtonsChanged);
  INTERRUPTION_enableRB();

  #ifndef USING_LCD
    SEVENSEG_setup(SEVENSEG_CATHODE);
    INTERRUPTION_setupTimer0( SEVENSEG_cycleDisplay,
                              INTERRUPTION_TIMER0_PRESCALER_256,
                              781,
                              INTERRUPTION_TIMER0_REPEAT);
  #else
    LCD_setup();
    INTERRUPTION_setupTimer0( displayNumberOnLCD,
                              INTERRUPTION_TIMER0_PRESCALER_256,
                              781,
                              INTERRUPTION_TIMER0_REPEAT); 
  #endif


  INTERRUPTION_startTimer0();
  
  return 0;
}