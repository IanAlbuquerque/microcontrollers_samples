#define KEYBOARD_WRITE_COLS_READ_ROWS 0
#define KEYBOARD_WRITE_ROWS_READ_COLS 1

void KEYBOARD_setup(int operation_mode);
void KEYBOARD_setKeyMapping(char key_mapping_4x4[][4]);
char KEYBOARD_getKeyPressed();