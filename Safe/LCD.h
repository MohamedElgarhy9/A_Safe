/*
 * LCD.h
 *
 * Created: 10/30/2021 1:13:39 AM
 *  Author: Mohamed Maged
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "DIO.h"
#include "LCD_Config.h"
#define CLR_SCREEN 0X01
#define CURSOR_OFF_DISPLAY_ON 0x0C
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06
#define Data_port 'D'
#define EN_port 'B'
#define RS_port 'B'
#define RW_port 'B'
#define EN 0
#define RS 1
#define RW 2
#if defined four_bits_mode
	#define FOUR_BITS 0x28
#elif defined eight_bits_mode
	#define EIGHT_BITS 0x38
#endif
void LCD_vInit(void);//Initialize the LCD
void LCD_vsend_Falling_Edge(void);//Send pulses to enable
void LCD_vSend_Char(unsigned char data);//Send a character to be written on the LCD
void LCD_vSend_Cmd(unsigned char cmd);//Send a given command to LCD
void LCD_vClearScreen();//Clear screen
void LCD_vSend_String(char *data);//Send string to be written on the LCD
void LCD_vMoveCursor(unsigned char row,unsigned char coloumn);//Move cursor to a given location (according to a given row and a given coloumn)

#endif /* LCD_H_ */