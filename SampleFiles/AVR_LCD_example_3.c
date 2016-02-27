
#include <avr/io.h>
#include <util/delay.h>

#define DPORT PORTB //Define Data port
#define DPDDR DDRB
#define CPORT PORTD //Define Signals port
#define CPDDR DDRD

#define RS PD6 //Signal Pins, Reset
#define EN PD7 //Signal Pins, Enable

//Pre-defining Commands
#define LCDClear 0x01 //Clears LCD Display
#define LCD8bit 0x38 //Sets up LCD in 8bit mode
#define LCDCursorOn 0x0f //Enables Cursor
#define LCDSeek00 0x80 //Seeks the pointer to the begeining


void LCD(char ch);
void LCDcmd(void);
void LCDInitialize(void);


int main()
{ 
	DPDDR=0xff;
	CPDDR=0xf0;
	_delay_ms(2000);
	LCDInitialize();
	LCD(‘C’);
	LCD(‘i’);
	LCD(‘r’);
	LCD(‘c’);
	LCD(‘u’);
	LCD(‘i’);
	LCD(‘t’);
	LCD(‘s’);
	LCD(‘ ’);
	LCD(‘T’);
	LCD(‘o’);
	LCD(‘d’);
	LCD(‘a’);
	LCD(‘y’);
	return 0;
}


void LCD(char ch)
{ 
	DPORT=ch; //Put values to ports
	CPORT=(1< _delay_us(10);
	CPORT=(1< _delay_us(45);
}


void LCDcmd(char ch)
{ 
	DPORT=ch;
	CPORT=(0< _delay_ms(10);
	CPORT=(0< _delay_ms(45);
	if(ch==0x01||ch==0x02) // If commands are LCD Clear or
	// LCDSeek00, delay 2mS
	_delay_ms(2);
}


void LCDInitialize(void)
{ 
	LCDcmd(LCD8bit);
	LCDcmd(LCDCursorOn);
	LCDcmd(LCDClear);
	LCDcmd(LCDSeek00);
}


