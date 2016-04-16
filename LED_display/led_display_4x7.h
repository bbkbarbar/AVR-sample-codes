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


// ======================================================================================================
// |                                           Configurations                                           |
// ======================================================================================================

#define REPLACE_ZERO_FROM_BEGIN		1

// ======================================================================================================
// |                                          Macro definitions                                         |
// ======================================================================================================

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
	
	#define PIN_OF_SEGM_A			PD6
	#define PIN_OF_SEGM_B			PD7
	#define PIN_OF_SEGM_C			PD4
	#define PIN_OF_SEGM_D			PD3
	#define PIN_OF_SEGM_E			PD2
	#define PIN_OF_SEGM_F			PD1
	#define PIN_OF_SEGM_G			PD0
	#define PIN_OF_SEGM_H			PD5


	#define PORT_OF_DIGIT_1			PORTB 
	#define PORT_OF_DIGIT_2			PORTB 
	#define PORT_OF_DIGIT_3			PORTB
	#define PORT_OF_DIGIT_4			PORTB
	
	#define PIN_OF_DIGIT_1			PB4
	#define PIN_OF_DIGIT_2			PB5
	#define PIN_OF_DIGIT_3			PB7
	#define PIN_OF_DIGIT_4			PB3

 	#define PORTS_FOR_LED_DISPLAY_ARE_DEFINED
 	 
#endif


// ======================================================================================================
// |                                          Common methods                                            |
// ======================================================================================================

void wait(unsigned short val);

// ======================================================================================================
// |                                          Private methods                                           |
// ======================================================================================================

/* 
 *  Enable outputs for given segments
 */
void enableSegments(uint8_t value);

/*
 *  Enable output for given digit
 */
void enableDigit(uint8_t digit);

/*
 *  Returns a "segmentValue" for given charachter
 */
uint8_t getSegmentValueForChar(char c);


void setDotAfter(uint8_t* pSegmentValue, uint8_t dotEnabled);


/*
 *  Get segmentParrern array from given integer value.
 */
uint8_t* getSegmentPatternArray(uint16_t value);


// ======================================================================================================
// |                                          Useful methods                                            |
// ======================================================================================================

/* 
 *  Shows segments according to the given segmentPattern array
 */
void showSegmentPatterns(uint8_t* segmentPatterns, uint8_t delayBetweenDigits);

/*
 *  Show given numberic value in a 4 digits display
 *  for given frameCount
 *  for given length of frames for digits
 *  It can 
 */
// e.g.:                    5678
void showIntValueWithDot(uint16_t value, uint8_t delayBetweenDigits, uint8_t needToShowDotAfterLastCharacter);


// ======================================================================================================
// |                                         "Public" methods                                           |
// ======================================================================================================

/*
 *  Show given numberic value in a 4 digits display
 *  for given frameCount
 *  for given length of frames for digits
 */
// e.g.:                    5678
void showIntValue(uint16_t value, uint8_t delayBetweenDigits);

/*
 *  Show given numberic value in a 4 digits display
 *  for given frameCount
 *  for given length of frames for digits
 */
// e.g.: value: 5678f or 9.875f or 75.21f or 7.123f or 0.123
void showFloatValue(float value, uint8_t frameCount, uint8_t delayBetweenDigits);
