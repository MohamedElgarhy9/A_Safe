/*
 * IncFile1.h
 *
 * Created: 10/2/2021 2:31:56 PM
 *  Author: 20155
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define REGISTER_SIZE 8
#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit)) 
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT(reg,bit) ((reg&(1u<<bit))>>bit)
#define IS_BIT_SET(reg,bit) (reg&(1<<bit))>>bit
#define IS_BIT_CLR(reg,bit) !((reg&(1<<bit))>>bit)
#define ROR(reg,num) reg=(reg>>num)|(reg<<(REGISTER_SIZE-num))
#define ROL(reg,num) reg=(reg<<num)|(reg>>(REGISTER_SIZE-num))

#endif /* INCFILE1_H_ */