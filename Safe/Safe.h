/*
 * Safe.h
 *
 * Created: 12/3/2021 2:37:24 PM
 *  Author: 20155
 */ 


#ifndef SAFE_H_
#define SAFE_H_

#define F_CPU 8000000UL
#include <util/delay.h>
#define EEPROM_STATUS_LOCATION 0x20
#define EEPROM_PASSWORD_LOCATION 0x21
#define PASSWORD_LENGTH 4
#define MAX_TRIES 3
char arr[PASSWORD_LENGTH];
char set[PASSWORD_LENGTH];
char repeat[PASSWORD_LENGTH];
char setting_tries = MAX_TRIES;
char check_tries = MAX_TRIES;
char pressed_value = NOTPRESSED;
char i,flag;
char Check_flag=0;
char setting_flag;
void Set_Pass();//This function enables the user to set a password to the safe
void Repeat_Pass();//This function asks the user to repeat the same password he has set
/*
	If the user has correctly entered the repeated pass as the first taken one, and the password has been saved in the EEPROM,
	Now the second step is to check the pass to open the safe 
*/
void Check_Pass();
void Check_Setting_Flag();//Check whether the repeated password same as the first taken one or not


#endif /* SAFE_H_ */