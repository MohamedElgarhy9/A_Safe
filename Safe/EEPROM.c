/*
 * EEPROM.c
 *
 * Created: 10/27/2021 1:52:52 AM
 *  Author: Mohamed Maged
 */ 


#include <avr/io.h>
#include "std_macros.h"

void EEPROM_vWrite(unsigned short address, unsigned char data) // Writing a given data in a given address in EEPROM 
{
	// Explicit casing, it isn't important as the compiler will does an implicit declaration any way
	EEARL = (char) address; 
	//  Explicit casing, it isn't important as the compiler will does an implicit declaration any way
	EEARH = (char) (address >> 8);
	EEDR = data;
	// Setting EEPROM master writing enable bit in EEPROM control register
	SET_BIT(EECR,EEMWE);
	// Setting EEPROM writing enable bit in EEPROM control register
	SET_BIT(EECR,EEWE); 
	/*
	We will not leave the function until the writing process completed. 
	To ensure that if we call the EEPROM_vWrite function again, the writing process of the previous function has already completed 
	*/
	while(READ_BIT(EECR,EEWE)==1);//Pooling on EEWE bit (pooling = looping)
}
unsigned char EEPROM_u8Read(unsigned short address)// Reading the data in a given address in EEPROM 
{
	// Explicit casing, it isn't important as the compiler will does an implicit declaration any way
	EEARL = (char) address; 
	// Explicit casing, it isn't important as the compiler will does an implicit declaration any way
	EEARH = (char) (address >> 8);
	// Setting EEPROM reading enable bit in EEPROM control register
	SET_BIT(EECR,EERE);
	return EEDR;
}