 /********************************************************************\
 *    Driver for 7+1 segment LED display @ 4 digits                   *
 *    Device: Custom, [4x7 base panel suggested]                      *
 *                                                                    *
 *    Tested with ADC channels:                                       *
 *      + ___ - OK?                                                   *
 *                                                                    *
 *                         Boor Andras - 2016                         *
 *                                                                    *
 *    https://www.youtube.com/watch?v=???????????                     *
 \********************************************************************/

//#define F_CPU 1000000

//TODO: need?
#include <avr/io.h>


#define PORT_OF_SEGM_A         
#define PORT_OF_SEGM_B         
#define PORT_OF_SEGM_C         
#define PORT_OF_SEGM_D         
#define PORT_OF_SEGM_E         
#define PORT_OF_SEGM_F         
#define PORT_OF_SEGM_G         
#define PORT_OF_SEGM_H         
#define PORT_OF_SEGM_DOT       PORT_OF_SEGM_H

#define PORT_OF_DIGIT_1         
#define PORT_OF_DIGIT_2         
#define PORT_OF_DIGIT_3         
#define PORT_OF_DIGIT_4         


#define PIN_OF_SEGM_A          
#define PIN_OF_SEGM_B          
#define PIN_OF_SEGM_C          
#define PIN_OF_SEGM_D          
#define PIN_OF_SEGM_E          
#define PIN_OF_SEGM_F          
#define PIN_OF_SEGM_G          
#define PIN_OF_SEGM_H          
#define PIN_OF_SEGM_DOT        

#define PIN_OF_DIGIT_1         
#define PIN_OF_DIGIT_2         
#define PIN_OF_DIGIT_3         
#define PIN_OF_DIGIT_4 


// Used to store states of segments in one variable
//                       ABCDEFGH             
uint8_t segmentValue = 0b00000000;

void setStateOfSegments(uint8_t value){
    //TODO
    if( value & 0b1000000 ){ //A
        
    }
}

unsigned char a;
 