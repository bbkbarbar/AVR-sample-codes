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
#define PORT_OF_ 


uint8_t res;
unsigned char a;
 