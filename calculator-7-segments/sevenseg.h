#define SEVENSEG_CATHODE 0
#define SEVENSEG_ANODE 1

void SEVENSEG_setDisplayFromNumber(int x);
void SEVENSEG_setDisplayFromNumberString(char* number_str);
char SEVENSEG_getCodeFromInt(int x, int has_dot);
void SEVENSEG_setDisplayClear();
void SEVENSEG_setSegment(int segment, char code);
void SEVENSEG_setup(int sevenseg_type);
void SEVENSEG_cycleDisplay();