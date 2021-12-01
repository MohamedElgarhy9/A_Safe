/*
 * IncFile1.h
 *
 * Created: 10/2/2021 4:41:35 PM
 *  Author: 20155
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

 void DIO_vsetPINDIR(unsigned char portname,unsigned char pinnumber,unsigned char direction);// v stands for the return data type of the function is void 
 void DIO_vwritePIN(unsigned char portname,unsigned char pinnumber,unsigned char outputvalue);// v stands for the return data type of the function is void 
 void DIO_vtogglePIN(unsigned char portname,unsigned char pinnumber);// v stands for the return data type of the function is void 
 unsigned char DIO_u8readPIN(unsigned char portname,unsigned char pinnumber);// u8 stands for the return data type of the function is unsigned char
 void DIO_vsetPORTDIR(unsigned char portname,unsigned char direction);// v stands for the return data type of the function is void 
 void DIO_vwritePORT(unsigned char portname,unsigned char outputvalue);// v stands for the return data type of the function is void 
 void DIO_vtogglePORT(unsigned char portname);// v stands for the return data type of the function is void 
 unsigned char DIO_u8readPORT(unsigned char portname);// u8 stands for the return data type of the function is unsigned char
void DIO_vconnectInternalPULLUP(unsigned char portname, unsigned char pinnumber, unsigned char connect_value); // v stands for the return data type of the function is void 
void DIO_vWriteLowNibble(unsigned char portname, unsigned char number);//Puts the first four bits of a given number on least four bins of a given port
void DIO_vWriteHighNibble(unsigned char portname, unsigned char number);//Puts the first four bits of a given number on most four bins of a given port

#endif /* INCFILE1_H_ */