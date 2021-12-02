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
		//This part of code enables the user to set a password of the safe 
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
		//This part of code asks the user to repeat the same password he has set 
		LCD_vClearScreen();
		LCD_vSend_String("Repeat Pass:");	
		for(i=0;i<PASSWORD_LENGTH;i++)
		{
			do
			{
				repeat[i] = keypad_u8CheckPress();
			}while(repeat[i]==NOTPRESSED);
			LCD_vSend_Char(repeat[i]);
			_delay_ms(500);
			LCD_vMoveCursor(1,13+i);
			LCD_vSend_Char('*');
		}
		//Check whether the repeated password same as the first taken one or not
		char setting_flag = 1;
		for(i=0;i<PASSWORD_LENGTH;i++)
		{
			if(set[i] != repeat[i])
			{
				setting_flag = 0;
				break;
			}
		}
		//If the repeated password same as the first taken one, the password will be saved in EEPROM
 		if(setting_flag==1)
		{
			for(i=0;i<PASSWORD_LENGTH;i++)
			{
				EEPROM_vWrite(EEPROM_PASSWORD_LOCATION + i,set[i]);
			}
			EEPROM_vWrite(EEPROM_STATUS_LOCATION,0x00);
		}
		/*
			If the repeated password isn't similar to the first taken one,
			the user has three tries to enter a matching password to the first taken pass.
		*/
		else 
		{
			while(flag == 0)
				{
					tries = tries -1;
					if(tries>0)
					{
						LCD_vClearScreen();
						LCD_vSend_String("Mismatch pass!");
						_delay_ms(1000);
						LCD_vMoveCursor(2,1);
						LCD_vSend_String("Tries left:");
						LCD_vSend_Char(tries+48);
						_delay_ms(2000);
						LCD_vClearScreen();
						LCD_vSend_String("Repeat pass:");
						for(i=0;i<PASSWORD_LENGTH;i++)
						{
							do
							{
								repeat[i] = keypad_u8CheckPress();
							}while(repeat[i]==NOTPRESSED);
							LCD_vSend_Char(repeat[i]);
							_delay_ms(500);
							LCD_vMoveCursor(1,13+i);
							LCD_vSend_Char('*');
						}
					}
					//If the three tries have already finished, the user will be has to wait 10 sec until a new three tries opens again.
					else
					{
						LCD_vClearScreen();
						LCD_vSend_String("Mismatch pass!");
						_delay_ms(1000);
						LCD_vMoveCursor(2,1);
						LCD_vSend_String("try again in:");
						_delay_ms(500);
						for(i=9; i>0; i--)
						{
							LCD_vSend_Char(i+48);
							LCD_vMoveCursor(2,14);
							_delay_ms(1000);
						}
						LCD_vClearScreen();
						LCD_vSend_String("Repeat pass:");
						for(i=0;i<PASSWORD_LENGTH;i++)
						{
							do
							{
								repeat[i] = keypad_u8CheckPress();
							}while(repeat[i]==NOTPRESSED);
							LCD_vSend_Char(repeat[i]);
							_delay_ms(500);
							LCD_vMoveCursor(1,13+i);
							LCD_vSend_Char('*');
						}
						flag =1;
					}
			}
		}
	}	
	/*
		If the user has correctly entered the repeated pass as the first taken one, and the password has been saved in the EEPROM,
		now the second step is to check the pass to open the safe 
	*/ 	
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
		//If the user entered a pass match with the first and repeated passes, the safe will open
		if(correctFlag)
		{
			LCD_vClearScreen();
			LCD_vSend_String("Safe Opened");
			_delay_ms(1000);
			LCD_vClearScreen();
			LCD_vSend_String("Welcome Ahmed!");
			flag =1;
		}
		/*
			If the user entered a pass doesn't match with the first and repeated passes, 
			he or she will has three tries to get the correct one after the three tries the safe will closed for ever
		*/ 
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
