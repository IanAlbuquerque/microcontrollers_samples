#include "sevenseg.h"

#define SEVENSEG_EMPTY_CODE 0

#define SEVENSEG_A 0;
#define SEVENSEG_B 1;
#define SEVENSEG_C 2;
#define SEVENSEG_D 3;
#define SEVENSEG_E 4;
#define SEVENSEG_F 5;
#define SEVENSEG_G 6;
#define SEVENSEG_DOT 7;

#define SEVENSEG_HAS_DOT 1
#define SEVENSEG_HAS_NOT_DOT 0

extern sfr sbit SEG_A;
extern sfr sbit SEG_B;
extern sfr sbit SEG_C;
extern sfr sbit SEG_D;
extern sfr sbit SEG_E;
extern sfr sbit SEG_F;
extern sfr sbit SEG_G;
extern sfr sbit SEG_DOT;

extern sfr sbit CTRL_1;
extern sfr sbit CTRL_2;
extern sfr sbit CTRL_3;
extern sfr sbit CTRL_4;

extern sfr sbit SEG_A_Direction;
extern sfr sbit SEG_B_Direction;
extern sfr sbit SEG_C_Direction;
extern sfr sbit SEG_D_Direction;
extern sfr sbit SEG_E_Direction;
extern sfr sbit SEG_F_Direction;
extern sfr sbit SEG_G_Direction;
extern sfr sbit SEG_DOT_Direction;

extern sfr sbit CTRL_1_Direction;
extern sfr sbit CTRL_2_Direction;
extern sfr sbit CTRL_3_Direction;
extern sfr sbit CTRL_4_Direction;

char _display_codes[4];
int _sevenseg_type = SEVENSEG_CATHODE;
int _current_active_display = 0;

void SEVENSEG_cycleDisplay()
{
  switch(_current_active_display)
  {
    case 0:
      CTRL_1 = 1;
      CTRL_2 = 0;
      CTRL_3 = 0;
      CTRL_4 = 0;
      break;
    case 1:
      CTRL_1 = 0;
      CTRL_2 = 1;
      CTRL_3 = 0;
      CTRL_4 = 0;
      break;
    case 2:
      CTRL_1 = 0;
      CTRL_2 = 0;
      CTRL_3 = 1;
      CTRL_4 = 0;
      break;
    case 3:
      CTRL_1 = 0;
      CTRL_2 = 0;
      CTRL_3 = 0;
      CTRL_4 = 1;
      break;
  }
  SEG_A = (_display_codes[_current_active_display] & ( 0x1 << 0 )) >> 0;
  SEG_B = (_display_codes[_current_active_display] & ( 0x1 << 1 )) >> 1;
  SEG_C = (_display_codes[_current_active_display] & ( 0x1 << 2 )) >> 2;
  SEG_D = (_display_codes[_current_active_display] & ( 0x1 << 3 )) >> 3;
  SEG_E = (_display_codes[_current_active_display] & ( 0x1 << 4 )) >> 4;
  SEG_F = (_display_codes[_current_active_display] & ( 0x1 << 5 )) >> 5;
  SEG_G = (_display_codes[_current_active_display] & ( 0x1 << 6 )) >> 6;
  SEG_DOT = (_display_codes[_current_active_display] & ( 0x1 << 7 )) >> 7;

  _current_active_display += 1;
  if(_current_active_display > 3)
  {
    _current_active_display = 0;
  }
}

void SEVENSEG_setDisplayFromNumber(int x)
{
  SEVENSEG_setSegment(0,SEVENSEG_getCodeFromInt((x/1000)%10,SEVENSEG_HAS_NOT_DOT));
  SEVENSEG_setSegment(1,SEVENSEG_getCodeFromInt((x/100)%10,SEVENSEG_HAS_NOT_DOT));
  SEVENSEG_setSegment(2,SEVENSEG_getCodeFromInt((x/10)%10,SEVENSEG_HAS_NOT_DOT));
  SEVENSEG_setSegment(3,SEVENSEG_getCodeFromInt((x)%10,SEVENSEG_HAS_NOT_DOT));
}

void SEVENSEG_setDisplayFromNumberString(char* number_str)
{
  int i=0;
  int current_segment = 0;
  while(number_str[i] != '\0' && current_segment<=3)
  {
    if(number_str[i]=='.')
    {
      SEVENSEG_setSegment(current_segment,SEVENSEG_getCodeFromInt(-1,SEVENSEG_HAS_DOT));
      current_segment += 1;
    }
    else if(number_str[i]>='0' && number_str[i]<='9')
    {
      if(number_str[i+1] == '.')
      {
        SEVENSEG_setSegment(current_segment,SEVENSEG_getCodeFromInt(number_str[i] - '0',SEVENSEG_HAS_DOT));
      }
      else
      {
        SEVENSEG_setSegment(current_segment,SEVENSEG_getCodeFromInt(number_str[i] - '0',SEVENSEG_HAS_NOT_DOT));
      }
      current_segment += 1;
    }
    i++;
  }
}

char SEVENSEG_getCodeFromInt(int x, int has_dot)
{
  char dot_mask;

  dot_mask = has_dot?0x80:0x00;

  if(_sevenseg_type == SEVENSEG_CATHODE)
  {
    switch(x)
    {
      case -1:
        return 0x00 | dot_mask;
      case 0:
        return 0x3F | dot_mask;
      case 1:
        return 0x06 | dot_mask;
      case 2:
        return 0x5B | dot_mask;
      case 3:
        return 0x4F | dot_mask;
      case 4:
        return 0x66 | dot_mask;
      case 5:
        return 0x6D | dot_mask;
      case 6:
        return 0x7D | dot_mask;
      case 7:
        return 0x07 | dot_mask;
      case 8:
        return 0x7F | dot_mask;
      case 9:
        return 0x6F | dot_mask;
      default:
        return SEVENSEG_EMPTY_CODE;
    }
  }
  else
  {
    switch(x)
    {
      case -1:
        return 0x00 | dot_mask;
      case 0:
        return 0xC0 | dot_mask;
      case 1:
        return 0xF9 | dot_mask;
      case 2:
        return 0xA4 | dot_mask;
      case 3:
        return 0xB0 | dot_mask;
      case 4:
        return 0x99 | dot_mask;
      case 5:
        return 0x92 | dot_mask;
      case 6:
        return 0x82 | dot_mask;
      case 7:
        return 0xF8 | dot_mask;
      case 8:
        return 0x80 | dot_mask;
      case 9:
        return 0x90 | dot_mask;
      default:
        return SEVENSEG_EMPTY_CODE;
    }
  }
}

void SEVENSEG_setDisplayClear()
{
  _display_codes[0] = SEVENSEG_EMPTY_CODE;
  _display_codes[1] = SEVENSEG_EMPTY_CODE;
  _display_codes[2] = SEVENSEG_EMPTY_CODE;
  _display_codes[3] = SEVENSEG_EMPTY_CODE;
}

void SEVENSEG_setSegment(int segment_being_set, char given_code)
{
  if(segment_being_set >= 0 && segment_being_set <= 3)
  {
    _display_codes[segment_being_set] = given_code;
  }
}

void SEVENSEG_setup(int sevenseg_type)
{
  _sevenseg_type = sevenseg_type;

  SEG_A_Direction = 0;
  SEG_B_Direction = 0;
  SEG_C_Direction = 0;
  SEG_D_Direction = 0;
  SEG_E_Direction = 0;
  SEG_F_Direction = 0;
  SEG_G_Direction = 0;
  SEG_DOT_Direction = 0;

  CTRL_1_Direction = 0;
  CTRL_2_Direction = 0;
  CTRL_3_Direction = 0;
  CTRL_4_Direction = 0;

  CTRL_1 = 1;
  CTRL_2 = 1;
  CTRL_3 = 1;
  CTRL_4 = 1;

  SEG_A = 0;
  SEG_B = 0;
  SEG_C = 0;
  SEG_D = 0;
  SEG_E = 0;
  SEG_F = 0;
  SEG_G = 0;
  SEG_DOT = 0;

  SEVENSEG_setDisplayClear();
}
