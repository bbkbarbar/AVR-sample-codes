 /********************************************************************\
 *    Sample for 7+1 segment LED display @ 4 digits                   *
 *    Device: Custom, [4x7 base panel suggested]                      *
 *                                                                    *
 *    Tested with .............                                       *
 *      + ___ - OK?                                                   *
 *                                                                    *
 *                         Boor Andras - 2016                         *
 *                                                                    *
 *    https://www.youtube.com/watch?v=???????????                     *
 \********************************************************************/

#include "LED_display/led_display_4x7.c"

#define F_CPU 1000000

#include <avr/io.h>

//#include <util/delay.h>
//#define DELAY_INCLUDED


#define INT_4_DIGIT 		4567
#define INT_3_DIGIT 		369
#define INT_2_DIGIT 		48
#define INT_1_DIGIT 		2
#define FLOAT_1_2_DIGIT 	1.12

void init(){     // 76543210
		DDRB  = 0x0b11110000;
  	  	DDRD  = 0xFF;
	  	
	  	PORTB = 0;
	  	PORTD = 0;
	  	
	  //DDRB = (1<<PB0)|(1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7);
}


int main(){

	init();

	uint8_t demoItem = 0;



	return 0;
}
