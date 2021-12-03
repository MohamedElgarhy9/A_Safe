/*
 * Safe.c
 *
 * Created: 11/29/2021 10:49:42 PM
 *  Author: Mohamed Maged
 */ 

#include "Keypad.h"
#include "LCD.h"
#include "EEPROM.h"
#include "Safe.h"
int main(void)
{
	Keypad_vInit();
	LCD_vInit();
	/* 
		Checking the status location in EEPROM if found empty that means that is the first time we open the safe and we should start by setting the password,
		But if found filled by zeros that means we safe has already a password, if we want to open it we should pass it's password,
		which is the function of Check_Pass function.			
	*/ 
	if(EEPROM_u8Read(EEPROM_STATUS_LOCATION)==NOTPRESSED)
	{
		Set_Pass();
		Repeat_Pass();
		Check_Setting_Flag();
		/*
			If the repeated password isn't similar to the first taken one,
			the user has three tries to enter a matching password to the first taken pass.
		*/
		if(setting_flag != 1)
		{
			while(flag == 0)
				{
					setting_tries = setting_tries -1;
					if(setting_tries>0)
					{
						LCD_vClearScreen();
						LCD_vSend_String("Mismatch pass!");
						_delay_ms(1000);
						LCD_vMoveCursor(2,1);
						LCD_vSend_String("Tries left:");
						LCD_vSend_Char(setting_tries+48);
						_delay_ms(2000);
						Repeat_Pass();
						Check_Setting_Flag();
						if(setting_flag == 1)
						{
							break;
						}
					}
					/*
						If the three tries have already finished,
						the user will be had to wait 10 sec then he or she will has only one try to get the first taken pass,
						otherwise he or she will has to try again later
					 */
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
						Repeat_Pass();
						Check_Setting_Flag();
						if(setting_flag == 0)
						{
							LCD_vClearScreen();
							LCD_vSend_String("Mismatch pass!");
							_delay_ms(1000);
							LCD_vClearScreen();
							LCD_vSend_String("Try again later");
							_delay_ms(1000);
							Check_flag = 1;
						}
						flag =1;
					}
				}
		}		
	}
	while(Check_flag==0)
	{
		Check_Pass();
	}	
}
//This function enables the user to set a password to the safe
void Set_Pass()
{
	LCD_vSend_String("Set Pass:");
	_delay_ms(1000);
	for(i=0;i<PASSWORD_LENGTH;i++)
	{
		do
		{
			set[i] = keypad_u8CheckPress();
		}while(set[i]==NOTPRESSED);
		LCD_vSend_Char(set[i]);
		_delay_ms(500);
		LCD_vMoveCursor(1,10+i);
		LCD_vSend_Char('*');
	}
}
//This function asks the user to repeat the same password he has set
void Repeat_Pass()
{
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
}
/*
	If the user has correctly entered the repeated pass as the first taken one, and the password has been saved in the EEPROM,
	Now the second step is to check the pass to open the safe 
*/
void Check_Pass()
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
	for (int i=0; i < PASSWORD_LENGTH ;i++)
	{
		if (EEPROM_u8Read(EEPROM_PASSWORD_LOCATION+i)!=arr[i])
		{
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
		LCD_vSend_String("Welcome Maged!");
		Check_flag =1;
	}
	/*
		If the user entered a pass doesn't match with the first and repeated passes, 
		He or she will has three tries to get the correct one after the three tries the safe will closed for ever
	*/ 
	else
	{
		check_tries = check_tries -1;
		if(check_tries>0)
		{
			LCD_vClearScreen();
			LCD_vSend_String("Wrong Password!");
			_delay_ms(1000);
			LCD_vMoveCursor(2,1);
			LCD_vSend_String("Tries left:");
			LCD_vSend_Char(check_tries+48);
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
			Check_flag =1;
		}
	}
}
//Check whether the repeated password same as the first taken one or not
void Check_Setting_Flag()
{
	for(i=0;i<PASSWORD_LENGTH;i++)
	{
		if(set[i] != repeat[i])
		{
			setting_flag = 0;
			break;
		}
		else 
		{
			setting_flag = 1;
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
}
