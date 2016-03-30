/**********************************************************************
 *                                                                    *
 *    Control servo with standard PWM output on OCR1A (PB1)           *
 *    Device: ATmega8                                                 *
 *                                                                    *
 *    Value range for control servo (values for OCR1A):               *
 *         MIN:  450  (approximately)                                 *
 *         MAX: 2400  (approximately)                                 *
 *         MID: 1460  (real middle position equal to avg(MIN,MAX))    *
 *                                                                    *
 *    SERVO_MAX value means "leftmost" (0 degree) position.           *
 *    SERVO_MIN value means "rightmost" (~180 degree) position.       *
 *                                                                    *
 *                      Boor Andras - 2016                            *
 *                                                                    *
 *********************************************************************/

#include <avr\io.h>

#define SERVO_OUTPUT_MIN 	 450
#define SERVO_OUTPUT_MAX 	2400


#define SERVO_LEFT			SERVO_OUTPUT_MAX
#define SERVO_RIGHT			SERVO_OUTPUT_MIN
#define SERVO_MID 			1460

#ifdef SERVO_CONTROL_FINE
 	#include <util/delay.h>
 	#define DELAY_INCLUDED
	#define FINE_ROTATION_DELAY      10
	unsigned short lastServoPosition;
	unsigned short FINE_THRESHOLD = 100;
	unsigned short rotation_step =   20;
#endif

void initServoControl(){
	//Output pin set for PWM output
	DDRB |= 0b00000010; //PB1 (pin of OCR1A) set as output for SERVO_OUTPUT

	//TOP=ICR1;
	//Output compare OC1A 8 bit non inverted PWM
	//Clear OC1A on Compare Match, set OC1A at TOP
	//Fast PWM
	//ICR1=20000 defines 50Hz PWM
	ICR1 = 20000;
	TCCR1A |= (0<<COM1A0) | (1<<COM1A1) | (0<<COM1B0) | (0<<COM1B1) |
	          (0<<FOC1A) | (0<<FOC1B) | (1<<WGM11) | (0<<WGM10);

	//start timer with prescaler 8
	TCCR1B |= (0<<ICNC1) | (0<<ICES1) | (1<<WGM13) |(1<<WGM12) |
	(0<<CS12) | (1<<CS11) | (0<<CS10);
}

void setServoPosition(unsigned short position){
	OCR1A = position;
	#ifdef SERVO_CONTROL_FINE
		lastServoPosition = position;
	#endif
}

#ifdef SERVO_CONTROL_FINE

unsigned short abs(short a){
	return (a > 0)?a:(-1*a);
}

void setServoPositionFine(unsigned short wantedPosition){
	if(OCR1A > wantedPosition){
		if(OCR1A - wantedPosition > FINE_THRESHOLD){
			OCR1A = (OCR1A - rotation_step);
			for(int i=0; i< FINE_ROTATION_DELAY; i++){
				_delay_ms(1);
			}
			setServoPositionFine(wantedPosition);
		}else{
			
		}
	}
	OCR1A = positionToSet;
	lastServoPosition = wantedPosition;
}
#endif
