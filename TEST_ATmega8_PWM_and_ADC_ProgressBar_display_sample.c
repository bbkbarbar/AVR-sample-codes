/*

ADC works, can be shown on PORTD "bar-display", but there is an issue with ADC value-range

*/

#include <avr/io.h>
#include <util/delay.h>

#define	DEFAULT_DELAY 100

#define UP 		1
#define DOWN 	1


void wait(unsigned short val) {

    while(val--) _delay_ms(1);

}


void _wait(){
	_delay_ms(DEFAULT_DELAY);
}


/*==========================================================================*
 *							 							   					*
 *			 			  "ProgressBar" on portD			   				*
 *							 Boor Andras - 2016			   					*
 *							 							   					*
 *==========================================================================*/
void showByteValueOnBar(unsigned int val){
	
	if(val > 16){
		PORTD =         0b1;
	}
	if(val > 48){
		PORTD |=       0b10;	
	}
	if(val > 80){
		PORTD |=      0b100;
	}
	if(val > 112){
		PORTD |=     0b1000;
	}
	if(val > 144){
		PORTD |=    0b10000;
	}
	if(val > 176){
		PORTD |=   0b100000;
	}
	if(val > 208){
		PORTD |=  0b1000000;
	}
	if(val > 240){
		PORTD |= 0b10000000;
	}

}


void init(){   // 76543210
		DDRB  = 0b11111111;
	  	DDRC  =  0b0000000;
  	  	DDRD  = 0b11111111;
	  	
	  	PORTD = 0x01;
	  	
	  //DDRB = (1<<PB0)|(1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7);
}


/*==========================================================================*
 *							 							   					*
 *			 	ADC (10bit) (tested in channel 0 and channel 5)			   	*
 *							 Tested on ATmega8			   					*
 *							 							   					*
 *		  DDRC seems doesn't matter (it works when DDRC = 0b11101111)		*
 *							 							   					*
 *							 							   					*
 *							 Boor Andras - 2014			   					*
 *							 							   					*
 *==========================================================================*/


void initADC() {
    //         76543210
    ADMUX  = 0b01000000;
    ADCSRA = 0b10000111;
} 


uint16_t readADC(uint8_t ch) {

    ADMUX = (ADMUX & 0b11110000) | ch;
//  01000001    ADMUX jelenlegi állapota (1-es ADC csatorna beállítva)
//& 11110000    ezzel toroljuk az elozo portok kivalasztast
//= 01000000    eredmenynek kapjuk az eredeti ADMUX beallitast
//| 00000101    "rairjuk" az ADC csatornat
//= 01000101    
    ADCSRA|=(1<<ADSC);          // konverzió elindítás
    while(ADCSRA & (1<<ADSC));  // várás az átalakításra

    return (ADCL | (ADCH<<8));  // adc érték visszaadása
}


int main(){

	init();
	PORTC = 0;
	initADC();

	unsigned char i = 0;
	unsigned char direction = UP;
	unsigned int value = 0;

	for(;i<3;i++){
		
		showByteValueOnBar(value);
		_wait();

		if(direction == UP){
			if(value < 255){
				value++;
			}else{
				direction = DOWN;
			}
		}
		else{ 		// DOWN
			if(value > 0){
				value--;
			}else{
				direction = UP;
			}
		}
	}

	while(1){

		value = readADC(2);

		if(value > 1023){
			PORTB |=   0b10000000;
		}else{
			PORTB &= !(0b10000000);
		}

		if(value > 511){
			PORTB |=   0b01000000;
		}else{
			PORTB &= !(0b01000000);
		}

		if(value > 255){
			PORTB |=   0b00100000;
		}else{
			PORTB &= !(0b00100000);
		}

		showByteValueOnBar((value/4) -20);
		wait(50);

	}

	return 0;

}
