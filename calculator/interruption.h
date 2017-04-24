#define INTERRUPTION_TIMER0_PRESCALER_256 0x7
#define INTERRUPTION_TIMER0_PRESCALER_128 0x6
#define INTERRUPTION_TIMER0_PRESCALER_64 0x5
#define INTERRUPTION_TIMER0_PRESCALER_32 0x4
#define INTERRUPTION_TIMER0_PRESCALER_16 0x3
#define INTERRUPTION_TIMER0_PRESCALER_8 0x2
#define INTERRUPTION_TIMER0_PRESCALER_4 0x1
#define INTERRUPTION_TIMER0_PRESCALER_2 0x0
#define INTERRUPTION_TIMER0_PRESCALER_1 -1

#define INTERRUPTION_TIMER0_ONE_TIME 0
#define INTERRUPTION_TIMER0_REPEAT 1

void INTERRUPTION_setup();

void INTERRUPTION_setupRB(void (*rb_function)(char));
void INTERRUPTION_enableRB();
void INTERRUPTION_disableRB();

void INTERRUPTION_setupTimer0(  void (*timer0_function)(void),
                                int prescaler,
                                int ticks,
                                int is_repeatable);
void INTERRUPTION_resetTimer0();
void INTERRUPTION_resumeTimer0();
void INTERRUPTION_startTimer0();
void INTERRUPTION_stopTimer0();