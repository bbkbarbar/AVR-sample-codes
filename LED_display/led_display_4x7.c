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

// ======================================================================================================
// |                                           Configurations                                           |
// ======================================================================================================

#define USED_DIGITS					4

// removed h
//#define REPLACE_ZERO_FROM_BEGIN		1


// ======================================================================================================
// |                                          Macro definitions                                         |
// ======================================================================================================

//TODO: need?
#include <avr/io.h>
#include "led_display_4x7.h"

#ifndef DELAY_INCLUDED
    #include <util/delay.h>
    #define DELAY_INCLUDED
#endif

/*
#ifndef PORTS_FOR_LED_DISPLAY_ARE_DEFINED

 	// Define PORTs and PINs 
 	// for using LED display @ 4 digits

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
*/

#ifndef PORTS_FOR_LED_DISPLAY_ARE_DEFINED
	#define PORT_OF_SEGM_DOT		PORT_OF_SEGM_H
	#define PIN_OF_SEGM_DOT			PIN_OF_SEGM_H
#endif

#define SET_VALUE(port, pin, value)	 	( ((value) > 0)?( port |= (1 << pin) ):(port &= ~(1 << pin)) )

#define NONE				0
#define ALL					0xFF

#define NO_DOT 				0
#define DOT_NEEDED			1



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
// |                                          Private methods                                           |
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

/*
uint8_t setDotAfter(uint8_t sValue, uint8_t dotEnabled){
	uint8_t result = sValue;
	//                                       AB.....H                 AB.....H
	return ( (dotEnabled > 0) ? (result |= 0b00000001) : (result &= 0b11111110) );
} 
*/

void setDotAfter(uint8_t* pSegmentValue, uint8_t dotEnabled){
	if(dotEnabled > 0){
		//                  AB.....H
		*pSegmentValue |= 0b00000001;
	}else{
		//                  AB.....H
		*pSegmentValue &= 0b11111110;
	}
}


uint8_t* getSegmentPatternArray(uint16_t value){

	uint8_t segmentPatterns[USED_DIGITS];
	uint16_t tmp = 0;

	if((value <= 9999) && (value >= 0)){

		tmp = tmp/10; // 7
		segmentPatterns[3] = getSegmentValueForChar( (value - (tmp*10)) + '0'); // '8'
		value /= 10; // 7 (tmp = 7 too)

		tmp = tmp/10; // 0
		segmentPatterns[2] = getSegmentValueForChar( (value - (tmp*10)) + '0'); // '7'
		value /= 10; // 56 (tmp = 56 too)

		tmp = tmp/10; // 5
		segmentPatterns[1] = getSegmentValueForChar( (value - (tmp*10)) + '0'); // '0'
		value /= 10; // 5 

		segmentPatterns[0] = getSegmentValueForChar(  value             + '0'); // '0'

		//segmentPatterns = {'5', '6', '7', '8'}

	}else
	if(value > 9999){
		segmentPatterns[0] = 'T';
		segmentPatterns[1] = 'T';
		segmentPatterns[2] = 'T';
		segmentPatterns[3] = 'T';
	}else{
		segmentPatterns[0] = '_';
		segmentPatterns[1] = '_';
		segmentPatterns[2] = '_';
		segmentPatterns[3] = '_';
	}

	return &segmentPatterns;
}


void showSegmentPattern(uint8_t* segmentPatterns, uint8_t frameCount, uint8_t delayBetweenDigits){

	uint8_t frame;
	uint8_t currDigit = 0;
	
	for( frame = 0; frame < frameCount; frame++ ){
		for( currDigit = 0; currDigit < USED_DIGITS; currDigit++ ){

			if( segmentPatterns[currDigit] == 0){
				continue;
			}
			enableDigit( NONE );
			enableSegments( segmentPatterns[currDigit] );
			enableDigit( currDigit + 1 );
			wait(delayBetweenDigits);

		}
	}

}


// ======================================================================================================
// |                                          Useful methods                                            |
// ======================================================================================================

// Show given numberic value in a 4 digits display
// for given frameCount
// for given length of frames for digits
// e.g.:                    5678
void showIntValueWithDot(uint16_t value, uint8_t frameCount, uint8_t delayBetweenDigits, uint8_t needToShowDotAfterLastCharacter){

	uint16_t tmp = value;
	uint16_t digitVal = 0;

	uint8_t segmentPatterns[USED_DIGITS];

	/*
	 *  Determine the appropriate characters for each segment
	 */
	 //TODO: Try it out (in paper too) with values: 456, 78, 1, 0
	*segmentPatterns = getSegmentPatternArray(value);


	#ifndef REPLACE_ZERO_FROM_BEGIN
		if(REPLACE_ZERO_FROM_BEGIN > 0){

			uint8_t tmpCounter = 0;
			while( (tmpCounter < 3) && (segmentPatterns[tmpCounter] == '0') ){
				segmentPatterns[tmpCounter] = ' ';
				tmpCounter++;
			}

		}
	#endif


	if(needToShowDotAfterLastCharacter){
		setDotAfter( &(segmentPatterns[USED_DIGITS-1]), DOT_NEEDED);
	}


	/*
	 *  Segment value stored 
	 *  (if needed then 0-s from the begin replaced with ' ').
	 *  Start to show..
	 */
	showSegmentPattern(segmentPatterns, frameCount, delayBetweenDigits);

}


/*
 *  This function made to findSegment correct configuration of segments.
 *  Examples: 
 *       findSegment('A', 0b1111);
 *       findSegment('.', 0b0100);
 */
void findSegment(char c, uint8_t digits){
		
	enableSegments(NONE);

	SET_VALUE(PORT_OF_DIGIT_1, PIN_OF_DIGIT_1, (digits & 0b0001) );
	SET_VALUE(PORT_OF_DIGIT_2, PIN_OF_DIGIT_2, (digits & 0b0010) );
	SET_VALUE(PORT_OF_DIGIT_3, PIN_OF_DIGIT_3, (digits & 0b0100) );
	SET_VALUE(PORT_OF_DIGIT_4, PIN_OF_DIGIT_4, (digits & 0b1000) );


	switch (c) {
		case 'A' :
		case 'a' :
		    SET_VALUE(PORT_OF_SEGM_A, PIN_OF_SEGM_A, 1 );
			break;
		case 'B' :
		case 'b' :
		    SET_VALUE(PORT_OF_SEGM_B, PIN_OF_SEGM_B, 1 );
			break;
		case 'C' :
		case 'c' :
		    SET_VALUE(PORT_OF_SEGM_C, PIN_OF_SEGM_C, 1 );
			break;
		case 'D' :
		case 'd' :
		    SET_VALUE(PORT_OF_SEGM_D, PIN_OF_SEGM_D, 1 );
			break;
		case 'E' :
		case 'e' :
		    SET_VALUE(PORT_OF_SEGM_E, PIN_OF_SEGM_E, 1 );
			break;
		case 'F' :
		case 'f' :
		    SET_VALUE(PORT_OF_SEGM_F, PIN_OF_SEGM_F, 1 );
			break;
		case 'G' :
		case 'g' :
		    SET_VALUE(PORT_OF_SEGM_G, PIN_OF_SEGM_G, 1 );
			break;
		case 'H' :
		case 'h' :
		case '.' :
		case ',' :
		    SET_VALUE(PORT_OF_SEGM_H, PIN_OF_SEGM_H, 1 );
			break;
		default:
			enableSegments(ALL);
	}

}


// ======================================================================================================
// |                                         "Public" methods                                           |
// ======================================================================================================


void showIntValue(uint16_t value, uint8_t frameCount, uint8_t delayBetweenDigits){
	showIntValueWithDot(value, frameCount, delayBetweenDigits, NO_DOT);
}


void showFloatValue(float value, uint8_t frameCount, uint8_t delayBetweenDigits){
	
	if( value >= 1000.0f ){ // there is no place to show decimals
		showIntValueWithDot((uint16_t)value, frameCount, delayBetweenDigits, DOT_NEEDED);
		return;
	}

	uint8_t segmentPatterns[USED_DIGITS]; 


	if( value >=  100.0f ){ // 100,0 .. 999,9 -> 1 decimal place
		// *= 10
		*segmentPatterns = getSegmentPatternArray( (value * 10) );
		setDotAfter( &(segmentPatterns[2]), DOT_NEEDED);

	}else
	if( value >=   10.0f ){ //  10,0 ..  99,99 -> 2 decimal place
		// *= 100              ->        9999
		*segmentPatterns = getSegmentPatternArray( (value * 100) );
		setDotAfter( &(segmentPatterns[1]), DOT_NEEDED);

	}else
	if( value >=    1.0f ){ //   1,0 ..   9,999 -> 3 decimal place
		// *= 1000             ->         9999
		*segmentPatterns = getSegmentPatternArray( (value * 1000) );
		setDotAfter( &(segmentPatterns[0]), DOT_NEEDED);

	}else
	if( (value > 0.0f) && (value < 1.0f) ){ //  -> 3 decimal place, starts with 0
		//                       0,512  * 1000 => 0512 => _512
		*segmentPatterns = getSegmentPatternArray( (value * 1000) );  // "0512" 
		//segmentPatterns[0] = getSegmentValueForChar('0');           
		setDotAfter( &(segmentPatterns[0]), DOT_NEEDED);              // "0.512"
	}

}
