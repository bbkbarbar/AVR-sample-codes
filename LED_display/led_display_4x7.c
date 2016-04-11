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


#define SET_VALUE(port, pin, value)	 	( (value>0)?( port |= (1<<pin) ):(port &= ~(1<<pin)) )


// Used to store states of segments in one variable
//                       ABCDEFGH             
uint8_t segmentValue = 0b00000000;


void setSegments(uint8_t value){ //e.g.: 0b01000010 //B+G
    
    //													A	
    SET_VALUE(PORT_OF_SEGM_A, PIN_OF_SEGM_A, (value & 0b10000000) );
    //													 B	
    SET_VALUE(PORT_OF_SEGM_B, PIN_OF_SEGM_B, (value & 0b01000000) );
    //													  C	
    SET_VALUE(PORT_OF_SEGM_C, PIN_OF_SEGM_C, (value & 0b00100000) );
    //													   D
    SET_VALUE(PORT_OF_SEGM_D, PIN_OF_SEGM_D, (value & 0b00010000) );
    //														E
    SET_VALUE(PORT_OF_SEGM_E, PIN_OF_SEGM_E, (value & 0b00001000) );
    //														 F
    SET_VALUE(PORT_OF_SEGM_F, PIN_OF_SEGM_F, (value & 0b00000100) );
    //														  G
    SET_VALUE(PORT_OF_SEGM_G, PIN_OF_SEGM_G, (value & 0b00000010) );
    //														   H
    SET_VALUE(PORT_OF_SEGM_H, PIN_OF_SEGM_H, (value & 0b00000001) );

}
 
