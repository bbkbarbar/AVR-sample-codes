/*
* main.c
* author : gtk, uprog@tvn.hu
* 2006. szept 26.
*
* MCU: ATMega8
* Pelda vertical scroll-ra sajat karakterekkel.
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
#define  CNT1_THRESHOLD  60
#define  CNT3_THRESHOLD  20

unsigned char i = 0, j = 0, n = 0, ch;
volatile unsigned int cnt1 = 0, cnt3 = 0;
unsigned char cnt3_flag = 0;
uint8_t *p = 0;


#define ROWS 6
#define COLLUMNS 8

const uint8_t array2d[ROWS][COLLUMNS] PROGMEM = {
  {143, 144, 144, 142, 129, 129, 158, 128},	//S
  {128, 128, 142, 144, 144, 145, 142, 128},	//c
  {128, 128, 150, 153, 144, 144, 144, 128},	//r
  {128, 128, 142, 145, 145, 145, 142, 128},	//o
  {140, 132, 132, 132, 132, 132, 142, 128},	//l
  {140, 132, 132, 132, 132, 132, 142, 128}	//l
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
  if (cnt3_flag)
    {
      cnt3++;
    }
}


int
main ()
{
  DDRD = 0x00;
  PORTD = 0xff;

  lcd_init ();

  /*display on, cursor & blink off */
  lcd_control (1, 0, 0);
  timer1_init ();
  lcd_cls ();
  lcd_clear_CRGAM ();
  //az elso sorba irunk
  lcd_putstr ("Vertical", LCD_FIRST_LN_ADDR);
  
/* main -loop */
  for (;;)
    {
      if (cnt1 == CNT1_THRESHOLD)
	{
	  cnt1 = 0;
	  cnt3_flag = 1;
	  //clear second line
	  for (ch = 0; ch < 20; ch++)
	    {
	      lcd_set_DDRAM_addr (LCD_SECND_LN_ADDR + ch);
	      lcd_putch (' ');
	    }
	  /* 
	   * array2d: custom chars array
	   * ROWS: number of chars
	   * 30: vertical delay in ms
	   * 0: horiz. delay
	   * LCD_FIRST_LN_ADDR + 9 : ddram addr.
	   * 1: set CGRAM clear mode; 0: no CGRAM clear 
	   */
	   
	  //nem clear modban erdekes hatast kelt ;-)
	  lcd_vertical_scroll (array2d, ROWS, 40, 0 /* delay ms */ ,
			       LCD_FIRST_LN_ADDR + 9, 0);
	}

      if (cnt3 == CNT3_THRESHOLD)
	{
	  cnt3 = 0;
	  cnt3_flag = 0;
	  
	  lcd_putstr ("Is COOL!", LCD_SECND_LN_ADDR + 5);
	}
    }
  return 0;
}
