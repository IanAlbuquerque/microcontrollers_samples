#define COUNTER (0xffff - 156 )
#define COUNTER1 (0xffff - 25000 )

int segmento[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};


int temporizador = 1;
int dezena = 0;
int unidade = 0;
int decimo = 0;

int acabou = 0;
int controle = 1;
int step = 1;
int dispara = 0;
int programando = 0;



void digitou(char digito){
	char str[10];
	int numeroDigitado = digito - '0';
	str[0] = digito;
	str[1] = '\0';


	if(step == 1){
		temporizador = numeroDigitado;
		step = 2;
	}
	else if(step == 2){
		temporizador = temporizador*10 + numeroDigitado;
		step = 3;
	}
	else if(step == 3){
		temporizador = temporizador*10 + numeroDigitado;
		step = 1;
	}


}
void pegaTeclaLida(){
	int linha;
	int i;
	int aux;


	char str[10];
	char str1[10];

			if(!PORTC.RC4){
				//line 1

				PORTB.RB0 = 1;
				if(PORTC.RC4){
					//NUMBER 7
	                digitou('7');
					//show('7');
				}
				else{
					PORTB.RB1 = 1;
					if(PORTC.RC4){
						 digitou('8');
						//show('8');
					}
					else{
						PORTB.RB2 = 1;
						if(PORTC.RC4){
							//NUMBER 9
							 digitou('9');
							//show('9');
						}
						else{
							PORTB.RB3 = 1;
							if(PORTC.RC4){
							//NUMBER /
							////lcd_out(1,1,"/");
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
			else if(!PORTC.RC5){
				//line 2

				PORTB.RB0 = 1;
				if(PORTC.RC5){
					//NUMBER 4
					 digitou('4');
					//show('4');
				}
				else{
					PORTB.RB1 = 1;
					if(PORTC.RC5){
					//NUMBER 5
					 digitou('5');
					//show('5');
					}
					else{
						PORTB.RB2 = 1;
						if(PORTC.RC5){
						//NUMBER 6
						 digitou('6');
						//show('6');
						}
						else{
							PORTB.RB3 = 1;
							if(PORTC.RC5){
							//NUMBER *
							////lcd_out(1,1,"*");
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
			else if(!PORTC.RC6){
				//line 3

				PORTB.RB0 = 1;
				if(PORTC.RC6){
					//NUMBER 1
					 digitou('1');
					//show('1');
				}
				else{
					PORTB.RB1 = 1;
					if(PORTC.RC6){
					//NUMBER 2
					 digitou('2');
					//show('2');
					}
					else{
						PORTB.RB2 = 1;
						if(PORTC.RC6){
						//NUMBER 3
						 digitou('3');
					//	show('3');
						}
						else{
							PORTB.RB3 = 1;
							if(PORTC.RC6){
							//NUMBER -
							////lcd_out(1,1,"-");
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
			else if(!PORTC.RC7){
				//line 4

				PORTB.RB0 = 1;
				if(PORTC.RC7){
					//NUMBER on
					////lcd_out(1,1,"on");
					//checkCode();
				}
				else{
					PORTB.RB1 = 1;
					if(PORTC.RC7){
					//NUMBER 0
					////lcd_out(1,1,"0");
					digitou('0');
					}
					else{
						PORTB.RB2 = 1;
						if(PORTC.RC7){
						//NUMBER =
						////lcd_out(1,1,"=");
						//show('7');
						}
						else{
							PORTB.RB3 = 1;
							if(PORTC.RC7){
							//NUMBER +
							////lcd_out(1,1,"+");
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



void interrupt(){

	if(INTCON.RBIF){
		//interrupcao de mudança de nível

		char teste[30];


		if(!PORTB.RB7 && programando){
		    strcpy(teste,"Teclado");
		    pegaTeclaLida();
		    PORTB.RB0 = 0;
		 	PORTB.RB1 = 0;
		 	PORTB.RB2 = 0;
		 	PORTB.RB3 = 0;


		}
		else if(PORTB.RB4){
		    strcpy(teste,"Programa");
		    //liga led programando
		    PORTC.RC2 = 1;

		    programando = 1;
		    //nova programacao, paga LED FIM
		    dispara = 0;
		    acabou = 0;
		    //PORTC.RC2 = 0;




		}
		else if(PORTB.RB5 && programando){
			//só disparar depois de programar
			strcpy(teste,"dispara");

			//apaga led programando
			PORTC.RC2 = 0;

			programando = 0;
			dispara = 1;

		}

	 INTCON.RBIF = 0;

	}

	if(PIR1.TMR1IF == 1 && !acabou && dispara){
		//interrupcao do timer 1
		//diminui o valor do temporizador
		if(temporizador == 0){
			acabou = 1;
			dispara = 0;

			//liga o led indicando que acabou
			//PORTC.RC2 = 1;

			PORTA.RA2 = 0;
		 	PORTA.RA3 = 0;
		 	PORTA.RA4 = 0;
		}
		else{
		temporizador--;
		}
		TMR1H = COUNTER1 >> 8;  // RE-Load Timer 0 counter - 1st TMR0H
    	TMR1L = COUNTER1;       // RE-Load Timer 0 counter - 2nd TMR0L

		PIR1.TMR1IF = 0;
	}

	 if (INTCON.TMR0IF == 1 && !acabou && dispara){
	 	//interrupcao de timerint0 total = 0


	 	if(!PORTA.RA2 && controle == 1){
	 		controle = 2;

	 		PORTA.RA2 = 0;
	 		PORTA.RA3 = 0;
	 		PORTA.RA4 = 0;
	 		PORTD = 0X00;

	 		dezena = temporizador/100;
	 		PORTA.RA2 = 1;
	 		PORTD = segmento[dezena];
	 	}
	 	else if(!PORTA.RA3 && controle == 2){
	 		controle = 3;

	 		PORTA.RA2 = 0;
	 		PORTA.RA3 = 0;
	 		PORTA.RA4 = 0;
	 		PORTD = 0X00;

	 		unidade = (temporizador%100)/10;
	 		PORTA.RA3 = 1;
	 		PORTD = segmento[unidade];

	 	}
	 	else if(!PORTA.RA4 && controle == 3){
	 		controle = 1;

	 		PORTA.RA2 = 0;
	 		PORTA.RA3 = 0;
	 		PORTA.RA4 = 0;
	 		PORTD = 0X00;

	 		decimo = temporizador%10;
	 		PORTA.RA4 = 1;
	 		PORTD = segmento[decimo];

	 	}

	 	//PORTD.RD7 = ~PORTD.RD7;
	    TMR0H = COUNTER >> 8;  // RE-Load Timer 0 counter - 1st TMR0H
	    TMR0L = COUNTER;       // RE-Load Timer 0 counter - 2nd TMR0L

	    INTCON.TMR0IF=0;
	  }

}


int main(){
	char str[10];
	INTCON.GIE = 1;
	INTCON.RBIE = 1; INTCON.RBIF = 0;
	//external interrupt
	INTCON.INT0IE = 1;
	INTCON.PEIE = 0;

	TRISA = 0X00;
	TRISB = 0xF0;
	TRISC = 0xFB;
	TRISD = 0X00;


	PORTB.RB0 = 0;
	PORTB.RB1 = 0;
	PORTB.RB2 = 0;
	PORTB.RB3 = 0;


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
	// Start timer 0
	T0CON.TMR0ON=1;         // Timer ON


	//Timer 1 configuration
	T1CON = 0X31;
	TMR1H = COUNTER1 >> 8;
	TMR1L = COUNTER1;

	PIR1.TMR1IF = 0;
	PIE1.TMR1IE = 1;


}