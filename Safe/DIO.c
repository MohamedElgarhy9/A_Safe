/*
 * DIO.c
 *
 * Created: 10/2/2021 2:24:37 PM
 *  Author: Mohamed Maged
 */ 


#include <avr/io.h>
#include "std_macros.h"
#include "DIO.h"

void DIO_vsetPINDIR(unsigned char portname,unsigned char pinnumber,unsigned char direction) // v stands for the return data type of the function is void 
{
	switch(portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
			if(direction==1)
			{
				SET_BIT(DDRA,pinnumber); // Set direction of a given pin in PORTA as output 
			}
			else
			{
				CLR_BIT(DDRA,pinnumber); // Set direction of a given pin in PORTA as input	
			}
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
			if(direction==1)
			{
				SET_BIT(DDRB,pinnumber); // Set direction of a given pin in PORTB as output
 			}
			else
			{
				CLR_BIT(DDRB,pinnumber); // Set direction of a given pin in PORTB as input
			}
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
			if(direction==1)
			{
				SET_BIT(DDRC,pinnumber); // Set direction of a given pin in PORTC as output
			}
			else 
			{
				CLR_BIT(DDRC,pinnumber); // Set direction of a given pin in PORTC as input
			}
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
			if(direction==1)
			{
				SET_BIT(DDRD,pinnumber); // Set direction of a given pin in PORTD as output
			}
			else
			{
				CLR_BIT(DDRD,pinnumber); // Set direction of a given pin in PORTD as input
			}
		break;
	}
}
void DIO_vwritePIN(unsigned char portname,unsigned char pinnumber,unsigned char outputvalue) // v stands for the return data type of the function is void 
{
	switch(portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
			if(outputvalue==1)
			{
				SET_BIT(PORTA,pinnumber); // Set the value of a given pin in PORTA as HIGH
			}
			else 
			{
				CLR_BIT(PORTA,pinnumber); // Set the value of a given pin in PORTA as LOW
			}
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
			if(outputvalue==1)
			{
				SET_BIT(PORTB,pinnumber); // Set the value of a given pin in PORTB as HIGH
			}
			else
			{
				CLR_BIT(PORTB,pinnumber); // Set the value of a given pin in PORTB as LOW
			}
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
			if (outputvalue==1)
			{
				SET_BIT(PORTC,pinnumber);// Set the value of a given pin in PORTC as HIGH
			}
			else 
			{
				CLR_BIT(PORTC,pinnumber); // Set the value of a given pin in PORTC as LOW
			}
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
			if (outputvalue==1)
			{
				SET_BIT(PORTD,pinnumber); // Set the value of a given pin in PORTD as HIGH
			}
			else 
			{
				CLR_BIT(PORTD,pinnumber); // Set the value of a given pin in PORTD as LOW
			}
		break;
	}
}
void DIO_vtogglePIN(unsigned char portname,unsigned char pinnumber) // v stands for the return data type of the function is void  
{
	switch(portname)
	{
		case 'A': 
		// Case the user inputs a as a small litter not the capital one
		case 'a':
			TOG_BIT(PORTA,pinnumber); // Toggle the value of a given pin in portA
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
			TOG_BIT(PORTB,pinnumber); // Toggle the value of a given pin in portB
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
			TOG_BIT(PORTC,pinnumber); // Toggle the value of a given pin in portC
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
			TOG_BIT(PORTD,pinnumber); // Toggle the value of a given pin in portD
		break;
	}
}
unsigned char DIO_u8readPIN(unsigned char portname,unsigned char pinnumber)// u8 stands for the return data type of the function is unsigned char 
{
	unsigned char return_value;
	switch(portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
			return_value = READ_BIT(PINA,pinnumber); // Read the value from the given pin in PORTA
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
			return_value = READ_BIT(PINB,pinnumber); // Read the value from the given pin in PORTB
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
			return_value = READ_BIT(PINC,pinnumber); // Read the value from the given pin in PORTC
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
			return_value = READ_BIT(PIND,pinnumber); // Read the value from the given pin in PORTD
		break;
	}
	return return_value;
}
void DIO_vsetPORTDIR(unsigned char portname,unsigned char direction)// v stands for the return data type of the function is void 
{
	switch(portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
			DDRA = direction;  // Set direction of PORTA
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
			DDRB = direction; // Set direction of PORTB
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
			DDRC = direction; // Set direction of PORTC
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
			DDRD = direction; // Set direction of PORTD
		break;	
	}
}
void DIO_vwritePORT(unsigned char portname,unsigned char outputvalue)// v stands for the return data type of the function is void 
{
	switch(portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
			PORTA = outputvalue; // Write the value of PORTA
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
			PORTB = outputvalue;// Write the value of PORTB
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
			PORTC = outputvalue;// Write the value of PORTC
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
			PORTD = outputvalue;// Write the value of PORTD
		break;
	}
}
void DIO_vtogglePORT(unsigned char portname)// v stands for the return data type of the function is void 
{
	switch(portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
			PORTA = ~PORTA;// (PORTA^=0xff) Toggle PORTA 
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
			PORTB = ~PORTB;// (PORTB^=0xff) Toggle PORTB
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
			PORTC = ~PORTC;// (PORTC^=0xff) Toggle PORTC
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
			PORTD = ~PORTD;// (PORTD^=0xff) Toggle PORTD
		break;
	}
}
unsigned char DIO_u8readPORT(unsigned char portname)// u8 stands for the return data type of the function is unsigned char
{
	unsigned char return_value;
	switch(portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
			return_value = PINA;// Read the value of PORTA
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
			return_value = PINB;// Read the value of PORTB
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
			return_value = PINC;// Read the value of PORTC
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
			return_value = PIND;// Read the value of PORTD
		break;
	}
}
void DIO_vconnectInternalPULLUP(unsigned char portname, unsigned char pinnumber, unsigned char connect_value) // v stands for the return data type of the function is void 
//Connect_value equals one if i want to enable the internal pull up and zero if i disabled it after the enabling 
{
	switch (portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
			if (connect_value==1)
			{
				SET_BIT(PORTA,pinnumber);//If connect_value equals one connect the internal pull up for the given pinnumber
			}	
			else
			{
				CLR_BIT(PORTA,pinnumber);
			}
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
			if(connect_value==1)
			{
				SET_BIT(PORTB,pinnumber);//If connect_value equals one connect the internal pull up for the given pinnumber
			}
			else
			{
				CLR_BIT(PORTB,pinnumber);	
			}
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
			if(connect_value==1)
			{
				SET_BIT(PORTC,pinnumber);//If connect_value equals one connect the internal pull up for the given pinnumber
			}
			else
			{
				CLR_BIT(PORTC,pinnumber);
			}
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
			if(connect_value==1)
			{
				SET_BIT(PORTD,pinnumber);//If connect_value equals one connect the internal pull up for the given pinnumber
			}
			else 
			{
				CLR_BIT(PORTD,pinnumber);
			}
		break;
	}
}
void DIO_vWriteLowNibble(unsigned char portname, unsigned char number)//Puts the first four bits of a given number on least four bins of a given port
//number should be from 0 to 9
{
	//Difficult Solution..
	number = number & 0x0f;//if the user insert a number greater than 9, we will take only the first four bits
	switch(portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
		PORTA = PORTA & 0xf0;
		PORTA = PORTA | number;
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
		PORTB = PORTB & 0xf0;
		PORTB = PORTB | number;
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
		PORTC = PORTC & 0xf0;
		PORTC = PORTC | number;
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
		PORTD = PORTD & 0xf0;
		PORTD = PORTD | number;
		break;
	}
}
void DIO_vWriteHighNibble(unsigned char portname, unsigned char number)//Puts the first four bits of a given number on most four bins of a given port
//number should be from 0 to 9
{
	//Difficult Solution..
	number = number<<4;//if the user insert a number greater than 9, we will take only the first four bits
	switch(portname)
	{
		case 'A':
		// Case the user inputs a as a small litter not the capital one
		case 'a':
		PORTA = PORTA & 0x0f;
		PORTA = PORTA | number;
		break;
		case 'B':
		// Case the user inputs b as a small litter not the capital one
		case 'b':
		PORTB = PORTB & 0x0f;
		PORTB = PORTB | number;
		break;
		case 'C':
		// Case the user inputs c as a small litter not the capital one
		case 'c':
		PORTC = PORTC & 0x0f;
		PORTC = PORTC | number;
		break;
		case 'D':
		// Case the user inputs d as a small litter not the capital one
		case 'd':
		PORTD = PORTD & 0x0f;
		PORTD = PORTD | number;
		break;
	}
}



