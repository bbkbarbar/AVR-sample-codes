#include <avr/io.h>
#include <util/delay.h>
//#include <avr/iom8.h>

//#include <avr/interrupt.h>
//#include <compat/deprecated.h>

#define DEFAULT_DELAY 20

#define MAX_PERCENTAGE 70

#define CH_RED		0
#define CH_BLUE   	2
#define CH_GREEN  	1

#define DispEI		PORTD |=  (1<<PD0)
#define DispEN		PORTD &= ~(1<<PD0)



void init(){   // 76543210
		DDRB  = 0xFF;
	  	DDRC  =  0b0000000;
  	  	DDRD  = 0x01;
	  	
	  	PORTB = 0b00000000;
	  	PORTD = 0x01;
	  	
	  //DDRB = (1<<PB0)|(1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7);
}

void wait(unsigned short val) {
//-------------------------------------
    while(val--) _delay_ms(2);
}

 
void _wait() {
//-------------------------------------
    wait(DEFAULT_DELAY);
}


void onBtn1Pressed(unsigned char* p){

	if(*p){
		*p = 0;
	}else{
		*p = 1;
	}

	if(*p == 0){
		PORTB &= 0b11001111;
	}else{
		PORTB |= 0b00110000;
	}

}

void onBtn2Pressed(unsigned char* p){

	if(*p){
		*p = 0;
	}else{
		*p = 1;
	}

	if(*p == 0){
		PORTB &= 0b00111111;
	}else{
		PORTB |= 0b11000000;
	}
	
}

int main(){

	init();

	unsigned char bt1Pressed = 0;
	unsigned char bt2Pressed = 0;

	unsigned char state  = 0;	
	unsigned char state2 = 0;	

	while(1){


		if(bt1Pressed == 0){
			if((PIND>>6 & 0b1)){
				bt1Pressed = 1;
			}
		}else{
			if((PIND>>6 & 0b1) == 0){
				bt1Pressed = 0;
				onBtn1Pressed(&state);
				wait(100);
			}
		}

		if(bt2Pressed == 0){
			if((PIND>>7 & 0b1)){
				bt2Pressed = 1;
			}
		}else{
			if((PIND>>7 & 0b1) == 0){
				bt2Pressed = 0;
				onBtn2Pressed(&state2);
				wait(100);
			}
		}

		/*
		if(PIND & 0b00100000){
			PORTB |= 0b00001100;
		}else{
			PORTB &= ~(0b00001100);
		}	/**/

	}

	return 0;
}
