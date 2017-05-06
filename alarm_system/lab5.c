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

#define COUNTER (0xffff - 1000 )


char sensorDefeito[10];
int cont1;
int pos = 0;
int alarmeAtivo = 0;
int digitandoSenha = 0;

char *senhaAtiva = "123";
char *senhaDesativa = "321";

int errou = 0;

void digitou(char digito){
	char str[10];
	str[0] = digito;
	str[1] = '\0';
	Lcd_Out(1,1,"                         ");
	Lcd_Out(2,1,"                         ");
	Lcd_Out(1,1,str);
	digitandoSenha = 1;
	if(!alarmeAtivo){
		//comparo com senha que ativa
		if(senhaAtiva[pos] != digito){
			errou = 1;
		}
	}
	else{
		if(senhaDesativa[pos] != digito){
			errou = 1;
		}
	}



	if(pos == 2){
		if(errou){
			Lcd_Out(1,1,"Senha invalida");	
		}
		else{
			Lcd_Out(1,1,"Acertou");
			if(alarmeAtivo){
				alarmeAtivo=0;
				Lcd_Out(1,1,"Alarme desativado");
				PORTD.RD2 = 0;
			}
			else{
				alarmeAtivo=1;
				Lcd_Out(1,1,"Alarme ativado");
				PORTD.RD2 = 1;
			}

			
		}
		errou = 0;
		digitandoSenha = 0;
		pos = -1;
	}

	pos++;

}
void pegaTeclaLida(){
	int linha;
	int i;
	int aux;


	char str[10];
	char str1[10];
	   /*
	    if(!PORTB.RB4){
	    linha=1;
	    Lcd_Out(1,1,"Linha 1");
	     }
	    else if(!PORTB.RB5){
	    linha=2;
	     Lcd_Out(1,1,"Linha 2");
	    }
	    else if(!PORTb.RB6){
	    linha=3;
	     Lcd_Out(1,1,"Linha 3");
	    }
	    else if(!PORTb.RB7){
	    linha=4;
	     Lcd_Out(1,1,"Linha 4");
	    }
	    */
	    




			if(!PORTB.RB4){
				//line 1

				PORTB.RB0 = 1;
				if(PORTB.RB4){
					//NUMBER 7
	                cont1++;
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
							//Lcd_Out(1,1,"/");
							//show('b');
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
							//Lcd_Out(1,1,"*");
							//show('a');
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
					//	show('3');
						}
						else{
							PORTB.RB3 = 1;
							if(PORTB.RB6){
							//NUMBER -
							//Lcd_Out(1,1,"-");
							//show('c');
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
					//checkCode();
				}
				else{
					PORTB.RB1 = 1;
					if(PORTB.RB7){
					//NUMBER 0
					//Lcd_Out(1,1,"0");
					//show('0');
					}
					else{
						PORTB.RB2 = 1;
						if(PORTB.RB7){
						//NUMBER =
						//Lcd_Out(1,1,"=");
						//show('7');
						}
						else{
							PORTB.RB3 = 1;
							if(PORTB.RB7){
							//NUMBER +
							//Lcd_Out(1,1,"+");
							//show('7');
							}
						}

					}
				}


				 PORTB.RB0 = 0;
				 PORTB.RB1 = 0;
				 PORTB.RB2 = 0;
				 PORTB.RB3 = 0;


			}
			
			return;
		
}

void exibe(int total){
	int i;
	char totalString[8];
	char stringCompleta1[50];
	char stringCompleta2[50];

	IntToStr(total,totalString);

	if(total >= 2){
		strcpy(stringCompleta1,"Alert.Intr:          ");
		strcpy(stringCompleta2,totalString);
		strcat(stringCompleta2, " sensores ativados         ");
	}
	else if(total == 1){
		strcpy(stringCompleta1,"Alert.Poss.Intr:        ");
		strcpy(stringCompleta2,sensorDefeito);
		strcat(stringCompleta2," com defeito               ");
	}
	else{
		strcpy(stringCompleta1,"Nenhum sensor ativado      ");
		strcpy(stringCompleta2,"                          ");
	}

	Lcd_Cmd(_LCD_CURSOR_OFF);
	
     //Lcd_Cmd(_LCD_CLEAR);
	Lcd_Out(1,1,stringCompleta1);
    Lcd_Out(2,1,stringCompleta2);

}


int leSensorDig(){
	int i;
	int total =0;

	total = (int) PORTC.RC0 + (int) PORTC.RC1 + (int) PORTC.RC2 + (int) PORTC.RC3;

	if((int) PORTC.RC0){
		strcpy(sensorDefeito, "dig1");
	}
	if((int) PORTC.RC1){
		strcpy(sensorDefeito, "dig2");
	}
	if((int) PORTC.RC2){
		strcpy(sensorDefeito, "dig3");
	}
	if((int) PORTC.RC3){
		strcpy(sensorDefeito, "dig4");
	}

    return total;

}
int leSensorAnal(){
	int total = 0;
	int i;
    unsigned int anal1;
    unsigned int anal2;
    
    
     anal1 = ADC_Read(0);
     anal1 = anal1 >> 2;

     if(anal1 > 153){
     	strcpy(sensorDefeito, "anal 1");
     	total++;
     }
     
     anal2 = ADC_Read(1);
     anal2 = anal2 >> 2;


      if(anal2 > 204){
      	strcpy(sensorDefeito, "anal 2");
     //sensor 2 ativado
     //204 is 80% of 255 (4volts/5volts)
      	total++;
     }

     return total;
}

void interrupt(){
	if(INTCON.RBIF){
		//interrupcao de mudança de nível
	    pegaTeclaLida();
	    PORTB.RB0 = 0;
	 	PORTB.RB1 = 0;
	 	PORTB.RB2 = 0;
	 	PORTB.RB3 = 0;
	    //apenas ao final de tudo
	    INTCON.RBIF = 0;

	}

	 if (INTCON.TMR0IF == 1){
	 	//interrupcao de timerint total = 0
	 	if(digitandoSenha || !alarmeAtivo){

	 	}
	 	else{
		 	
		 	char str[10];
		 	int total = 0;
		 	strcpy(sensorDefeito,"          ");
		    total += leSensorAnal();
		    total += leSensorDig();
		    exibe(total);
		     

		    TMR0H = COUNTER >> 8;  // RE-Load Timer 0 counter - 1st TMR0H
		    TMR0L = COUNTER;       // RE-Load Timer 0 counter - 2nd TMR0L
	 	}
	     INTCON.TMR0IF=0;
	  }

}

int i=0;
int main(){
	char str[10];
    cont1 = 0;
	INTCON.GIE = 1;
	INTCON.RBIE = 1; INTCON.RBIF = 0;
	//external interrupt
	INTCON.INT0IE = 1;
	INTCON.PEIE = 0;

	TRISB = 0xF0;
	TRISD = 0XFB;
	
	
	PORTB.RB0 = 0;
	PORTB.RB1 = 0;
	PORTB.RB2 = 0;
	PORTB.RB3 = 0;
    
    //an0 e an1 sao analogicos
    ADCON1.AN0 = 0;
    ADCON1.AN1 = 0;
    //inputs
    TRISA.AN0 = 1;
    TRISA.AN1 = 1;
        
        
	Lcd_Init();

	// Timer 0 Configuration
	T0CON.T08BIT = 0;       // 16 bits
	T0CON.T0CS = 0;         // Internal clock => Crystal/4
	T0CON.PSA = 0;          // Prescaler ON
	T0CON.T0PS2 = 0;        // Prescaler = 000 => 1:2
	T0CON.T0PS1 = 0;
	T0CON.T0PS0 = 0;
	// Load Timer 0 counter
	TMR0H = COUNTER >> 8;  // Load Timer 0 counter - 1st TMR0H
	TMR0L = COUNTER;       // Load Timer 0 counter - 2nd TMR0L
	// Timer 0 interrupt
	INTCON.TMR0IP = 1;
	INTCON.TMR0IF=0;
	INTCON.TMR0IE=1;
	INTCON.PEIE=0;
	INTCON.GIE=1;
	// Start timer 0
	T0CON.TMR0ON=1;         // Timer ON


	alarmeAtivo = 0;

}