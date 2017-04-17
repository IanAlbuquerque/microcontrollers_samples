#include "lcd.h"
#include "keyboard.h"
#include "interruption.h"
#include "string.h"

#define KEY_BUFFER_SIZE 8
#define ACTIVATION_CODE "*2025*"
#define DEACTIVATION_CODE "+1830+"

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
                                {'C','0','E','/'}
                              };

char key_buffer[KEY_BUFFER_SIZE] = "";
int key_buffer_size=0;

int is_activated = 0;

void keyBufferPush(char c)
{
  if(key_buffer_size < KEY_BUFFER_SIZE-1)
  {
    key_buffer[key_buffer_size] = c;
    key_buffer[key_buffer_size+1] = '\0';
    key_buffer_size++;
  } 
  LCD_display(key_buffer);
}

void keyBufferClean()
{
  key_buffer[0] = '\0';
  key_buffer_size = 0; 
  LCD_display(key_buffer);
}

void processInputKey(char key_pressed)
{
   if(key_pressed == 'C')
  {
    keyBufferClean();
  }
  else if(key_pressed == 'E')
  {
    if(strcmp(key_buffer,ACTIVATION_CODE) == 0)
    {
      is_activated = 1;
      LCD_display("ACTIVATED");
    }
    else if(strcmp(key_buffer,DEACTIVATION_CODE) == 0)
    {
      is_activated = 0;
      LCD_display("DEACTIVATED");
    }
    else
    {
      LCD_display("FAILURE");
    }
    INTERRUPTION_setupTimer0( keyBufferClean,
                              INTERRUPTION_TIMER0_PRESCALER_256,
                              7812,
                              INTERRUPTION_TIMER0_ONE_TIME);
    INTERRUPTION_startTimer0();
  }
  else
  {
    keyBufferPush(key_pressed);
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
  // Config for ADCON1 = 0x04
  // AN7 = D
  // AN6 = D
  // AN5 = D
  // AN4 = D
  // AN3 = A
  // AN2 = D
  // AN1 = A
  // AN0 = A
  // VREF+ = VDD
  // VREF- = VSS
  // C/R = 3/1
  ADCON1 = 0x04;

  // digital sensors input
  TRISC0_bit = 1;
  TRISC1_bit = 1;
  TRISC2_bit = 1;
  TRISC3_bit = 1;

  // analog sensors input
  TRISA0_bit = 1;
  TRISA1_bit = 1;

  LCD_setup();
  KEYBOARD_setup(KEYBOARD_WRITE_COLS_READ_ROWS);
  KEYBOARD_setKeyMapping(keyboard_mapping);
  INTERRUPTION_setup();
  INTERRUPTION_setupRB(interruptionButtonsChanged);
  INTERRUPTION_enableRB();

  while(1)
  {
    if(is_activated)
    {
      int num_sensors_activated;
      num_sensors_activated = (int) PORTC.RC0 + (int) PORTC.RC1 + (int) PORTC.RC2 + (int) PORTC.RC3;
      if(num_sensors_activated >= 2)
      {
        key_buffer[0] = 'A';
        key_buffer[1] = '\0';
        key_buffer_size=1;
      }
      else if(num_sensors_activated==1)
      {
        key_buffer[0] = 'B';
        key_buffer[1] = '\0';
        key_buffer_size=1;
      }
    }
  }
  
  return 0;
}