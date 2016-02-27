 /***********************************************************
  *   Program:    simple_driver.c
  *   Version 	  1.2 
  *   Created:    2006. aug 28.
  *   Author:     gtk
  *               uprog@tvn.hu
  *   Comments:   HD44780 based LCD driver
  *   
  ************************************************************/

#include "simple_driver.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>


//delay us max: 65535us
void
lcd_delay_us (uint16_t us)
{
  uint16_t i = 0;
  for (; i < us; i++)
    _delay_us (1.0);
}

//delay_ms max: 65535ms
lcd_delay_ms (double ms)
{
  //delay time in us = ms*10*100
  uint16_t t = (10 * ms);
  while (t--)
    lcd_delay_us (100);
}

void
lcd_toggle_E ()
{				//--enable puls width(high level) min 230 ns--
  LCD_PORT |= (1 << LCD_E);	// E=1
  lcd_delay_us (25);		//KS0065: ~25us, DEM16102SYH-PY: ~50us, HD44780: ~550 us
  LCD_PORT &= ~(1 << LCD_E);	// E=0
}


/*-----------------'06. aug. 29. 10:09---------------
 *  Clear display
 *--------------------------------------------------*/
void
lcd_cls ()
{
  LCD_PORT = 0x0;
  lcd_toggle_E ();
  LCD_PORT = (1 << LCD_DB4);
  lcd_toggle_E ();
  lcd_delay_ms (1.6);		//1.6ms
}

/*-----------------'06. aug. 29. 10:09---------------
 *  Home position
 *--------------------------------------------------*/
void
lcd_home ()
{
  LCD_PORT = 0x0;
  lcd_toggle_E ();
  LCD_PORT = (1 << LCD_DB5);
  lcd_toggle_E ();
  lcd_delay_ms (1.6);		//1.6ms
}


/*-----------------'06. aug. 29. 10:09---------------
 *  LCD & Cursor control (Blinking, ON/OFF,...)
 *--------------------------------------------------*/
void
lcd_control (uint8_t disonoff, uint8_t curonoff, uint8_t curblink)
{
  uint8_t temp = 0x0;
  LCD_PORT = 0x0;
  lcd_toggle_E ();

  temp = (1 << LCD_DB7);	//
  if (disonoff == 1)
    temp |= (1 << LCD_DB6);	//display on
  if (curonoff == 1)
    temp |= (1 << LCD_DB5);	//cursor on
  if (curblink == 1)
    temp |= (1 << LCD_DB4);	//cursor blink

  LCD_PORT = temp;
  lcd_toggle_E ();
  lcd_delay_us (39);
}


/*-----------------'06. aug. 29. 10:09 --------------------
 *  Goto position   (0x00 - 1.row, 1.col)
 *                  (0x40 - 1.row, 2.col)
 *--------------------------------------------------*/

void
lcd_set_DDRAM_addr (uint8_t addr)
{
  uint8_t tmp;
  tmp = (1 << LCD_DB7);		//0x08;
  tmp |= addr >> 4;		//addr high nibble      
  LCD_PORT = tmp;
  lcd_toggle_E ();

  LCD_PORT = (addr & 0x0F);	//addr low nibble
  lcd_toggle_E ();
  lcd_delay_us (39);
}



//CGRAM cimenek beallitasa
void
lcd_set_CGRAM_addr (uint8_t addr)
{
  /* addr: user defined address. 
   */
  uint8_t cmd = (1 << LCD_DB6);	//set CGRAM address cmd
  cmd |= (addr >> 4);		//out cmd and addr high nibble 
  LCD_PORT = cmd;

  lcd_toggle_E ();		//
  LCD_PORT = (addr & 0x0F);	//low nibble
  lcd_toggle_E ();		//
  lcd_delay_us (39);		//
}


/* 
* lcd_put_custom_char (uint8_t charnum, uint8_t values[]) 
* sajat karakter megjelenitese.
* charnum: a karakter n. helye a CGRAMban. Osszesen 8(8 bytos) karaktert lehet definialni.
* values[]: 8 byteos adattombre mutato,amelyben definialva vannak a sajat karakter 
* bytejai.(karakterleiro.)  
*/

uint8_t
lcd_put_custom_char (uint8_t charnum, const uint8_t * values)
{
  register uint8_t j = 0;	//addr = 0x40 + (charnum * 8);
  uint8_t *p = values;

  if (charnum > 7)
    {
      return 1;
    }
  lcd_set_CGRAM_addr (charnum * 8);	//charnum: (8byteos)karakter n. helye a CGRAMban 
  for (; j < 8; j++)
    {
      lcd_putch (*(p + j));	//write 8 byte data (one character) to CGRAM
    }

  return (0);
}


//clear CGRAM
void
lcd_clear_CRGAM ()
{
  register uint8_t i = 0;
  for (; i < 64; i++)
    {
      lcd_set_CGRAM_addr (i);
      lcd_putch (0x00);
    }
}

 
/* 
*lcd_vertical_scroll
* __custom_chars: custom chars array
* __NUM: number of chars (MAX 8)
* __x_delay_ms: delay
* __clear: 1: set CGRAM clear mode; 0: no CGRAM clear 
*/
void
lcd_vertical_scroll (const void *__custom_chars, uint8_t __NUM,
		     uint16_t __verti_delay_ms, uint16_t __horiz_delay_ms,
		     uint8_t ddram_addr, uint8_t __clear)
{
  typedef uint8_t matrix[8][8];
  matrix *p_mtx = __custom_chars;
  register uint8_t i, j;
  uint8_t n, m;
  uint8_t cgram_addr = 0x00;
  uint8_t d, block_line = 7;

  __clear ? lcd_clear_CRGAM () : 0;

  for (n = 0; n < 8; n++)	//ciklus: karakter blokk/sorok szamaig.
    {
      for (i = 0; i < __NUM; i++)
	{			//CGRAM cimbeallitas
	  lcd_set_CGRAM_addr (cgram_addr + block_line);
	  for (j = 0; j < n; j++)
	    {
	      lcd_putch (pgm_read_byte_near (&(*p_mtx)[i][j]));	//irunk cgramba n byteot
	    }
	  cgram_addr = (i + 1) * 8;	//kov. 8byte cime a GCRAMban
	  //kiirtunk __NUM -nyi sajat tipusu karaktert a CGRAMba
	  //(elso ciklusban uresen marad a GGRAM)
	}
      //megjelenitjuk a CGRAM tartalmat (a karaktereket): 
      //(igy kulon ciklusban mar a CGRAMba irt __NUM karakternyi tartalmat jelenit meg, gyorsabb/szebb)

      for (m = 0; m < __NUM; m++)
	{
	  lcd_set_DDRAM_addr (ddram_addr + m);
	  lcd_putch (m);
	  lcd_delay_ms (__horiz_delay_ms);
	}

      cgram_addr = 0x00;
      block_line--;
      //varunk:
      lcd_delay_ms (__verti_delay_ms);
    }
}

/*
lcd_putch (pgm_read_byte_near(&(*p_mtx)[i][j])); ----->>

lcd_putch ((__extension__(
{ 
uint16_t __addr16 = (uint16_t)
((uint16_t)(&(*p_mtx)[i][j])); 
uint8_t __result;
 __asm__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; 
}
)));
*/

/*-----------------'06. aug. 29. 10:09---------------
 *  Put character on LCD
 *--------------------------------------------------*/

void
lcd_putch (uint8_t data)
{
  uint8_t temp;
  temp = (data >> 4);		//temp -be felso 4bit
  temp |= (1 << LCD_RS);	//adatkuldes bekapcs
  LCD_PORT = temp;		//kiirjuk

  lcd_toggle_E ();		//LCD vegrehajtja
  temp = (data & 0x0F);		//temp -be also 4BIT; felso 4bit nullazva
  temp |= (1 << LCD_RS);	//adatkuldes bekapcs

  LCD_PORT = temp;
  lcd_toggle_E ();		//
  lcd_delay_us (43);		//wait 43us
}

/*-----------------2006. aug. 28. 23:21---------------
 *  Display null terminated string 
 *--------------------------------------------------*/
void
lcd_putstr (const uint8_t * data, uint8_t addr)
{
  register uint8_t *p = data;
#if LCD_LINE_1X16
  uint8_t i = 0;
#endif
  lcd_set_DDRAM_addr (addr);
  while (*p)
    {
      //ha 1X16(2X8) karakteres LCD akkor 8 karakter kiirasa utan 
      //atvaltunk a masodik sorba,azaz a 9. karaktert mar a masodik sorba irjuk.
#if LCD_LINE_1X16
      if (i == (8 - addr))
	{
	  lcd_set_DDRAM_addr (LCD_SECND_LN_ADDR);	//2. sor 8BITes cime
	}
#endif
      lcd_putch (*p);		//adatkuldes
      p++;
#if LCD_LINE_1X16
      i++;			//
#endif
    }
}


/*---------2006. aug. 28. 23:21----------------------
 *   Display initialization
 *--------------------------------------------------*/
void
lcd_init (void)
{
  //The display will be busy for approximately 30mS after power ON.

  DDR = 0xFF;			//DDR as out
  LCD_PORT = 0x0;		//PORT = 0
  lcd_delay_ms (40.0);		//wait 40ms after power ON

  LCD_PORT = (1 << LCD_DB5);	//set 4-bit operation
  lcd_toggle_E ();
  //lcd_delay_ms (5.0);         //wait more then 4.1ms
  LCD_PORT = (1 << LCD_DB5);
  lcd_toggle_E ();

  LCD_PORT = (1 << LCD_DB7);
  lcd_toggle_E ();		//2 line mod, 5x8 fonts 

  lcd_delay_us (39);		//39us

  LCD_PORT = 0x0;
  lcd_toggle_E ();
  LCD_PORT = (1 << LCD_DB7);
  lcd_toggle_E ();		//Display ctrl: display off, cursor off, blink off
  lcd_delay_us (39);

  LCD_PORT = 0x0;
  lcd_toggle_E ();
  LCD_PORT = (1 << LCD_DB4);
  lcd_toggle_E ();		//clr
  lcd_delay_ms (1.6);		//1.6ms

  LCD_PORT = 0x0;
  lcd_toggle_E ();
  LCD_PORT = (1 << LCD_DB6) | (1 << LCD_DB5);
  lcd_toggle_E ();		//increment mode,entire shift off  
}
