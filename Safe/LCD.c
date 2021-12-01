/*
 * LCD.c
 *
 * Created: 10/29/2021 11:59:43 PM
 *  Author: Mohamed Maged
 */ 

#include "LCD.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void LCD_vInit(void)//Initialize LCD
{
	_delay_ms(200);//Delay to ensure that LCD becomes ON
	#if defined eight_bits_mode
		DIO_vsetPORTDIR(Data_port,0xff);//Set all pins of a given port as output
		DIO_vsetPINDIR(EN_port,EN,1);//set a given pin in MC which connected to LCD's enable as output
		DIO_vsetPINDIR(RS_port,RS,1);//set a given pin in MC which connected to LCD's Read Register as output 
		DIO_vsetPINDIR(RW_port,RW,1);//set a given pin in MC which connected to LCD's Read/Write as output
		#if defined LCD_Write
			DIO_vwritePIN(RW_port,RW,0);//That means, I want LCD to write
		#elif defined LCD_Read
			DIO_vwritePIN(RW_port,RW,1);//That means, I want LCD to Read
		#endif
		LCD_vSend_Cmd(EIGHT_BITS);//8 bits mode
		_delay_ms(1);
		LCD_vSend_Cmd(CURSOR_OFF_DISPLAY_ON);
		_delay_ms(1);
		LCD_vSend_Cmd(CLR_SCREEN);
		_delay_ms(10);
		LCD_vSend_Cmd(ENTRY_MODE);
		_delay_ms(1);
	#elif defined four_bits_mode
		//Setting upper four bins of a given port as output
		DIO_vsetPINDIR(Data_port,0,1);
		DIO_vsetPINDIR(Data_port,1,1);
		DIO_vsetPINDIR(Data_port,2,1);
		DIO_vsetPINDIR(Data_port,3,1);
		DIO_vsetPINDIR(EN_port,EN,1);//set a given pin in MC which connected to LCD's enable as output
		DIO_vsetPINDIR(RS_port,RS,1);//set a given pin in MC which connected to LCD's Read Register as output
		DIO_vsetPINDIR(RW_port,RW,1);//set a given pin in MC which connected to LCD's Read/Write as output
		#if defined LCD_Write
			DIO_vwritePIN(RW_port,RW,0);//That means, I want LCD to write
		#elif defined LCD_Read
			DIO_vwritePIN(RW_port,RW,1);//That means, I want LCD to Read
		#endif
		LCD_vSend_Cmd(RETURN_HOME);
		_delay_ms(10);
		LCD_vSend_Cmd(FOUR_BITS);//4 bits mode
		_delay_ms(1);
		LCD_vSend_Cmd(CURSOR_OFF_DISPLAY_ON);
		_delay_ms(1);
		LCD_vSend_Cmd(CLR_SCREEN);
		_delay_ms(10);
		LCD_vSend_Cmd(ENTRY_MODE);
		_delay_ms(1);
	#endif
}
void LCD_vsend_Falling_Edge(void)//It is responsible for Sending pulses to enable
{
	DIO_vwritePIN(EN_port,EN,1);
	_delay_ms(2);
	DIO_vwritePIN(EN_port,EN,0);
	_delay_ms(2);
}
void LCD_vSend_Char(unsigned char data)//Send a character to be written on the LCD
{
	#if defined eight_bits_mode
	
	DIO_vwritePORT(Data_port,data);
	DIO_vwritePIN(RS_port,RS,1);
	LCD_vsend_Falling_Edge();
	
	#elif defined four_bits_mode
	
	DIO_vWriteLowNibble(Data_port,data>>4);
	DIO_vwritePIN(RS_port,RS,1);
	LCD_vsend_Falling_Edge();
	DIO_vWriteLowNibble(Data_port,data);
	DIO_vwritePIN(RS_port,RS,1);
	LCD_vsend_Falling_Edge();
	#endif
}
void LCD_vSend_Cmd(unsigned char cmd)//Send a given command to LCD
{
	#if defined eight_bits_mode
	
	DIO_vwritePORT(Data_port,cmd);
	DIO_vwritePIN(RS_port,RS,0);
	LCD_vsend_Falling_Edge();
	
	#elif defined four_bits_mode
	
	DIO_vWriteLowNibble(Data_port,cmd>>4);
	DIO_vwritePIN(RS_port,RS,0);
	LCD_vsend_Falling_Edge();
	DIO_vWriteLowNibble(Data_port,cmd);
	DIO_vwritePIN(RS_port,RS,0);
	LCD_vsend_Falling_Edge();
	
	#endif
}
void LCD_vClearScreen()
{
	LCD_vSend_Cmd(CLR_SCREEN);
	_delay_ms(10);
}
void LCD_vSend_String(char *data)//Send string to be written on the LCD
{
	while((*data) != '\0')
	{
		LCD_vSend_Char(*data);
		data++;
	}
}
void LCD_vMoveCursor(unsigned char row,unsigned char coloumn)//Move cursor to a given location (according to a given row and a given coloumn)
{
	char data;
	if(row > 2 || row < 1 || coloumn > 16 || coloumn < 1)
	{
		data = 0x80;
	}
	else if(row == 1)
	{
		data = 0x80+coloumn-1;
	}
	else if(row == 2)
	{
		data = 0xc0+coloumn-1;
	}
	LCD_vSend_Cmd(data);
	_delay_ms(1);
}
