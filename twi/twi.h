#ifndef TWI_H
#define TWI_H

#include<avr/io.h>
#include "bitmath.h"

#define PRESCALER_1   0
#define PRESCALER_16  1
#define PRESCALER_64  2
#define PRESCALER_128 3

#define TWI_IRQ_ENABLE  (SET_BIT(TWCR,TWIE))
#define TWI_IRQ_DISABLE (CLR_BIT(TWCR,TWIE))

#define TWI_SLAVE_GENERAL_CALL_EN  (SET_BIT(TWAR,TWGCE))
#define TWI_SLAVE_GENERAL_CALL_DIS (CLR_BIT(TWAR,TWGCE))
/*-----------------------Config----------------------*/
#define BUAD 400000
#define MY_PSC PRESCALER_1
/*---------------------------------------------------*/
static uint8_t twi_PSC[4] = {1, 16, 64, 128};
	
#define BRATE (((F_CPU/BUAD)-16)/(2*twi_PSC[MY_PSC]))


void TWI_MstrInit(void);
void TWI_SlavInit(char addr);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(char data);
char TWI_ReadAck(void);
char TWI_ReadoNAck(void);

void Set_TWICallBack(void(*pf)(void));



#endif