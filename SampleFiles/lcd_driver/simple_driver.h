 /***********************************************************
  * File: simple_driver.h   
  *       HD44780 based LCD driver header
  *   Created:    --
  *   Author:     gtk
  *                 uprog@tvn.hu
  *   Comments:   functions & definitions
  ************************************************************/

#ifndef SIMPLE_DRIVER_H
#define SIMPLE_DRIVER_H

#include <inttypes.h>
//#include <stdio.h>

/*
LCD in 4bit mode;
data lines:

ATMega8
PC0 = lcd DB4
PC1 = lcd DB5
PC2 = lcd DB6
PC3 = lcd DB7

PC4 = lcd RS
PC5 = lcd E
      
lcd RW to GND
*/

/* data direction and port */

#define DDR DDRC
#define LCD_PORT PORTC

/*lcd 4BIT data lines*/
#define LCD_DB4	PC0
#define LCD_DB5	PC1
#define LCD_DB6	PC2
#define LCD_DB7	PC3

/* for LCD control */
#define LCD_RS  PC4
#define LCD_E	PC5

//----------------------------------------------------------------//

/* lines address in DDRAM
*/
#define LCD_FIRST_LN_ADDR 0x00
#define LCD_SECND_LN_ADDR 0x40

//def. for LCD_putstr()
//0: not 1X16 LCD
//1:     1X16 LCD
#define LCD_LINE_1X16 0


void lcd_delay (unsigned int p);
void lcd_toggle_E ();
void lcd_cls ();
void lcd_home ();
void lcd_control (uint8_t disonoff, uint8_t curonoff, uint8_t curblink);
void lcd_set_CGRAM_addr (uint8_t addr);
void lcd_set_DDRAM_addr (uint8_t mesto);
uint8_t lcd_put_custom_char (uint8_t charnum, const uint8_t * values);
// lcd_vertical_scroll: max 8 char
void
lcd_vertical_scroll (const void *__custom_chars, uint8_t __NUM,
		     uint16_t __verti_delay_ms, uint16_t __horiz_delay_ms,
		     uint8_t ddram_addr, uint8_t __clear);
void lcd_clear_CRGAM ();
void lcd_putch (uint8_t data);
void lcd_putstr (const uint8_t * data, uint8_t addr);
void lcd_init (void);

#endif /* SIMPLE_DRIVER_H */
