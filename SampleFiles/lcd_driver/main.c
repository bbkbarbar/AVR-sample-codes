/*
* main.c
* author : gtk, uprog@tvn.hu
* 2006. szept 26.
*
* Pelda sajat karakterek animalasara.
* Megj: a sajat karakter bytejai PROGMEMbe(Flash) irodnak.
* MCU: ATMega8
*
* Forditas, egetes:
*
* make clean
* make all
* make writefuse
* make program
*/

#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "simple_driver.h"

//cnt1,2 kuszobertekei
#define  CNT1_THRESHOLD  2
#define  CNT2_THRESHOLD  7

unsigned char i = 0, j = 0;
volatile unsigned int cnt1, cnt2;
unsigned char n = 0;

//custom characters 
const uint8_t anim[4][8] PROGMEM = {
  {0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00},
  {0x01, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00;}
};

const uint8_t man[2][8] PROGMEM = {
  {0x04, 0x0E, 0x15, 0x04, 0x04, 0x0A, 0x0A, 0x0A},
  {0x15, 0x0E, 0x04, 0x04, 0x04, 0x1B, 0x00, 0x00}
};


void
timer1_init ()
{
  TCCR1B |= (1 << CS11);	//presc: 8; F_CPU = 8 000 000Hz;
  //ovf.int time = timer counter max / (fosc/prescaler) 
  // = 65535/(8 000 000/8) = 0,065535
  TIMSK |= (1 << TOIE1);	//timer1 ovf. bekapcsolva
  sei ();			//global int. enable
}

/* ovf 0.065 sec . 
* 'idoosztas . 
*/
SIGNAL (SIG_OVERFLOW1)
{
  cnt1++;
  cnt2++;
}

#include <stdlib.h>
#include <avr/iom8.h>
int
main ()
{
  DDRD = 0x00;
  PORTD = 0xff;

  lcd_init ();
  /*display on, cursor & blink off */
  lcd_control (1, 0, 0);
  lcd_cls ();
  lcd_putstr ("Animate is cool !", LCD_FIRST_LN_ADDR + 2);

  timer1_init ();

/* main -loop */
  for (;;)
    {
      // 2*0.065 Sec-kent vegrehajtodik az 1. es 3. animacio egy reszlete

      if (cnt1 == CNT1_THRESHOLD)
	{
	  cnt1 = 0;
	  //1. animacio 
	  if (i > 3)
	    {
	      i = 0;
	    }
	  uint8_t buf[8];

	  for (n = 0; n < 8; n++)
	    {
	      buf[n] = pgm_read_byte_near (&anim[i][n]);
	    }
	    i++;
	  lcd_put_custom_char (0x00, buf);	//CGRAM 0x00 cimre beirjuk a sajat karaktert.
	  lcd_set_DDRAM_addr (LCD_FIRST_LN_ADDR);	//vissza DDRAMhoz, elso sor 1 karakterehez
	  lcd_putch (0x00);	//megjelenitjuk a CGRAM 0x00 cimen levo karaktert.

	  //2. animacio
	  lcd_set_DDRAM_addr (LCD_FIRST_LN_ADDR + 19);	//masodik sor 8. karakterehez
	  lcd_putch (0x00);	//megjelenitjuk a CGRAM 0x00 cimen levo karaktert.
	}

      // 7 * 0.065 Sec(OVF) -kent vegrehajtodik a 3. animacio egy reszlete

      if (cnt2 == CNT2_THRESHOLD)
	{
	  cnt2 = 0;
	  //3. animacio
	  if (j > 1)
	    {
	      j = 0;
	    }
	  uint8_t buf[8];

	  //read 8byte(one char) from FLASH
	  for (n = 0; n < 8; n++)
	    {
	      buf[n] = pgm_read_byte_near (&man[j][n]);
	    }
	    j++;
	  lcd_put_custom_char (0x02, buf);
	  lcd_set_DDRAM_addr (LCD_SECND_LN_ADDR);
	  lcd_putch (0x02);
	}
    }
  return 0;
}
