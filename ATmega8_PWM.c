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



void init(){// 76543210
  	  DDRD = 0b11111111;
	  DDRC =  0b0000000;
	  PORTC = 0b1111111;
	  DDRB = 0b11111111;
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


void wait(unsigned short val) {
//-------------------------------------
    while(val--) _delay_ms(2);
}

 
void _wait() {
//-------------------------------------
    wait(DEFAULT_DELAY);
}


void pwmFade(){

	int i;

	for(i=0; i<1024; i+=5){
		//PORTD = i/10;				
		OCR1B = i;
		wait(1);
	}	
	for(i=0; i<1024; i+=5){
		//PORTD = i/10;				
		OCR1A = i;
		wait(1);
	}	
	for(i=0; i<1024; i+=5){
		//PORTD = i/10;				
		OCR2 =  ((int)(( (float)i / 4)));
		wait(1);
	}
	
	for(i=1023; i>=0; i-=5){
		//PORTD = i/10;				
		OCR1B = i;
		wait(1);
	}	
	OCR1B = 0;
	for(i=1023; i>=0; i-=5){
		//PORTD = i/10;				
		OCR1A = i;
		wait(1);
	}
	OCR1A = 0;
	for(i=1023; i>=0; i-=5){
		//PORTD = i/10;				
		OCR2 =  ((int)(( (float)i / 4)));
		wait(1);
	}
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
		if(channel == 0){
		//	PORTB &= 00011111;
		//	PORTB |= 00100000;
		}
		else{
		//	PORTB &= 00011111;
		//	PORTB |= 01000000;
		}
		PORTD = value;
	}
	else{
		setPwmOut(channel, value);
		//PORTB |= 10000000;
		//PORTD = value;
	}

	if(PINC & 0b000100){
		PORTB |= 0b00100000;
	}else{
		PORTB &=  ~(0b00100000);
	}

}


void changeOrder(unsigned short val) {
	
}


void showColorOnPWM(unsigned long rgb){
	
	setPwmByte(0, (( 0b111111110000000000000000 & rgb) >> 16));
	setPwmByte(1, (( 0b000000001111111100000000 & rgb) >>  8));
	setPwmByte(2, (( 0b000000000000000011111111 & rgb)));

}

volatile int state = 0;

void onPC3Pressed(unsigned char* p){
	if(*p == 0){
		PORTD = 0b00010001;
	}
	if(*p == 1){
		PORTD = 0b00000001;
	}
	if(*p == 2){
		PORTD = 0b00000001;
	}
	if(*p == 3){
		PORTD = 0b00000001;
	}

	*p++;

	if(*p >= 4){
		*p = 0;
	}
}

int main(){

	init();

	// Ask for 50Hz (20ms) PWM signal (ms count should be halved)
	//ICR1 = 20000/2 ;

	// Center both servos
	//OCR1A = 1500/2 ;
	//OCR1B = 1500/2 ;

	// Ask for non-inverted PWM on OC1A and OC1B
	//TCCR1A = (1 << COM1A1) | (1 << COM1B1);

	// Configure timer 1 for Phase and Frequency Correct PWM mode, with no prescaling
	//TCCR1B = (1 << WGM13) | (1 << CS10);

	initPWM3();

		PORTB = 0;
		PORTD = 0;
		int j, i;
		int tmp;	

		setPwmByte(3, 0);

		/*
		unsigned long arr[] = {
			0xFF0000,
			0xFF5500,
			0xFFAA00,
			0xFFFF00,
			0xAAFF00,
			0x55FF00,
			0x00FF00,
			0x0000FF,
			0xFFFF00,
			0xFF00FF,
			0x00FFFF,
			0xFFFFFF
		};	/**/

		// for(j=0; j<255; j++){
		// 	setPwmByte(0, j);
		// }
		// wait(50);
		// for(j=255; j>=0; j--){
		// 	setPwmByte(0, j);
		// }
		// wait(50);

		// for(j=0; j<255; j++){
		// 	setPwmByte(1, j);
		// }
		// wait(50);
		// for(j=255; j>=0; j--){
		// 	setPwmByte(1, j);
		// }
		// wait(50);

		// for(j=0; j<255; j++){
		// 	setPwmByte(2, j);
		// }
		// wait(50);
		// for(j=255; j>=0; j--){
		// 	setPwmByte(2, j);
		// }
		// wait(50);


		// for(j=0; j<255; j++){
		// 	setPwmByte(0, j);
		// }
		// wait(50);

		unsigned char isPressed1 = 0;
		unsigned char isPressed2 = 0;
		unsigned char isPressed3 = 0;

		unsigned char s = 0;

		while(1){
			//PORTB = 0;
			PORTD = 0;
			

			if(isPressed3 == 0){

				if(PINC & 0b000100 == 0){
					isPressed3 = 1;
					
				}

			}else{
				if(PINC & 0b000100 == 1){
					onPC3Pressed(&s);
					isPressed3 = 0;
				}
			}
			
			// for(j=0; j<255; j++){
			// 	setPwmByte(1, j);
			// }
			// wait(150);
			// for(j=255; j>=0; j--){
			// 	setPwmByte(0, j);
			// }
			// wait(150);
			// for(j=0; j<255; j++){
			// 	setPwmByte(2, j);
			// }
			// wait(150);
			// for(j=255; j>=0; j--){
			// 	setPwmByte(1, j);
			// }
			// wait(150);
			// for(j=0; j<255; j++){
			// 	setPwmByte(0, j);
			// }
			// wait(150);
			// for(j=255; j>=0; j--){
			// 	setPwmByte(2, j);
			// }
			// wait(150);



			/*
			for(i=0; i<1024; i+=10){
				//PORTB = i;
				//PORTD = 255-i;

				PORTD = i/10;
				OCR2 =  255-((int)(( (float)i / 4)));
				OCR1A = i;
				OCR1B = 1024-i;
				
				//wait(1);	
				
			}	

			for(i=1023; i>=0; i-=10){
				//PORTB = i;
				//PORTD = 255-i;

				PORTD = i/10;
				OCR2 =  255-((int)(( (float)i / 4)));
				OCR1A = i;
				OCR1B = 1024-i;
				
				//wait(1);	
				
			}
			/**/


			

			
			
			/*
			OCR1A = 0;
			wait(50);

			for(i=MAX_PERCENTAGE; i>=0; i--){
				//PORTB = i;
				//PORTD = 255-i;
				
				PORTD = i/10;
				OCR2 =  (int)(( (float)i / 100) *  255);
				OCR1A = (int)(( (float)(MAX_PERCENTAGE-i) / 100) * 1024);
				OCR1B = (int)(( (float)(MAX_PERCENTAGE-i) / 100) * 1024);				

				if(i<50){
					wait(1);
				}else{
					wait(1);	
				}
			}
			OCR2 = 0;
			wait(50);
			/**/
			
			/*
			 * NR villogo
			 */	
			/*
			PORTB = 0b11000000;
			_wait();
			PORTB = 0b00110000;
			_wait();
			PORTB = 0b00001100;
			_wait();
			PORTB = 0b00000011;
			_wait();
			PORTB = 0;
			PORTD = 0b11000000;
			_wait();
			PORTD = 0b00110000;
			_wait();
			PORTD = 0b00001100;
			_wait();
			PORTD = 0b00000011;
			_wait();
			PORTD = 0;
			PORTD = 0b00000011;
			_wait();
			PORTD = 0b00001100;
			_wait();					
			PORTD = 0b00110000;
			_wait();		
			PORTD = 0b11000000;
			_wait();		
			PORTD = 0;
			PORTB = 0b00000011;
			_wait();
			PORTB = 0b00001100;
			_wait();
			PORTB = 0b00110000;
			_wait();
			
			/**/

			
			/**
			  *	Rendor villogo
			  */

			/*
			PORTB = 0b00001111;
			wait(5);
			PORTB = 0;
			wait(1);
			PORTB = 0b11110000;
			wait(5);
			//PORTB = 0;
			//wait(10);
			//PORTB = 0b11110000;
			wait(5);
			PORTB = 0;
			wait(1);
			PORTB = 0b00001111;
			wait(5);
			PORTB = 0;
			wait(50);

			
			PORTD = 0b11110000;
			wait(5);
			PORTD = 0;
			wait(1);
			PORTD = 0b00001111;
			wait(5);				
			//PORTD = 0;
			//wait(10);
			//PORTD = 0b00001111;
			wait(5);
			PORTD = 0;
			wait(1);
			PORTD = 0b11110000;
			wait(5);
			PORTD = 0;
			wait(50);/**/

		} /**/


return 0;
}
