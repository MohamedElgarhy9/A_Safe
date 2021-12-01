/*
 * EEPROM.h
 *
 * Created: 10/27/2021 2:20:35 AM
 *  Author: 20155
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_vWrite(unsigned short address, unsigned char data); // Writing a given data in a given address in EEPROM 
unsigned char EEPROM_u8Read(unsigned short address); // Reading the data in a given address in EEPROM 

#endif /* EEPROM_H_ */