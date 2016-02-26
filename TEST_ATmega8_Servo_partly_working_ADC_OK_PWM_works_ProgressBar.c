#include <avr/io.h>
#include <util/delay.h>

#define	DEFAULT_DELAY 100

#define UP		1
#define DOWN	1


void wait(unsigned short val) {

    while(val--) _delay_ms(1);

}


void _wait(){
	_delay_ms(DEFAULT_DELAY);
}


void initPWM3(){

	//====================================================
	// 				PWM init of OCR2 (maybe)
	//====================================================
	DDRB |= (1 << DDB3);
    // PB3 is now an output

    OCR2 = 128;
	// set PWM for 50% duty cycle


    TCCR2 |= (1 << COM21);
    // set none-inverting mode

    TCCR2 |= (1 << WGM21) | (1 << WGM20);
    // set fast PWM Mode

    TCCR2 |= (1 << CS21);
    // set prescaler to 8 and starts PWM

	// End of PWM init



	//====================================================
	// 				PWM init of OCR1A (maybe)
	//====================================================
    OCR1A = 0x01FF;
    // set PWM for 50% duty cycle @ 10bit


    TCCR1A |= (1 << COM1A1);
    // set none-inverting mode

    TCCR1A |= (1 << WGM11) | (1 << WGM10);
    // set 10bit phase corrected PWM Mode

    TCCR1B |= (1 << CS12);			// ORIG: TCCR1B |= (1 << CS11);
    // set prescaler to 8 and starts PWM


	//====================================================
	// 				PWM init of OCR1B (maybe)
	//====================================================

	// TCCR1B
	// Bit                  7     6       5       4      3      2      1      0
	// Bit Name           COM1A1 COM1A0 COM1B1 COM1B0  -----  -----  WGM11   WGM10
	// Initial Value      0       0       0       0      0      0      0      0
	// changed to         1       1       1       1      0      0      1      0
	TCCR1A = 0b11110010;

	// TCCR1B
	// Bit              7     6     5       4       3       2       1       0
	// Bit Name      ICNC1  ICES1  -----  WGM13   WGM12   CS12    CS11    CS10
	// Initial Value    0     0      0      0       0       0       0       0
	// changed to       0     0      0      1       1       1       0       1
	// CS12,CS11,CS10 = (0,0,1) System clock, no division
	TCCR1B = 0b00011010;

	//TCCR1B = 25;// 00011001
	ICR1 = 1023 ; // 10 bit resolution
	OCR1A = 511; // vary this value between 0 and 1024 for 10-bit

	OCR1B = 511; // vary this value between 0 and 1024 for 10-bit

	//=================================


	/*
	 *  PWM init OCR2
	 */
	 /*
	DDRB |= (1 << DDB3);
    // PB3 is now an output

    OCR2 = 128;
	// set PWM for 50% duty cycle


    TCCR2 |= (1 << COM21);
    // set none-inverting mode

    TCCR2 |= (1 << WGM21) | (1 << WGM20);
    // set fast PWM Mode

    TCCR2 |= (1 << CS21);
    // set prescaler to 8 and starts PWM
	/**/
	// End of PWM init

	OCR1A = 0;
	OCR1B = 0;
	OCR2 = 0;
	
}


void setPwmOut(unsigned char channel, unsigned int value){

	unsigned int v;

	if(channel == 0){
		v = 0b1111111111 & value;
		OCR1A = 1024 - v;
	}
	else
	if(channel == 1){
		v = 0b1111111111 & value;
		OCR1B = 1024 - v;
	}

	if(channel == 2){
		v = 0b11111111 & value;
		OCR2 = v;
	}

}

void setPwmByte(unsigned char channel, unsigned char value){

	//if(value > 192)
	{
		//value *= 0.3;
	}

	if(channel == 3){
		setPwmByte(0, value);
		setPwmByte(1, value);
		setPwmByte(2, value);
	}
	else
	if((channel == 0) || (channel == 1)){
		setPwmOut(channel, value * 4);
	}
	else{
		setPwmOut(channel, value);
	}

}



/*==========================================================================*
 *							 							   					*
 *			 			  "ProgressBar" on portD			   				*
 *							 Boor Andras - 2016			   					*
 *							 							   					*
 *==========================================================================*/
void showByteValueOnBar(unsigned int val){
	
	if(val > 16){
		PORTD =         0b1;
	}
	if(val > 48){
		PORTD |=       0b10;	
	}
	if(val > 80){
		PORTD |=      0b100;
	}
	if(val > 112){
		PORTD |=     0b1000;
	}
	if(val > 144){
		PORTD |=    0b10000;
	}
	if(val > 176){
		PORTD |=   0b100000;
	}
	if(val > 208){
		PORTD |=  0b1000000;
	}
	if(val > 240){
		PORTD |= 0b10000000;
	}

}


void init(){   // 76543210
	DDRB  = 0b11111111;
	DDRC  =  0b0000000;
	DDRD  = 0b11111111;

	PORTC = 0;
	PORTD = 0x01;
	  	
}


/*==========================================================================*
 *							 							   					*
 *			 	ADC (10bit) (tested in channel 0 and channel 5)			   	*
 *							 Tested on ATmega8			   					*
 *							 							   					*
 *		  DDRC seems doesn't matter (it works when DDRC = 0b11101111)		*
 *							 							   					*
 *							 							   					*
 *							 Boor Andras - 2014			   					*
 *							 							   					*
 *==========================================================================*/


void initADC() {
    //         76543210
    ADMUX  = 0b01000000;
    ADCSRA = 0b10000111;
} 


uint16_t readADC(uint8_t ch) {

    ADMUX = (ADMUX & 0b11110000) | ch;
//  01000001    ADMUX jelenlegi állapota (1-es ADC csatorna beállítva)
//& 11110000    ezzel toroljuk az elozo portok kivalasztast
//= 01000000    eredmenynek kapjuk az eredeti ADMUX beallitast
//| 00000101    "rairjuk" az ADC csatornat
//= 01000101    
    ADCSRA|=(1<<ADSC);          // konverzió elindítás
    while(ADCSRA & (1<<ADSC));  // várás az átalakításra

    return (ADCL | (ADCH<<8));  // adc érték visszaadása
}


int main(){

	init();
	initPWM3();
	//PORTC = 0;
	initADC();

	unsigned int value = 0;
	uint16_t     adc;

	while(1){

		value = readADC(0);
		value = (value / 4);


		showByteValueOnBar(value);		
		setPwmByte(0, value/8);
		setPwmByte(1, value);
		setPwmByte(2, (255-value));

		if((value < 165) && (value > 135)){
			PORTB |= (1<<PINB5);
	        _delay_ms(1);
	        adc = value*3;
	        while(adc--) _delay_us(3.9); //1000/255
	        PORTB &= ~(1<<PINB5);	
		}else{
			PORTB &= ~(1<<PINB5);
		}	

	}

	return 0;

}
