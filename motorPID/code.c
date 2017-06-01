//40ms pro anti boucing
#define COUNTER (0xffff - 235 )
#define COUNTER1 (0xffff - 50000 )

// LCD module connections
sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;


int totalPulsos = 0;

int setPointDuty;
int currentDuty;

int pwm = 254;

int erroTotal = 0;


int setPointRPM = 0;
//lida pela frequencia do circuito
//vamos comecar em 1200
int currentRPM = 1200;

//se = 1, aceita nova tecla
//se = 0, nao aceita -> anti boucing em acao
int aceitaNovaTecla = 1;


void controlePid(){
    float kp = 0.015, ki=0.0005;
    int saida;
    int erro;
    int pwmTemp;

    //erro = setPointRPM - currentRPM;
    erro = setPointRPM - currentRPM;
    erroTotal += erro;

     if(abs(erro) > 5){
        //vamos tentar controlar
         pwmTemp = pwm + kp*erro + ki*erroTotal;
        
         //pwmTemp = (((pwm*20 - 2389) + kp*erro + ki*erroTotal) + 2389)/20;
        
        //garantindo que nao vai sair de 0 nem 255

        if(pwmTemp > 255)
        {
         pwm = 255;
        }
        else if(pwmTemp < 0){
         pwm = 125;
        }
        else{
         pwm = pwmTemp;
        }
        //joga saida pra PWM

    }
    else{
        //considero controlado
        erro = 0;
        erroTotal = 0;
    }




}


float leAnalogico(){
    int resInt;

    resInt = ADC_Read(0);
    return 5.0*(resInt/1024.0);
}

void exibe(){

    int i=0;
    char currentRPMStr[10];
    char setPointRPMStr[10];
    char strCurrent[16];
    char strSetPoint[16];
    char strPwm[16];
    char pwmDisplay[16];

    Lcd_Cmd(_LCD_CURSOR_OFF);

    strcpy(strSetPoint,"SP");
    IntToStr(setPointRPM, setPointRPMStr);
    strcat(strSetPoint, &setPointRPMStr[2]);
    
    strcpy(pwmDisplay, " PWM");
    IntToStr(pwm, strPwm);
    strcat(pwmDisplay, &strPwm[3]);
    
    strcpy(strCurrent,"Current: ");
    IntToStr(currentRPM,currentRPMStr);

    strcat(strCurrent, currentRPMStr);


    Lcd_Out(1,1,strSetPoint);

    Lcd_Out(1,8,pwmDisplay);
    Lcd_Out(2,1,strCurrent);
}

void digitou(char digito){

    if(digito == '1'){
        //pwm--;
        setPointRPM = 800;
    }
    else if(digito == '2'){
        //pwm++;
        setPointRPM = 1200;
    }
    else if(digito == '3'){
        setPointRPM = 1400;
    }

}
void pegaTeclaLida(){
    int linha;
    int i;
    int aux;


    char str[10];
    char str1[10];

    if(!PORTB.B4){
                                //line 1

        PORTA.RA1 = 1;
        if(PORTB.RB4){
                                        //NUMBER 7


            digitou('7');
                                        //show('7');
        }
        else{
            PORTB.RB1 = 1;
            if(PORTB.RB4){
               digitou('8');
                                                //show('8');
           }
           else{
            PORTB.RB2 = 1;
            if(PORTB.RB4){
                                                        //NUMBER 9
               digitou('9');
                                                        //show('9');
           }
           else{
            PORTB.RB3 = 1;
            if(PORTB.RB4){
                                                        //NUMBER /
                                                        ////lcd_out(1,1,"/");
                                                        //show('b');
            }
        }

    }
}

PORTA.RA1 = 0;
PORTB.RB1 = 0;
PORTB.RB2 = 0;
PORTB.RB3 = 0;




}
else if(!PORTB.RB5){
                                //line 2

    PORTA.RA1 = 1;
    if(PORTB.RB5){
                                        //NUMBER 4
       digitou('4');
                                        //show('4');
   }
   else{
    PORTB.RB1 = 1;
    if(PORTB.RB5){
                                        //NUMBER 5
       digitou('5');
                                        //show('5');
   }
   else{
    PORTB.RB2 = 1;
    if(PORTB.RB5){
                                                //NUMBER 6
       digitou('6');
                                                //show('6');
   }
   else{
    PORTB.RB3 = 1;
    if(PORTB.RB5){
                                                        //NUMBER *
                                                        ////lcd_out(1,1,"*");
                                                        //show('a');
    }
}

}
}

PORTA.RA1 = 0;
PORTB.RB1 = 0;
PORTB.RB2 = 0;
PORTB.RB3 = 0;


}
else if(!PORTB.RB6){
                                //line 3

    PORTA.RA1 = 1;
    if(PORTB.RB6){
                                        //NUMBER 1
       digitou('1');
                                        //show('1');
   }
   else{
    PORTB.RB1 = 1;
    if(PORTB.RB6){
                                        //NUMBER 2
       digitou('2');
                                        //show('2');
   }
   else{
    PORTB.RB2 = 1;
    if(PORTB.RB6){
                                                //NUMBER 3
       digitou('3');
                                        //        show('3');
   }
   else{
    PORTB.RB3 = 1;
    if(PORTB.RB6){
                                                        //NUMBER -
                                                        ////lcd_out(1,1,"-");
                                                        //show('c');
    }
}

}
}

PORTA.RA1 = 0;
PORTB.RB1 = 0;
PORTB.RB2 = 0;
PORTB.RB3 = 0;


}
else if(!PORTB.RB7){
                                //line 4

    PORTA.RA1 = 1;
    if(PORTB.RB7){
                                        //NUMBER on
                                        ////lcd_out(1,1,"on");
                                        //checkCode();
    }
    else{
        PORTB.RB1 = 1;
        if(PORTB.RB7){
                                        //NUMBER 0
                                        ////lcd_out(1,1,"0");
            digitou('0');
        }
        else{
            PORTB.RB2 = 1;
            if(PORTB.RB7){
                                                //NUMBER =
                                                ////lcd_out(1,1,"=");
                                                //show('7');
            }
            else{
                PORTB.RB3 = 1;
                if(PORTB.RB7){
                                                        //NUMBER +
                                                        ////lcd_out(1,1,"+");
                                                        //show('7');
                }
            }

        }
    }


    PORTA.RA1 = 0;
    PORTB.RB1 = 0;
    PORTB.RB2 = 0;
    PORTB.RB3 = 0;


}

return;

}



void interrupt(){
    if(PIR1.TMR1IF){
        unsigned int currentFrequency;
        //timer 1 responsavel por atualizar display
        //le a entrada, avaliando sua frequencia(RPM)
        //e então, fazer controle do motor
        TMR1H = COUNTER1 >> 8;  // RE-Load Timer 1 counter
        TMR1L = COUNTER1;       // RE-Load Timer 1 counter

        PORTD.RD0 = ~PORTD.RD0;
        currentFrequency = totalPulsos*5; //0.2
        currentRPM = currentFrequency/16*15; //aqui tá em hz
          //currentRPM = currentFrequency/60/64;  /64 pedaços

        totalPulsos = 0;


        controlePid();
        PIR1.TMR1IF = 0;

    }

    if(INTCON.RBIF){
        //interrupcao de mudança de nível
            //anti boucing
            if(aceitaNovaTecla){
                PORTC.RC1 = ~PORTC.RC1;

                aceitaNovaTecla = 0;
                TMR0H = COUNTER >> 8;  // RE-Load Timer 0 counter - 1st TMR0H
                TMR0L = COUNTER;       // RE-Load Timer 0 counter - 2nd TMR0L

                pegaTeclaLida();

                INTCON.RBIF = 0;
            }
    }

    if (INTCON.TMR0IF){
        //timer 0 responsavel pelo anti bouncing

        if(aceitaNovaTecla == 0){
            aceitaNovaTecla = 1;
        }

        //acho que nao precisa, só é pra disparar quando clicar de novo
        TMR0H = COUNTER >> 8;  // RE-Load Timer 0 counter - 1st TMR0H
        TMR0L = COUNTER;       // RE-Load Timer 0 counter - 2nd TMR0L

        INTCON.TMR0IF=0;
    }

    if(INT0IF_BIT){
      PORTC.RC3 = ~PORTC.RC3;
     //porta mudou
      totalPulsos = totalPulsos+1;
      INT0IF_BIT = 0;
     }


}


int main(){
    char str[10];
    INTCON.GIE = 1;
    INTCON.RBIE = 1;
    INTCON.INT0IE = 1;
    INTCON.INT0IF= 0;
    INTCON.RBIF = 0;

    //só o 1 AN1 é saida
    TRISA = 0XFD;
    TRISB = 0Xf1;
    TRISC = 0X00;
    TRISD = 0X00;

    PORTA.RA1 = 0;
    PORTB.RB1 = 0;
    PORTB.RB2 = 0;
    PORTB.RB3 = 0;


    ADCON1 = 0X0E;


    // Timer 0 Configuration
    T0CON.T08BIT = 0;       // 16 bits
    T0CON.T0CS = 0;         // Internal clock => Crystal/4
    T0CON.PSA = 0;          // Prescaler ON
    T0CON.T0PS2 = 1;        // Prescaler = 000 => 1:256
    T0CON.T0PS1 = 1;
    T0CON.T0PS0 = 1;
    // Load Timer 0 counter
    TMR0H = COUNTER >> 8;  // Load Timer 0 counter - 1st TMR0H
    TMR0L = COUNTER;       // Load Timer 0 counter - 2nd TMR0L
    // Timer 0 interrupt
    INTCON.TMR0IP = 1;
    INTCON.TMR0IF=0;
    INTCON.TMR0IE=1;
    INTCON.PEIE=0;
    INTCON.GIE=1;
    // enable timer 0
    T0CON.TMR0ON=1;         // Timer ON


    //Timer 1 configuration
    T1CON = 0X31;
    PIR1.TMR1IF = 0;
    PIE1.TMR1IE = 1;
    TMR1H = COUNTER1 >> 8;  // RE-Load Timer 1 counter
    TMR1L = COUNTER1;       // RE-Load Timer 1 counter
    T1CON.TMR1ON = 1;

    INT0IE_bit = 1; //HABILITA INTERRUPCAO EXTERNA NO INT0

    //inicia com frequencia de 5khz
    PWM1_Init(5000);
    PWM1_Start();

    //LCD
    Lcd_Init();

    while(1){
           exibe();
           delay_ms(250);

           PWM1_Set_Duty(pwm);
//      setPointDuty = ADC_Read(0);
      //transforming from 10 bits to 8
//      setPointDuty = setPointDuty >> 2;



     // delay_ms(10);

  }


}