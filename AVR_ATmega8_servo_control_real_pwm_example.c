//-------------------------
#include <avr\io.h>
#include <avr\delay.h>

/**********************************************************************
 *    Control servo with standard PWM output on OCR1A (PB1)           *
 *    Device: ATmega8                                                 *
 *                                                                    *
 *    Value range for control servo (values for OCR1A):               *
 *         MIN:                                                       *
 *         MAX:                                                       *
 *                                                                    *
 *                      Boor Andras - 2016                            *
 *                                                                    *
 *********************************************************************/

int main(void) {

	//Port D pins as input
	DDRD=0x00;

	//Enable internal pull ups
	PORTD=0xFF;

	//Set PORTB1 pin as output
	DDRB=0xFF;

	//TOP=ICR1;
	//Output compare OC1A 8 bit non inverted PWM
	//Clear OC1A on Compare Match, set OC1A at TOP
	//Fast PWM
	//ICR1=20000 defines 50Hz PWM
	ICR1=20000;
	TCCR1A|=(0<<COM1A0)|(1<<COM1A1)|(0<<COM1B0)|(0<<COM1B1)|
	(0<<FOC1A)|(0<<FOC1B)|(1<<WGM11)|(0<<WGM10);

	TCCR1B|=(0<<ICNC1)|(0<<ICES1)|(1<<WGM13)|(1<<WGM12)|
	(0<<CS12)|(1<<CS11)|(0<<CS10);
	//start timer with prescaler 8

	unsigned int val = 10;	

	for (;;) {
		_delay_ms(100);
		if(val < 2000){
			OCR1A = val;
		}else{
			val = 0;
		}
		val+=10;
	}
}
//----------------------------------
