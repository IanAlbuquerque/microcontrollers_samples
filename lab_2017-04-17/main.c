int segmento[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};

char strcode[10];
int pos = 0;
/*
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
*/
void show(char num)
{
  delay_ms(50);
  PORTD = segmento[num - '0'];

  strcode[pos]=num;
  pos++;
  strcode[pos]='\0';


}

void checkCode(){

  char str[10];
  int i;
  str[0]='1';
  str[1]='2';
  str[3]='3';
  str[4]='\0';


  //só pra saber que chegou até aqui
  for(i=0;i<5;i++){
      PORTD.RD7 = 1;
      delay_ms(300);
      PORTD.RD7 = 0;
      delay_ms(300);
  }

  //se acertar codigo pisca mais 10
  if(!strcmp(str,strcode)){
    for(i=0;i<10;i++){
      PORTD.RD7 = 1;
      delay_ms(300);
      PORTD.RD7 = 0;
      delay_ms(300);
    }



  }

  pos = 0;
  strcode[pos]='\0';


}

void interrupt(){

     if(INTCON.RBIF){
        INTCON.RBIF = 0;


    if(!PORTB.RB4){
      //line 1

      PORTB.RB0 = 1;
      if(PORTB.RB4){
        //NUMBER 7
        //Lcd_Out(1,1,"7");
        show('7');
      }
      else{
        PORTB.RB1 = 1;
        if(PORTB.RB4){
          //NUMBER 8
          //Lcd_Out(1,1,"8");
          show('8');
        }
        else{
          PORTB.RB2 = 1;
          if(PORTB.RB4){
            //NUMBER 9
            //Lcd_Out(1,1,"9");
            show('9');
          }
          else{
            PORTB.RB3 = 1;
            if(PORTB.RB4){
            //NUMBER /
            //Lcd_Out(1,1,"/");
            show('b');
            }
          }

        }
      }

    PORTB.RB0 = 0;
    PORTB.RB1 = 0;
    PORTB.RB2 = 0;
    PORTB.RB3 = 0;




    }
    else if(!PORTB.RB5){
      //line 2

      PORTB.RB0 = 1;
      if(PORTB.RB5){
        //NUMBER 4
        //Lcd_Out(1,1,"4");
        show('4');
      }
      else{
        PORTB.RB1 = 1;
        if(PORTB.RB5){
        //NUMBER 5
        //Lcd_Out(1,1,"5");
        show('5');
        }
        else{
          PORTB.RB2 = 1;
          if(PORTB.RB5){
          //NUMBER 6
          //Lcd_Out(1,1,"6");
          show('6');
          }
          else{
            PORTB.RB3 = 1;
            if(PORTB.RB5){
            //NUMBER *
            //Lcd_Out(1,1,"*");
            show('a');
            }
          }

        }
      }

    PORTB.RB0 = 0;
    PORTB.RB1 = 0;
    PORTB.RB2 = 0;
    PORTB.RB3 = 0;


    }
    else if(!PORTB.RB6){
      //line 3

      PORTB.RB0 = 1;
      if(PORTB.RB6){
        //NUMBER 1
        //Lcd_Out(1,1,"1");
        show('1');
      }
      else{
        PORTB.RB1 = 1;
        if(PORTB.RB6){
        //NUMBER 2
        //Lcd_Out(1,1,"2");
        show('2');
        }
        else{
          PORTB.RB2 = 1;
          if(PORTB.RB6){
          //NUMBER 3
          //Lcd_Out(1,1,"3");
          show('3');
          }
          else{
            PORTB.RB3 = 1;
            if(PORTB.RB6){
            //NUMBER -
            //Lcd_Out(1,1,"-");
            show('c');
            }
          }

        }
      }

       PORTB.RB0 = 0;
       PORTB.RB1 = 0;
       PORTB.RB2 = 0;
       PORTB.RB3 = 0;


    }
    else if(!PORTB.RB7){
      //line 4

      PORTB.RB0 = 1;
      if(PORTB.RB7){
        //NUMBER on
        //Lcd_Out(1,1,"on");
        checkCode();
      }
      else{
        PORTB.RB1 = 1;
        if(PORTB.RB7){
        //NUMBER 0
        //Lcd_Out(1,1,"0");
        show('0');
        }
        else{
          PORTB.RB2 = 1;
          if(PORTB.RB7){
          //NUMBER =
          //Lcd_Out(1,1,"=");
          show('7');
          }
          else{
            PORTB.RB3 = 1;
            if(PORTB.RB7){
            //NUMBER +
            //Lcd_Out(1,1,"+");
            show('7');
            }
          }

        }
      }


       PORTB.RB0 = 0;
       PORTB.RB1 = 0;
       PORTB.RB2 = 0;
       PORTB.RB3 = 0;


    }

    }


}

int main(){


         unsigned value_a1;
         unsigned value_a2;
  //global
  INTCON.GIE = 1;
  //port change interrupt
  INTCON.RBIE = 1; INTCON.RBIF = 0;
  //external interrupt
  INTCON.INT0IE = 1;

  //4-7 input
  TRISB = 0XF0;
  PORTB.RB0 = 0;
  PORTB.RB1 = 0;
  PORTB.RB2 = 0;
  PORTB.RB3 = 0;

  TRISD = 0;

  PORTD.RD4 = 0;
  PORTD.RD5 = 0;
  PORTD.RD6 = 0;
  PORTD.RD7 = 0;


  //Lcd_Init();


        //AN0 and AN1 are analogic
        ADCON1.AN0 = 0;
        ADCON1.AN1 = 0;
        
        
        //AN0 and AN1 are digital
         //ADCON1.AN2 = 1;
         //ADCON1.AN3 = 1;
        // ADCON1.AN4 = 1;
        // ADCON1.AN5 = 1;

        //analogics
        TRISA.AN0 = 1;
        TRISA.AN1 = 1;
        
        //digitals
        //TRISA.AN3 = 1;
       // TRISA.AN4 = 1;
       // TRISA.AN5 = 1;
        
        while(1){
           //reading from channel 0 (AN0)
         value_a1 = ADC_Read(0);
         //transforming from 10 bits to 8
         value_a1 = value_a1 >> 2;
         
         if(value_a1 > 153){
         //sensor 1 ativado
         //153 is 60% of 255 (3volts/5volts)

         //blink just to identify
                     PORTD.RD7 = 1;
                     delay_ms(300);
                     PORTD.RD7 = 0;
                     delay_ms(300);
         }




           //reading from channel 0 (AN0)
         value_a2 = ADC_Read(1);
         //transforming from 10 bits to 8
         value_a2 = value_a2 >> 2;
         
         
          if(value_a2 > 204){
         //sensor 2 ativado
         //204 is 80% of 255 (4volts/5volts)

         //blink just to identify
                     PORTD.RD7 = 1;
                     delay_ms(300);
                     PORTD.RD7 = 0;
                     delay_ms(300);
                     PORTD.RD7 = 1;
                     delay_ms(300);
                     PORTD.RD7 = 0;
                     delay_ms(300);
         }

         delay_ms(1000);
        }


}