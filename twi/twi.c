

#include "twi.h"

static void(*twi_handler)(void);

void TWI_MstrInit(void)
{
	TWSR |= MY_PSC;   //clear status
	TWBR = BRATE;     //Bit rate 400kHz
	TWCR = (1<<TWEN); //Enable TWI
}

void TWI_SlavInit(char addr)
{
	TWAR &= 0x01; //Clear address bits
	TWAR |= (addr << 1); //Set the address
	TWCR = (1<<TWEN) | (1<<TWEA); //Enable ack after being addressed
}

void TWI_Start(void)
{
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while((TWCR&(1<<TWINT)) == 0);
}

void TWI_Stop(void)
{
	TWCR = (1<<TWSTO )|(1<<TWEN)|(1<<TWINT);
}

void TWI_Write(char data)
{
	TWDR = data;
	TWCR = (1<<TWEN)|(1<<TWINT);
	while((TWCR&(1<<TWINT)) == 0);
}

char TWI_ReadAck(void)
{
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	while((TWCR&(1<<TWINT)) == 0);
	return TWDR;
}

char TWI_ReadNoAck(void)
{
	TWCR = (1<<TWEN)|(1<<TWINT);
	while((TWCR&(1<<TWINT)) == 0);
	return TWDR;
}

void Set_TWICallBack(void(*pf)(void))
{
	twi_handler = pf;
}

ISR(TWI_vect)
{
	if(twi_handler)
		(*twi_handler)();
}