#include "keyboard.h"

extern sfr sbit COL_1;
extern sfr sbit COL_2;
extern sfr sbit COL_3;
extern sfr sbit COL_4;

extern sfr sbit ROW_1;
extern sfr sbit ROW_2;
extern sfr sbit ROW_3;
extern sfr sbit ROW_4;

extern sfr sbit COL_1_Direction;
extern sfr sbit COL_2_Direction;
extern sfr sbit COL_3_Direction;
extern sfr sbit COL_4_Direction;

extern sfr sbit ROW_1_Direction;
extern sfr sbit ROW_2_Direction;
extern sfr sbit ROW_3_Direction;
extern sfr sbit ROW_4_Direction;


int _OPERATION_MODE = KEYBOARD_WRITE_COLS_READ_ROWS;

char _KEYBOARD_MAPPING[4][4] = {
                                {'1','2','3','A'},
                                {'4','5','6','B'},
                                {'7','8','9','C'},
                                {'*','0','#','D'}
                              };

static void KEYBOARD_setCols(char value)
{
  COL_1 = (value & 0x1) >> 0;
  COL_2 = (value & 0x2) >> 1;
  COL_3 = (value & 0x4) >> 2;
  COL_4 = (value & 0x8) >> 3;
}

static void KEYBOARD_setRows(char value)
{
  ROW_1 = (value & 0x1) >> 0;
  ROW_2 = (value & 0x2) >> 1;
  ROW_3 = (value & 0x4) >> 2;
  ROW_4 = (value & 0x8) >> 3;
}

static char KEYBOARD_getRows()
{
  char value = 0x00;
  value = value | (ROW_1 << 0);
  value = value | (ROW_2 << 1);
  value = value | (ROW_3 << 2);
  value = value | (ROW_4 << 3);
  return value;
}

static char KEYBOARD_getCols()
{
  char value = 0x00;
  value = value | (COL_1 << 0);
  value = value | (COL_2 << 1);
  value = value | (COL_3 << 2);
  value = value | (COL_4 << 3);
  return value;
}

static int KEYBOARD_toIndex(char state)
{
  switch(state)
  {
    case 0x01:
      return 0;
      break;
    case 0x02:
      return 1;
      break;
    case 0x04:
      return 2;
      break;
    case 0x08:
      return 3;
      break;
  }
  return -1;
}

static char KEYBOARD_getKeyPressedInCurrentConfig()
{
  char rows;
  char cols;
  int row_index;
  int col_index;

  rows = KEYBOARD_getRows();
  cols = KEYBOARD_getCols();
  row_index = KEYBOARD_toIndex(rows);
  col_index = KEYBOARD_toIndex(cols);

  if(col_index != -1 && row_index != -1)
  {
    return _KEYBOARD_MAPPING[row_index][col_index];
  }
  return 0x0;
}

static void KEYBOARD_setOut(char value)
{
  if(_OPERATION_MODE == KEYBOARD_WRITE_COLS_READ_ROWS)
  {
    KEYBOARD_setCols(value);
  }
  else
  {
    KEYBOARD_setRows(value);
  }
}

static void KEYBOARD_setOperationMode(int operation_mode)
{
  _OPERATION_MODE = operation_mode;
  if(_OPERATION_MODE == KEYBOARD_WRITE_COLS_READ_ROWS)
  {
    COL_1_Direction = 0;
    COL_2_Direction = 0;
    COL_3_Direction = 0;
    COL_4_Direction = 0;

    ROW_1_Direction = 1;
    ROW_2_Direction = 1;
    ROW_3_Direction = 1;
    ROW_4_Direction = 1;
  }
  else
  {
    COL_1_Direction = 1;
    COL_2_Direction = 1;
    COL_3_Direction = 1;
    COL_4_Direction = 1;

    ROW_1_Direction = 0;
    ROW_2_Direction = 0;
    ROW_3_Direction = 0;
    ROW_4_Direction = 0;
  }
}

void KEYBOARD_setup(int operation_mode)
{
  KEYBOARD_setOperationMode(operation_mode);
  if(_OPERATION_MODE == KEYBOARD_WRITE_COLS_READ_ROWS)
  {
    COL_1 = 1;
    COL_2 = 1;
    COL_3 = 1;
    COL_4 = 1;
  }
  else
  {
    ROW_1 = 1;
    ROW_2 = 1;
    ROW_3 = 1;
    ROW_4 = 1;
  }
}

void KEYBOARD_setKeyMapping(char key_mapping_4x4[][4])
{
  int i;
  int j;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      _KEYBOARD_MAPPING[i][j] = key_mapping_4x4[i][j];
    }
  }
}

char KEYBOARD_getKeyPressed()
{
  int i;
  char key;

  key = 0x0;
  for(i=0;i<4;i++)
  {
    KEYBOARD_setOut(1 << i);
    key += KEYBOARD_getKeyPressedInCurrentConfig();
  }
  KEYBOARD_setOut(0x0F);
  return key;
}