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

/***********************INCLUDES START***************************************/

#include <stdint.h>
#include "ANY_LCD.h"

/***********************INCLUDES END*****************************************/

/************************STATIC FUNCTION PROTOYPES START*************************/
/*
 * NOTES: These are functions that are used in the creation of other functions
 * and have no use to the end product of this abstraction layer as the functions
 * prototyped in the header files will be sufficient to interface with the LCD
 */

/*
 * Name: MakeCMD
 * Desc: converts command byte into 4 byte array for
 *       LCD transmission
 * Inputs:
 * buffer - length 4 array
 * data   - 8 bit number
 */
static void LCD_MakeCMD(uint16_t *buffer,uint16_t data);

/*
 * Name: MakeData
 * Desc: converts command byte into 4 byte array for
 *       LCD transmission
 * Inputs:
 * buffer - length 4 array
 * data   - 8 bit number
 */
static void LCD_MakeData(uint16_t *buffer,uint16_t data);

/*
 * Name: SendBytes
 * Desc: Send array of bytes to lcd 
 * 
 * Inputs:
 * buffer - data to be sent
 * len    - len of array 
 */
static void LCD_SendBytes(uint16_t *buffer,any_lcd_t lcd,uint8_t len);

/************************STATIC FUNCTION PROTOTYPES END**************************/

/************************FUNCTION DEFINITIONS START*************************/
/*
 * Name:LCD_WriteCMD
 * Desc: write command to LCD
 */
void LCD_WriteCMD(uint16_t cmd,any_lcd_t lcd){
    static uint16_t buffer[LCD_MSG_LEN];
    LCD_MakeCMD(buffer,cmd);
    LCD_SendBytes(buffer,lcd,LCD_MSG_LEN);
}

/*
 * Name:LCD_WriteString
 * Desc: write string to LCD
 */
void LCD_WriteString(char *str,any_lcd_t lcd){

    static uint16_t buffer[LCD_MSG_LEN];
    while(*str){
        LCD_MakeData(buffer,*str);
        LCD_SendBytes(buffer,lcd,LCD_MSG_LEN);
        str++;
    }
}

/*
 * Name:LCD_WriteData
 * Desc: write data to LCD
 */
void LCD_WriteData(uint16_t data,any_lcd_t lcd){
    static uint16_t buffer[LCD_MSG_LEN];
    LCD_MakeData(buffer,data);
    LCD_SendBytes(buffer,lcd,LCD_MSG_LEN);
}

/*****************************
 * Name: LCD_Init
 * Desc: sends LCD init sequence
 *
 * NOTE: DOES NOT INITIALIZE 
 * HARDWARE PERIPHERALS 
 *****************************/
void LCD_Init(any_lcd_t lcd){
    LCD_WriteCMD(LCD_INIT1,lcd);
    LCD_WriteCMD(LCD_INIT2,lcd);
    LCD_WriteCMD(LCD_4BIT_2LINE,lcd);
    LCD_WriteCMD(LCD_DISP_CUR_POS_ON,lcd);
    LCD_WriteCMD(LCD_CLEAR,lcd);
    lcd.delay_us(1E4);
}

/*****************************
 * Name: LCD_Reset
 * Desc: Clears LCD and returns cursor to 0
 *****************************/
void LCD_Reset(any_lcd_t lcd){
    LCD_WriteCMD(LCD_CLEAR,lcd);
    lcd.delay_us(5E3);;
    LCD_WriteCMD(LCD_RETURN,lcd);
    lcd.delay_us(1E4);
}

/*
 * Name: MakeCMD
 * Desc: converts command byte into 4 byte array for
 *       LCD transmission
 *       clear the RS bit
 * Inputs:
 * buffer - length 4 array
 * data   - 8 bit number
 */
static void LCD_MakeCMD(uint16_t *buffer,uint16_t data){

    /******HIGH NIBBLE**********/
    //set led enable and enable bits ; clear RS and RnW bits
    buffer[0] = ((data & 0xF0) | LCD_LED_bm | LCD_E_bm) & (~LCD_RS_bm) & (~LCD_RnW_bm);
    //set led ; clear RS ,E,and RnW bits
    buffer[1] = ((data & 0xF0) | LCD_LED_bm) & (~LCD_RS_bm) & (~LCD_RnW_bm) & (~LCD_E_bm);

    /******LOW NIBBLE**********/
    //set led enable and enable bits ; clear RS and RnW bits
    buffer[2] = (((data<<4) & 0xF0) | LCD_LED_bm | LCD_E_bm) & (~LCD_RS_bm) & (~LCD_RnW_bm);
    //set led ; clear RS ,E,and RnW bits
    buffer[3] = (((data<<4) & 0xF0) | LCD_LED_bm) & (~LCD_RS_bm) & (~LCD_RnW_bm) & (~LCD_E_bm);
}

/*
 * Name: MakeData
 * Desc: converts command byte into 4 byte array for
 *       LCD transmission
 *       SET RS
 * Inputs:
 * buffer - length 4 array
 * data   - 8 bit number
 */
static void LCD_MakeData(uint16_t *buffer,uint16_t data){

    /******HIGH NIBBLE**********/
    //set led enable and enable bits ; and RnW bits
    buffer[0] = ((data & 0xF0) | LCD_LED_bm | LCD_E_bm | LCD_RS_bm) & (~LCD_RnW_bm);
    //set led ; clear RS ,E,and RnW bits
    buffer[1] = ((data & 0xF0) | LCD_LED_bm | LCD_RS_bm) & (~LCD_RnW_bm) & (~LCD_E_bm);

    /******LOW NIBBLE**********/
    //set led enable and enable bits ; and RnW bits
    buffer[2] = (((data<<4) & 0xF0) | LCD_LED_bm | LCD_E_bm | LCD_RS_bm) & (~LCD_RnW_bm);
    //set led ; clear RS ,E,and RnW bits
    buffer[3] = (((data<<4) & 0xF0) | LCD_LED_bm | LCD_RS_bm) & (~LCD_RnW_bm) & (~LCD_E_bm);
}

/*
 * Name: SendBytes
 * Desc: Send array of bytes to lcd 
 * 
 * Inputs:
 * buffer - data to be sent 
 * len    - len of array 
 */
static void LCD_SendBytes(uint16_t *buffer,any_lcd_t lcd,uint8_t len){
	
	for(uint8_t i = 0;i < len;i++){
		lcd.lcd_write(buffer[i]);
        	lcd.delay_us(1E3);
	}

}
	
	
	
	
	

/************************FUNCTION DEFINITIONS END***************************/
