#define SEGMENT_DEFINITIONS_C_INCLUDED

// TARGET pinout configuration
//#define TARGET_PINOUT_USED
//							  76543210								D = 0-4		B = TOP3
#define A(x) if(x) PORTB |= 0b00001000; else PORTB &= 0b11110111	//	pb3
#define B(x) if(x) PORTB |= 0b00010000; else PORTB &= 0b11101111	//	pb4
#define C(x) if(x) PORTB |= 0b00000010; else PORTB &= 0b11111101	//	pb1
#define D(x) if(x) PORTB |= 0b00000001; else PORTB &= 0b11111110	//	pb0
#define P(x) if(x) PORTB |= 0b00000100; else PORTB &= 0b11111011	//	pb2

#define E(x) if(x) PORTD |= 0b10000000; else PORTD &= 0b01111111	//	pd7
#define F(x) if(x) PORTD |= 0b01000000; else PORTD &= 0b10111111	//	pd6
#define G(x) if(x) PORTD |= 0b00100000; else PORTD &= 0b11011111	//	pd5
#define SEGMENTS_DEFINED

/*
//			  BAPCD
PORTB |= 0b00011011;
//		   EFG
PORTB |= 0b11100000;
*/


#define CLEAN_ALL_SEGMENTS   PORTB &= 0b11100000; PORTD &= 0b00011111
#define TURN_ON_ALL_SEGMENTS PORTB |= 0b00011111; PORTD |= 0b11100000


void setAllSegment(char newState){

	if(newState){
		TURN_ON_ALL_SEGMENTS;
	}else{
		CLEAN_ALL_SEGMENTS;
	}
	
	/*
	A(newState);
	B(newState);
	C(newState);
	D(newState);
	E(newState);
	F(newState);
	G(newState);
	P(newState);
	/**/

}

#define TURN_ON_ALL_DIGITS  PORTC |= 0b00011110
#define TURN_OFF_ALL_DIGITS PORTC &= 0b11100001

#define CLEAN_DIGITS PORTC &= 0b11100001
#define CLEAN CLEAN_DIGITS; CLEAN_ALL_SEGMENTS
#define DIGIT(d,s) if(d == 4) if(s)	PORTC |= 0b00000010; else PORTC &= 0b11111101; else if(d == 3) if(s) PORTC |= 0b00000100; else PORTC &= 0b11111011; else if(d == 2) if(s) PORTC |= 0b00001000; else PORTC &= 0b11110111; else if(d == 1) if(s) PORTC |= 0b00010000; else PORTC &= 0b11101111
#define SETALLDIGIT(s) if(s) TURN_ON_ALL_DIGITS; else TURN_OFF_ALL_DIGITS
//#define SETALLDIGIT(s) DIGIT(1,s); DIGIT(2,s); DIGIT(3,s); DIGIT(4,s)

