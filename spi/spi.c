
#include "spi.h"

static void(*SPI_Handler)(void);

void SPI_MstrInit(spiClk_t div, DataMode_t mode){
	/* Master mode */
	SET_BIT(SPCR,MSTR);
	
	/* Data mode */
	SPCR &= ~(3<<CPHA);
	SPCR |= (mode<<CPHA);
	
	/* Clock division */
	switch(div)
	{
		case SPI_DIV_4:
		case SPI_DIV_16:
		case SPI_DIV_64:
		case SPI_DIV_128:
			CLR_BIT(SPSR,SPI2X);
			break;
		case SPI_DIV_2:
		case SPI_DIV_8:
		case SPI_DIV_32:
			SET_BIT(SPSR,SPI2X);
			break;
	}
	
	div &= 0x03; //Clear the 2X bit in the clk variable (keep enum value 3 or lower)
	SPCR &= ~(3);
	SPCR |= div;
	
	SET_BIT(SPCR,SPE);
	
}

void SPI_SlavInit(DataMode_t mode){
	
	/* Slave mode */
	CLR_BIT(SPCR,MSTR);
	
	/* Data mode */
	SPCR &= ~(3<<CPHA);
	SPCR |= (mode<<CPHA);
	
	SET_BIT(SPCR,SPE);
}

void SPI_Send(uint8_t data){
	
	SPDR = data;
	while(!GET_BIT(SPSR,SPIF));
}

void SPI_WriteNoBlock(uint8_t data){
	
	SPDR = data;
}

uint8_t SPI_Receive(void){
	
	while(!GET_BIT(SPSR,SPIF));
	return SPDR;
}

uint8_t SPI_ReceiveNoBlock(uint8_t *data){
	
	if(GET_BIT(SPSR,SPIF)){
		*data = SPDR;
		return SPI_TRANSFER_DONE;
	}
	
	return SPI_TRANSFER_ONGOING;
}

void SetSPI_CallBack(void(*pf)(void)){
	SPI_Handler = pf;
}

ISR(SPI_vect)
{
	if(SPI_Handler)
		(*SPI_Handler)();
}