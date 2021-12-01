/*
 * Keypad.h
 *
 * Created: 11/29/2021 3:15:06 PM
 *  Author: 20155
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define PORTNAME 'A'
#define NOTPRESSED 0xff
#include "DIO.h"
/* 
Initialization function which defines:
	4 pins connected to 4 raws as outputs  
	4 pins connected to 4 col as inputs and connect internal pull up to it 
*/
void Keypad_vInit();
// The function which loops on the keypad buttons to check which one is pressed!
char keypad_u8CheckPress();

#endif /* KEYPAD_H_ */