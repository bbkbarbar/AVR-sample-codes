 /********************************************************************\
 *    Sample for 7+1 segment LED display @ 4 digits                   *
 *    Device: Custom, [4x7 base panel suggested]                      *
 *                                                                    *
 *    PIN configuration:                                              *
 *      - Led configured by default (see led_diplay_4x7.h)            *
 *      - Button:                    PB0                              *
 *      - Button pressed feedback:   PB1                              *
 *                                                                    *
 *                         Boor Andras - 2016                         *
 *                                                                    *
 *    https://www.youtube.com/watch?v=???????????                     *
 \********************************************************************/

#include "led_display_4x7.c"

#define F_CPU 8000000

#include <avr/io.h>

//#include <util/delay.h>
//#define DELAY_INCLUDED

//#define DIGIT_REVERSED


#define INT_1_DIGIT 		2
#define INT_2_DIGIT 		48
#define INT_3_DIGIT 		369
#define INT_4_DIGIT 		4567

#define FLOAT_0_1_DIGIT 	0.1f
#define FLOAT_0_2_DIGIT 	0.02f
#define FLOAT_0_3_DIGIT 	0.003f

#define FLOAT_1_1_DIGIT 	1.2f
#define FLOAT_1_2_DIGIT 	1.23f
#define FLOAT_1_3_DIGIT 	1.234f

#define FLOAT_2_0_DIGIT 	12.0f
#define FLOAT_2_1_DIGIT 	12.3f
#define FLOAT_2_2_DIGIT 	12.34f

#define FLOAT_3_0_DIGIT 	123.0f
#define FLOAT_3_1_DIGIT 	123.4f

#define FLOAT_4_0_DIGIT 	1234.0f


#define isPressed()                (((PINB >> 0) & 0b1) == 0)
#define isReleased()               (((PINB >> 0) & 0b1) == 1)


void init(){    
 
	//        76543210 
	DDRB  = 0b11111001;
	//DDRB  = 0xFF;;
	DDRD  = 0xFF;

	PORTB = 0b01111000;
	PORTD = 0;
	  	
	//PORTB |= (1 << 0); // set pullup for btn input
}


int main(){

	init();

	uint8_t demoItem = 0;
	uint8_t btnPressedPreviously = 0;
		
	char c[] = {  
			'8', 
			'7', 
			'1', 
			'3'
		};
	uint8_t patternArray[4];
	for(int i=0; i<4; i++){
		patternArray[i] = getSegmentValueForChar(c[i]);
	}

	while(1){
		
		//showIntValue(1234, 10);
		
		enableDigit(0);
		enableSegments(getSegmentValueForChar(c[0]));
		enableDigit(4);
		_delay_ms(20);
		
		enableDigit(0);
		enableSegments(getSegmentValueForChar(c[1]));
		enableDigit(3);
		_delay_ms(20);
		
		enableDigit(0);
		enableSegments(getSegmentValueForChar(c[2]));
		enableDigit(2);
		_delay_ms(20);

		enableDigit(0);
		enableSegments(getSegmentValueForChar(c[3]));
		enableDigit(1);
		_delay_ms(20);

	/*
		if(btnPressedPreviously == 0){
			if(isPressed()){
				btnPressedPreviously = 1;
			}
		}else{
			if(isReleased()){
				btnPressedPreviously = 0;
				demoItem++;
				if(demoItem > 15){
					demoItem = 0;
				}
			}
		}

		if( demoItem == 0 ){
			showIntValue(INT_1_DIGIT, 20, 10);
		}
		if( demoItem == 1 ){
			showIntValue(INT_2_DIGIT, 20, 10);
		}
		if( demoItem == 2 ){
			showIntValue(INT_3_DIGIT, 20, 10);
		}
		if( demoItem == 3 ){
			showIntValue(INT_4_DIGIT, 20, 10);
		}

		if( demoItem == 4 ){
			showFloatValue(FLOAT_0_1_DIGIT, 20, 10);
		}
		if( demoItem == 5 ){
			showFloatValue(FLOAT_0_2_DIGIT, 20, 10);
		}
		if( demoItem == 6 ){
			showFloatValue(FLOAT_0_3_DIGIT, 20, 10);
		}

		if( demoItem == 7 ){
			showFloatValue(FLOAT_1_1_DIGIT, 20, 10);
		}
		if( demoItem == 8 ){
			showFloatValue(FLOAT_1_2_DIGIT, 20, 10);
		}
		if( demoItem == 9 ){
			showFloatValue(FLOAT_1_3_DIGIT, 20, 10);
		}

		if( demoItem == 10 ){
			showFloatValue(FLOAT_2_0_DIGIT, 20, 10);
		}
		if( demoItem == 11 ){
			showFloatValue(FLOAT_2_1_DIGIT, 20, 10);
		}
		if( demoItem == 12 ){
			showFloatValue(FLOAT_2_2_DIGIT, 20, 10);
		}

		if( demoItem == 13 ){
			showFloatValue(FLOAT_3_0_DIGIT, 20, 10);
		}
		if( demoItem == 14 ){
			showFloatValue(FLOAT_3_1_DIGIT, 20, 10);
		}

		if( demoItem == 15 ){
			showFloatValue(FLOAT_4_0_DIGIT, 20, 10);
		}

		/**/
	}

	return 0;
}

