 /********************************************************************\
 *    Driver for 7+1 segment LED display @ 4 digits                   *
 *    Device: Custom, [4x7 base panel suggested]                      *
 *                                                                    *
 *    Tested with .............                                       *
 *      + ___ - OK?                                                   *
 *                                                                    *
 *                         Boor Andras - 2016                         *
 *                                                                    *
 *    https://www.youtube.com/watch?v=???????????                     *
 \********************************************************************/

//#define F_CPU 1000000

//TODO: need?
#include <avr/io.h>

#ifndef DELAY_INCLUDED
    #include <util/delay.h>
    #define DELAY_INCLUDED
#endif

#ifndef PORTS_FOR_LED_DISPLAY_ARE_DEFINED

 	/*
 	 * Define PORTs and PINs 
 	 * for using LED display @ 4 digits
 	 */

	#define PORT_OF_SEGM_A			PORTD
	#define PORT_OF_SEGM_B			PORTD
	#define PORT_OF_SEGM_C			PORTD
	#define PORT_OF_SEGM_D			PORTD
	#define PORT_OF_SEGM_E			PORTD
	#define PORT_OF_SEGM_F			PORTD
	#define PORT_OF_SEGM_G			PORTD
	#define PORT_OF_SEGM_H			PORTD
	#define PORT_OF_SEGM_DOT		PORT_OF_SEGM_H

	#define PORT_OF_DIGIT_1			PORTB 
	#define PORT_OF_DIGIT_2			PORTB 
	#define PORT_OF_DIGIT_3			PORTB
	#define PORT_OF_DIGIT_4			PORTB


	#define PIN_OF_SEGM_A			PD0
	#define PIN_OF_SEGM_B			PD1
	#define PIN_OF_SEGM_C			PD2
	#define PIN_OF_SEGM_D			PD3
	#define PIN_OF_SEGM_E			PD4
	#define PIN_OF_SEGM_F			PD5
	#define PIN_OF_SEGM_G			PD6
	#define PIN_OF_SEGM_H			PD7
	#define PIN_OF_SEGM_DOT			PD7

	#define PIN_OF_DIGIT_1			PB4
	#define PIN_OF_DIGIT_2			PB5
	#define PIN_OF_DIGIT_3			PB6
	#define PIN_OF_DIGIT_4			PB7

 	#define PORTS_FOR_LED_DISPLAY_ARE_DEFINED
 #endif


#define SET_VALUE(port, pin, value)	 	( ((value) > 0)?( port |= (1 << pin) ):(port &= ~(1 << pin)) )

#define NONE						0

#define USED_DIGITS					4


// Used to store states of segments in one variable
//                       ABCDEFGH             
uint8_t segmentValue = 0b00000000;



// ======================================================================================================
// |                                          Common methods                                            |
// ======================================================================================================

void wait(unsigned short val) {
    while(val--) _delay_ms(1);
}


// ======================================================================================================
// |                                           Basic methods                                            |
// ======================================================================================================

// Enable outputs for given segments
void enableSegments(uint8_t value){ //e.g.: 0b01000010 //B+G
    
    //                                                  A	
    SET_VALUE(PORT_OF_SEGM_A, PIN_OF_SEGM_A, (value & 0b10000000) );
    //                                                   B	
    SET_VALUE(PORT_OF_SEGM_B, PIN_OF_SEGM_B, (value & 0b01000000) );
    //                                                    C	
    SET_VALUE(PORT_OF_SEGM_C, PIN_OF_SEGM_C, (value & 0b00100000) );
    //                                                     D
    SET_VALUE(PORT_OF_SEGM_D, PIN_OF_SEGM_D, (value & 0b00010000) );
    //                                                      E
    SET_VALUE(PORT_OF_SEGM_E, PIN_OF_SEGM_E, (value & 0b00001000) );
    //                                                       F
    SET_VALUE(PORT_OF_SEGM_F, PIN_OF_SEGM_F, (value & 0b00000100) );
    //                                                        G
    SET_VALUE(PORT_OF_SEGM_G, PIN_OF_SEGM_G, (value & 0b00000010) );
    //                                                         H
    SET_VALUE(PORT_OF_SEGM_H, PIN_OF_SEGM_H, (value & 0b00000001) );

}

// Enable output for given digit
void enableDigit(uint8_t digit){

	if(digit <= USED_DIGITS ){

		SET_VALUE(PORT_OF_DIGIT_1, PIN_OF_DIGIT_1, 0 );
		SET_VALUE(PORT_OF_DIGIT_2, PIN_OF_DIGIT_2, 0 );
		SET_VALUE(PORT_OF_DIGIT_3, PIN_OF_DIGIT_3, 0 );
		SET_VALUE(PORT_OF_DIGIT_4, PIN_OF_DIGIT_4, 0 );

		switch(digit) {

			case NONE :
				return;

			case 1 :
				SET_VALUE(PORT_OF_DIGIT_1, PIN_OF_DIGIT_1, 1 );
				return;

			case 2 :
				SET_VALUE(PORT_OF_DIGIT_2, PIN_OF_DIGIT_2, 1 );
				return;

			case 3 :
				SET_VALUE(PORT_OF_DIGIT_3, PIN_OF_DIGIT_3, 1 );
				return;

			case 4 :
				SET_VALUE(PORT_OF_DIGIT_4, PIN_OF_DIGIT_4, 1 );
				return;
		}

	}else{
		/*
		 * In other cases show the roblem with using all digit in same time.
		 */
		SET_VALUE(PORT_OF_DIGIT_1, PIN_OF_DIGIT_1, 1 );
		SET_VALUE(PORT_OF_DIGIT_2, PIN_OF_DIGIT_2, 1 );
		SET_VALUE(PORT_OF_DIGIT_3, PIN_OF_DIGIT_3, 1 );
		SET_VALUE(PORT_OF_DIGIT_4, PIN_OF_DIGIT_4, 1 );
	}

}

// Returns a "segmentValue" for given charachter
uint8_t getSegmentValueForChar(char c){

	//   ABCDEFGH
	// 0b00000000;

	switch (c) {
		case '0' :
		case 'O' :
			//       ABCDEFGH
			return 0b11111100;
		case '1' :
			//       ABCDEFGH
			return 0b01100000;
		case '2' :
			//       ABCDEFGH
			return 0b11011010;
		case '3' :
			//       ABCDEFGH
			return 0b11110010;
		case '4' :
			//       ABCDEFGH
			return 0b01100110;
		case '5' :
			//       ABCDEFGH
			return 0b10110110;
		case '6' :
			//       ABCDEFGH
			return 0b10111110;
		case '7' :
			//       ABCDEFGH
			return 0b11100000;
		case '8' :
			//       ABCDEFGH
			return 0b11111110;
		case '9' :
			//       ABCDEFGH
			return 0b11110110;
		case '_' :
			//       ABCDEFGH
			return 0b00010000;
		case '-' :
			//       ABCDEFGH
			return 0b00000010;
		case '|' :
			//       ABCDEFGH
			return 0b00001100;
		case 'o' :
			//       ABCDEFGH
			return 0b00111010;
		case 'H' :
			//       ABCDEFGH
			return 0b01101110;
		case 'L' :
			//       ABCDEFGH
			return 0b00011100;
		case 'E' :
			//       ABCDEFGH
			return 0b10011110;
		case 'P' :
			//       ABCDEFGH
			return 0b11001110;
		case 'T' :
			//       ABCDEFGH
			return 0b10000000;
		case '.' :
		case ',' :
			//       ABCDEFGH
			return 0b00000001;
		case ' ' :
			//       ABCDEFGH
			return 0b00000000;
	}

	//default
	//       ABCDEFGH
	return 0b11000100;

}

uint8_t setDotAfter(uint8_t sValue, uint8_t dotEnabled){
	uint8_t result = sValue;
	//                                       AB.....H                 AB.....H
	return ( (dotEnabled > 0) ? (result |= 0b00000001) : (result &= 0b11111110) );

}


// ======================================================================================================
// |                                          Useful methods                                            |
// ======================================================================================================

// Show given numberic value in a 4 digits display
// for given frameCount
// for given length of frames for digits
// e.g.:                    5678
void showIntValue(uint16_t value, uint8_t frameCount, uint8_t delayBetweenDigits){

	uint16_t tmp = value;
	uint16_t digitVal = 0;

	uint8_t segmentPatterns[USED_DIGITS];

	/*
	 *  Determine the appropriate characters for each segment
	 */
	 //TODO: Try it out (in paper too) with values: 456, 78, 1, 0
	if((value <= 9999) && (value >= 0)){

		tmp = tmp/10; // 567
		segmentPatterns[3] = getSegmentValueForChar( (value - (tmp*10)) + '0'); // '8'
		value /= 10; // 567 (tmp = 567 too)

		tmp = tmp/10; // 56
		segmentPatterns[2] = getSegmentValueForChar( (value - (tmp*10)) + '0'); // '7'
		value /= 10; // 56 (tmp = 56 too)

		tmp = tmp/10; // 5
		segmentPatterns[1] = getSegmentValueForChar( (value - (tmp*10)) + '0'); // '6'
		value /= 10; // 5 

		segmentPatterns[0] = getSegmentValueForChar(  value             + '0'); // '5'

		//segmentPatterns = {'5', '6', '7', '8'}
	}else
	if(value > 9999){
		segmentPatterns = {'T', 'T', 'T', 'T'};
	}else{
		segmentPatterns = {'_', '_', '_', '_'};
	}

}
