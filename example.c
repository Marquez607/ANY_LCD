/*
 * Name: example.c 
 * Author: Marquez Jones
 * Desc: This is an example "program" that 
 *       demonstrates ANY_LCD functionality and 
 *       configuration 
 *
 * NOTE: THIS EXAMPLE IS NOT HARDWARE SPECIFIC AND 
 *       WILL NOT WORK AS IS ON ANY PLATFORM
 */

#include <stdio.h>
#include <stdint.h>
#include "ANY_LCD.h"

/* function prototypes */
/* check function definitions below */
void delayUS(uint32_t usec);
void writeLCD(uint8_t bitfield);
void writeLCD_alt(uint8_t bitfield);

/* however the user should initialize their gpio */
void gpioInit(void);

int main(void){
  gpioInit(); //user must initialize own gpio/peripheral 

  /****LCD INIT*****/
  any_lcd_t lcd;
  lcd.delay_us  = &delayUS; /* provide pointers to necessary functions */
  lcd.lcd_write = &writeLCD;
  LCD_Init(lcd); //will initialize lcd "logically" ie send the correct commands for 4 bit mode

  /* writing a string to the LCD */
  char *str = "ANY LCD";
  LCD_WriteString(str,lcd);
  
  /* 
    the 1602 lcd supports at least 2 lines
	using the CMD function and this define will 
	let you set your cursor to line 2
   */
  LCD_WriteCMD(LCD_SET_LINE2);
  
  /*
    the LCD_WriteData() function will let us write 
	characters to the lcd without strings 
   */
   
  int i = 0;
  /* write 'U' 5 times on line 2 */
  while(i < 5){
    LCD_WriteData('U');
  }
  
  /* this function will clear the lcd and reset the cursor 
     to the first position 
   */
  LCD_Reset();   
}


void delayUS(uint32_t usec){
  for(uint32_t i=0;i<usec;i++{
    delay_us(1); /* some kind of provided software delay */  
  }
}

void writeLCD(uint8_t bitfield){
  /*****************
   ASSUMING:
   PORTC 7-4 -> LCD D 7-4
   PORTC 2 -> LCD E 
   PORTC 1 -> LCD RW 
   PORTC 0 -> LCD RS 
  ******************/	
  PORTC = bitfield 
}


void writeLCD_alt(uint8_t bitfield){
  /* example using some more complex bit 
     manipulation techniques for other hardware 
	 configurations 
   */
  
  /*****************
   ASSUMING:
   PORTC 7-4 -> LCD D 7-4
   PORTC 2 -> LCD E 
   PORTC 1 -> LCD RW 
   PORTC 0 -> LCD RS 
  ******************/	
  
  /*clear unneeded bits */
  PORTC &= ~bitfield; 
  
  /* bits 7-4 */
  PORTC |= bitfield & 0xF0;
  
  /* E */
  PORTC |= bitfield & (0x01 << 2);
  
  /* RW */
  PORTC |= bitfield & (0x01 << 1);
  
  /* RS */ 
  PORTC |= bitfield & 0x01;
  
}


/* however the user should initialize their gpio */
void gpioInit(void){
  /* blank */	
}

