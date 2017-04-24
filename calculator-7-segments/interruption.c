#include "interruption.h"

void (*_RB_FUNCTION)(char);
int _IS_RB_ENABLED = 0;

void (*_TIMER0_FUNCTION)(void);
int _IS_TIMER0_ENABLED = 0;
int _TIMER0_TICKS = 0;
int _TIMER0_IS_REPEATABLE = 0;

static char INTERRUPTION_getStateRB()
{
  char value = 0x00;
  value = value | (PORTB.RB4 << 0);
  value = value | (PORTB.RB5 << 1);
  value = value | (PORTB.RB6 << 2);
  value = value | (PORTB.RB7 << 3);
  return value;
}

void interrupt()
{
  volatile char parameter_char = 0;

  if(_IS_RB_ENABLED && INTCON.RBIF)
  {
    INTCON.RBIF = 0;
    parameter_char = INTERRUPTION_getStateRB();
    _RB_FUNCTION(parameter_char);
  }
  if(_IS_TIMER0_ENABLED && INTCON.TMR0IF)
  {
    INTCON.TMR0IF = 0;

    if(_TIMER0_IS_REPEATABLE)
    {
      INTERRUPTION_startTimer0();
    }
    else
    {
      INTERRUPTION_stopTimer0();
    }

    _TIMER0_FUNCTION();
  }
}

void INTERRUPTION_setup()
{
  // global interruptions enable bit
  INTCON.GIE = 1;
  // peripheral interruption enable bit
  INTCON.PEIE = 0;
}

void INTERRUPTION_setupRB(void (*rb_function)(char))
{
  _RB_FUNCTION = rb_function;

  // priority bit
  INTCON2.RBIP = 1;
  // flag bit
  INTCON.RBIF = 0;
}

void INTERRUPTION_enableRB()
{
  _IS_RB_ENABLED = 1;
  // enable bit
  INTCON.RBIE = 1;
  // flag bit
  INTCON.RBIF = 0;
}

void INTERRUPTION_disableRB()
{
  _IS_RB_ENABLED = 0;
  // enable bit
  INTCON.RBIE = 0;
  // flag bit
  INTCON.RBIF = 0;
}

void INTERRUPTION_setupTimer0(  void (*timer0_function)(void),
                                int prescaler,
                                int ticks,
                                int is_repeatable)
{
  _TIMER0_FUNCTION = timer0_function;

  // priority bit
  INTCON2.TMR0IP = 1;
  // flag bit
  INTCON.TMR0IF = 0;

  // clock source bit (0 = CLKO)
  T0CS_bit = 0;
  // 16 bits
  T0CON.T08BIT = 0;

  // internal clock
  T0CON.CS = 0;

  if(prescaler == INTERRUPTION_TIMER0_PRESCALER_1)
  {
    // prescaler assignment bit (0 = prescaler assigned)
    PSA_bit = 1;
  }
  else
  {
    // prescaler assignment bit (0 = prescaler assigned)
    PSA_bit = 0;

    T0PS0_bit = (prescaler & 0x1) >> 0;
    T0PS1_bit = (prescaler & 0x2) >> 1;
    T0PS2_bit = (prescaler & 0x4) >> 2;
  }

  _TIMER0_TICKS = ticks;
  _TIMER0_IS_REPEATABLE = is_repeatable;
}

void INTERRUPTION_resetTimer0()
{
  TMR0H = (0xffff - _TIMER0_TICKS) >> 8;
  TMR0L = (0xffff - _TIMER0_TICKS);
}

void INTERRUPTION_resumeTimer0()
{
  _IS_TIMER0_ENABLED = 1;

  // enable bit
  TMR0IE_bit = 1;
  // flag bit
  INTCON.TMR0IF = 0;
  // start timer0
  T0CON.TMR0ON = 1;  
}

void INTERRUPTION_startTimer0()
{
  INTERRUPTION_resetTimer0(); 
  INTERRUPTION_resumeTimer0();
}

void INTERRUPTION_stopTimer0()
{
  _IS_TIMER0_ENABLED = 0;
  // enable bit
  TMR0IE_bit = 0;
  // flag bit
  INTCON.TMR0IF = 0;
}