
unsigned porcentagem;

float leAnalogico(){
int resInt;

resInt = ADC_Read(0);
return 5.0*(resInt/1024.0);
}
void interrupt(){
}



void main() {

TRISA = 0XFF;
TRISC = 0X00;

//only an1
ADCON1 = 0X0E;

PWM1_Init(5000);
PWM1_Start();


while(1){
int res = ADC_Read(0);
//transforming from 10 bits to 8
res = res >> 2;
PWM1_Set_Duty(res);


delay_ms(10);

}


}