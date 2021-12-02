/*
 * Keypad.c
 *
 * Created: 11/29/2021 2:35:03 PM
 *  Author: Mohamed Maged
 */ 


#include "Keypad.h"
/* 
Initialization function which defines:
	4 pins connected to 4 raws as outputs  
	4 pins connected to 4 col as inputs and connect internal pull up to it 
*/
void Keypad_vInit()
{
	DIO_vsetPINDIR(PORTNAME,0,1);
	DIO_vsetPINDIR(PORTNAME,1,1);
	DIO_vsetPINDIR(PORTNAME,2,1);
	DIO_vsetPINDIR(PORTNAME,3,1);
	DIO_vsetPINDIR(PORTNAME,4,0);
	DIO_vsetPINDIR(PORTNAME,5,0);
	DIO_vsetPINDIR(PORTNAME,6,0);
	DIO_vsetPINDIR(PORTNAME,7,0);
	DIO_vconnectInternalPULLUP(PORTNAME,4,1);
	DIO_vconnectInternalPULLUP(PORTNAME,5,1);
	DIO_vconnectInternalPULLUP(PORTNAME,6,1);
	DIO_vconnectInternalPULLUP(PORTNAME,7,1);
}
// The function which loops on the keypad buttons to check which one is pressed!
char keypad_u8CheckPress()
{
	char arr[4][4] = {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};
	char row, coloumn, x;
	char returnval = NOTPRESSED;
	for(row=0; row<4; row++)
	{
		DIO_vwritePIN(PORTNAME,0,1);
		DIO_vwritePIN(PORTNAME,1,1);
		DIO_vwritePIN(PORTNAME,2,1);
		DIO_vwritePIN(PORTNAME,3,1);
		DIO_vwritePIN(PORTNAME,row,0);
		for(coloumn=0;coloumn<4;coloumn++)
		{
			x = DIO_u8readPIN(PORTNAME,(coloumn+4)); // Here we added 4 to coloumn number to get the value of pin 4,5,6,7 of PIN REG 
			if(x==0)
			{
				returnval = arr[row][coloumn];
				/*
					As the goal of each iteration is "getting one pressed switch", when we get it the iteration will end.
					This break will end the internal for loop, so we also have to end the external one 
				*/
				break;  
			}
		}
		if(returnval != NOTPRESSED)// Which means there is one pressed switch
		{
			break;
		}
	}
	return returnval;
}
