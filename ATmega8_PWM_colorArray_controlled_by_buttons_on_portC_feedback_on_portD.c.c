#include <avr/io.h>
#include <util/delay.h>
//#include <avr/iom8.h>

//#include <avr/interrupt.h>
//#include <compat/deprecated.h>

#define DEFAULT_DELAY 20

#define MAX_PERCENTAGE 70

#define CH_RED		0
#define CH_BLUE   	2
#define CH_GREEN  	1

#define DispEI		PORTD |=  (1<<PD0)
#define DispEN		PORTD &= ~(1<<PD0)



void init(){   // 76543210
		DDRB = 0b11111111;
		PORTB = 0;
	  	DDRC  =  0b0000000;
  	  	PORTC  =  0b1111111;
  	  	DDRD  = 0xFF;
	  	PORTD = 0xFF;
	  	
	  	
	  //DDRB = (1<<PB0)|(1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7);
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

    TCCR1B |= (1 << CS11);
    // set prescaler to 8 and starts PWM


	//====================================================
	// 				PWM init of OCR1B (maybe)
	//====================================================

	 // TCCR1B
	 // Bit                  7     6       5            4      3   2         1      0
	 // Bit Name           COM1A1 COM1A0 COM1B1 COM1B0 -----        -----  WGM11   WGM10
	 // Initial Value      0       0       0            0      0      0      0       0
	 // changed to    1    1       1       1       0       0       1        0
	TCCR1A = 0b11110010;

	 // TCCR1B
	 // Bit                7           6   5         4       3       2       1       0
	 // Bit Name      ICNC1  ICES1  -----  WGM13   WGM12   CS12    CS11    CS10
	 // Initial Value    0     0      0      0       0       0       0       0
	 // changed to  0     0        0       1        1       0       0       1
	 // CS12,CS11,CS10 = (0,0,1) System clock, no division
	TCCR1B = 0b00011001;

	TCCR1B = 25;// 00011001
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
		OCR1A = 1023 - v;
	}
	else
	if(channel == 1){
		v = 0b1111111111 & value;
		OCR1B = 1023 - v;
	}

	if(channel == 2){
		v = 0b11111111 & value;
		OCR2 = v;
	}

}

void setPwmByte(unsigned char channel, unsigned char value){

	//if(value > 192)
	{
		value *= 0.3;
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

void showColorOnPWM(unsigned long rgb){
	
	setPwmByte(0, (( 0b111111110000000000000000 & rgb) >> 16));
	setPwmByte(1, (( 0b000000001111111100000000 & rgb) >>  8));
	setPwmByte(2, (( 0b000000000000000011111111 & rgb)));

}

void wait(unsigned short val) {

    while(val--) _delay_ms(2);

}

 
void _wait() {

    wait(DEFAULT_DELAY);

}


void onBtn1Pressed(unsigned char* p){

	*p = (*p >> 1);
	*p &= 0b1111111;

}

void onBtn2Pressed(unsigned char* p){

	unsigned char flag = 0;

	if(0b01000000 & *p){
		flag = 1;
	}
	
	*p = (*p << 1);
	
	if(flag == 0){
		*p += 1;
	}
	
	*p &= 0b1111111;
}

void keepValueInRange(char* value, unsigned char rangeMin, unsigned char rangeMax){
	if(*value <= rangeMin){
		*value = rangeMin;
	}
	if(*value > rangeMax){
		*value = rangeMax;
	}
}

int main(){

	init();
	initPWM3();

	setPwmByte(0, 0);
	setPwmByte(1, 0);
	setPwmByte(2, 0);

	unsigned long colors[] = {
		0x000000,
		0xFF0000,
		0xFFFF00,
		0x00FF00,
		0x00FFFF,
		0x0000FF,
		0xFF00FF
	};

	unsigned char bt1Pressed = 0;
	unsigned char bt2Pressed = 0;
	unsigned char bt3Pressed = 0;

	unsigned char state  = 0;	
	char colorId  = 0;	

	while(1){


		if(bt1Pressed == 0){
			//if((PIND>>5 & 0b1)){
			if((PINC>>3 & 0b1)){
				bt1Pressed = 1;
			}
		}else{
			//if((PIND>>5 & 0b1) == 0){
			if((PINC>>3 & 0b1) == 0){
				bt1Pressed = 0;
				onBtn1Pressed(&state);
				colorId--;
				keepValueInRange(&colorId, 0, 6);
				showColorOnPWM(colors[colorId]);
				wait(20);
			}
		}

		if(bt2Pressed == 0){
			//if((PIND>>7 & 0b1)){
			if((PINC>>5 & 0b1)){
				bt2Pressed = 1;
			}
		}else{
			//if((PIND>>7 & 0b1) == 0){
			if((PINC>>5 & 0b1) == 0){
				bt2Pressed = 0;
				onBtn2Pressed(&state);
				colorId++;
				keepValueInRange(&colorId, 0, 6);
				showColorOnPWM(colors[colorId]);
				wait(20);
			}
		}

		if(bt3Pressed == 0){
			//if((PIND>>6 & 0b1)){
			if((PINC>>4 & 0b1)){	
				bt3Pressed = 1;
			}
		}else{
			//if((PIND>>6 & 0b1) == 0){
			if((PINC>>4 & 0b1) == 0){
				bt3Pressed = 0;
				showColorOnPWM(0);
				state = 0;
				colorId = 0;
				wait(20);
			}
		}

		switch(colorId){
			case 0:
				PORTD = 0b01;
				break;
			case 1:
				PORTD = 0b101;
				break;
			case 2:
				PORTD = 0b1001;
				break;
			case 3:
				PORTD = 0b10001;
				break;
			case 4:
				PORTD = 0b100001;
				break;
			case 5:
				PORTD = 0b1000001;
				break;
			case 6:
				PORTD = 0b10000001;
				break;
			default:
				break;
		}
		//PORTD = 1 << state | 0b01;

		/*
		if(colorId >= 6){
			colorId = 0;
		}
		showColorOnPWM(colors[colorId]);/**/

		/*
		if(PIND & 0b00100000){
			PORTB |= 0b00001100;
		}else{
			PORTB &= ~(0b00001100);
		}	/**/

	}

	return 0;
}
