
#define COUNTER (0Xffff - 15625)


// LCD module connections
sbit LCD_RS at RD0_bit;
sbit LCD_EN at RD1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD0_bit;
sbit LCD_EN_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module connections


int total = 0;
float frequency;
char txt[10];

void interrupt(){

     if(INTCON.TMR0IF){
      //entra a cada 2segundos pela conta do timer
      frequency = total/2.0;
      total = 0;
      
      TMR0H = COUNTER >> 8;
      TMR0L = COUNTER;
      INTCON.TMR0IF = 0;
     }

     if(INT0IF_BIT){
      PORTC.RC2 = ~PORTC.RC2;
     //porta mudou
      total = total+1;
      INT0IF_BIT = 0;
     }
}


void main() {

int x = 10;
TRISB = 0XFF;
TRISC = 0X00;
TRISD = 0X00;
Lcd_Init();

//interrupt configs
INTCON.GIE = 1;
INTCON.RBIE = 1;
INTCON.RBIF = 0;
INTCON.PEIE = 0;
INT0IE_bit = 1; //HABILITA INTERRUPCAO EXTERNA NO INT0
 INTEDG1_bit = 0; // interrupcao por borda de descida

//TIMER 0
T0CON.T08BIT = 0;
T0CON.T0CS = 0;
PSA_bit = 0;
T0PS0_bit = 1;
T0PS1_bit = 1;
T0PS2_bit = 1;
T0CON.TMR0ON = 1;
//LOAD TIMER
TMR0H = COUNTER >> 8;
TMR0L = COUNTER;
//Enable
INTCON.TMR0IE = 1;
INTCON.TMR0IF = 0;
INTCON.INT0IE = 1;

Lcd_Cmd(_LCD_CURSOR_OFF);
while(1){
char txt1[20];
FloatToStr(frequency,txt1);
         // Cursor off
Lcd_Out(1,1,"Frequencia Lida (hz) ");
Lcd_Out(2,1,txt1);
delay_ms(20);

}


}