/*
 * Safe.c
 *
 * Created: 11/29/2021 10:49:42 PM
 *  Author: Mohamed Maged
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "Keypad.h"
#include "LCD.h"
#include "EEPROM.h"
#define EEPROM_STATUS_LOCATION 0x20
#define EEPROM_PASSWORD_LOCATION 0x21
#define PASSWORD_LENGTH 4
#define MAX_TRIES 3
char arr[PASSWORD_LENGTH];
int main(void)
{
	char pressed_value = NOTPRESSED;
	char flag=0, i;
	char tries = MAX_TRIES;
	Keypad_vInit();
	LCD_vInit();
	// Setting password code part
	if(EEPROM_u8Read(EEPROM_STATUS_LOCATION)==NOTPRESSED)
	{
		LCD_vSend_String("Set Pass:");
		_delay_ms(1000);
		for(i=0;i<PASSWORD_LENGTH;i++)
		{
			do
			{
				pressed_value = keypad_u8CheckPress();
			}while(pressed_value==NOTPRESSED);
			LCD_vSend_Char(pressed_value);
			_delay_ms(500);
			LCD_vMoveCursor(1,10+i);
			LCD_vSend_Char('*');
			EEPROM_vWrite(EEPROM_PASSWORD_LOCATION+i,pressed_value);
		}	
		EEPROM_vWrite(EEPROM_STATUS_LOCATION,0x00);	
	}
	while(flag==0)
	{
		LCD_vClearScreen();
		LCD_vSend_String("Check Pass:");
		for(i=0;i<PASSWORD_LENGTH;i++)
		{
			do
			{
				arr[i] = keypad_u8CheckPress();
			}while(arr[i]==NOTPRESSED);
			LCD_vSend_Char(arr[i]);
			_delay_ms(500);
			LCD_vMoveCursor(1,12+i);
			LCD_vSend_Char('*');
		}
		
		int correctFlag =1;
		for (int i=0; i < PASSWORD_LENGTH ;i++){
			if (EEPROM_u8Read(EEPROM_PASSWORD_LOCATION+i)!=arr[i]){
				correctFlag = 0;
				break;
			}
		}
		if(correctFlag)
		{
			LCD_vClearScreen();
			LCD_vSend_String("Safe Opened");
			_delay_ms(1000);
			LCD_vClearScreen();
			LCD_vSend_String("Welcome Ahmed!");
			flag =1;
		}
		else
		{
			tries = tries -1;
			if(tries>0)
			{
				LCD_vClearScreen();
				LCD_vSend_String("Wrong Password!");
				_delay_ms(1000);
				LCD_vMoveCursor(2,1);
				LCD_vSend_String("Tries left:");
				LCD_vSend_Char(tries+48);
				_delay_ms(2000);
			}
			else 
			{
				LCD_vClearScreen();
				LCD_vSend_String("Wrong Password!");
				_delay_ms(1000);
				LCD_vMoveCursor(2,1);
				LCD_vSend_String("Safe Closed");
				_delay_ms(1000);
				flag =1;
			}
		}
	}
}