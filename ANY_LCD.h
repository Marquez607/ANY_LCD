/*********************************
Name: ANY_LCD
Author: Marquez Jones
Date: 1/10/2020
Desc: My abstraction layer for using the LCD

HARDWARE NOTE: 
FOR LCD WIRING
BIT 7-4 -> LCD DATA 7-4
BIT 3   -> LCD LED PIN(if it exists/for i2c)
BIT 2   -> LCD E 
BIT 1   -> LCD RW
BIT 0   -> LCD RS

PARALLEL NOTE: 
Delay may be required in write 
function  
**********************************/

#include <stdint.h>

#ifndef ANY_LCD_H_
#define ANY_LCD_H_

/************************DEFINES/MACROS START********************************/
/****************BIT MASKS*********************/
#define LCD_E_bm    0x04
#define LCD_RnW_bm  0x02
#define LCD_RS_bm   0x01
#define LCD_LED_bm  0x08
#define LCD_DATA_bm 0xF0


/****************COMMANDS*********************/
#define LCD_INIT1           0x33
#define LCD_INIT2           0x32
#define LCD_4BIT_2LINE      0x28
#define LCD_DISP_CUR_POS_ON 0x0F
#define LCD_CLEAR           0x01
#define LCD_RETURN          0x02 //return to address 0
#define LCD_SET_ADDR        0x80 //bit mask this with address

/****************LINE*************************/
/*addresses for different LCD lines
 *in order to swap lines, change LCD address
 */
#define LCD_LINE1_ADDR 0x00
#define LCD_LINE2_ADDR 0x40
#define LCD_LINE3_ADDR 0x14
#define LCD_LINE4_ADDR 0x54

#define LCD_SET_LINE1 LCD_LINE1_ADDR | LCD_SET_ADDR
#define LCD_SET_LINE2 LCD_LINE2_ADDR | LCD_SET_ADDR
#define LCD_SET_LINE3 LCD_LINE3_ADDR | LCD_SET_ADDR
#define LCD_SET_LINE4 LCD_LINE4_ADDR | LCD_SET_ADDR

/****************OTHER*********************/
#define LCD_ADDR    0x3F //0x27 for big LCD
#define LCD_ADDR_BIG 0x27
#define LCD_CLK_FREQ 100  //I2C comm speed
#define LCD_SYS_CLK  200 //system clock speed
#define LCD_MSG_LEN  4        //commands/data will be split into an array of 4 bytes

/************************DEFINES/MACROS END**********************************/

/************************STRUCT START********************************/

typedef struct any_lcd{
	
	/*********************************
	 * NAME: lcd_write 
	 * DESC: This function is used by the 
	 * driver to write data to the lcd 
	 *
	 * NOTE: hardware interface for writing  
	 * data to  lcd
	 * HARDWARE NOTE: 
	 *	FOR LCD WIRING
	 *	BIT 7-4 -> LCD DATA 7-4
	 *	BIT 3   -> LCD LED PIN(if it exists/for i2c)
	 *	BIT 2   -> LCD E 
	 *	BIT 1   -> LCD RW
	 *	BIT 0   -> LCD RS  
	 *
	 * PARALLEL INTERFACE NOTE:
	 * IGNORE the LED pin
	 *
	 ********************************/
	void (*lcd_write)(uint8_t bitfield);
	
	/************************************
	 * Name: Delay us 
	 * Desc: delay microseconds  
	 ***********************************/
	void (*delay_us)(uint32_t microseconds);
	
}any_lcd_t;

/************************STRUCT END**********************************/

/************************FUNCTION PROTOYPES START*************************/

/*****************************
 * Name: LCD_Reset
 * Desc: Clears LCD and returns cursor to 0
 *****************************/
void LCD_Reset(any_lcd_t lcd);

/*****************************
 * Name:LCD_WriteCMD
 * Desc: write command to LCD
 *****************************/
void LCD_WriteCMD(uint16_t cmd,any_lcd_t lcd);

/*****************************00
 * Name:LCD_WriteString
 * Desc: write string to LCD
 *****************************/
void LCD_WriteString(char *str,any_lcd_t lcd);
/*****************************
 * Name:LCD_WriteData
 * Desc: write data to LCD
 *****************************/
void LCD_WriteData(uint16_t data,any_lcd_t lcd);

/*****************************
 * Name: LCD_Init
 * Desc: sends LCD init sequence
 *
 * NOTE: DOES NOT INITIALIZE 
 * HARDWARE PERIPHERALS 
 *****************************/
void LCD_Init(any_lcd_t lcd);

/************************FUNCTION PROTOTYPES END**************************/


#endif /* ANY_LCD_H_ */
