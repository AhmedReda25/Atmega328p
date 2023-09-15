#ifndef SPI_H
#define SPI_H

#include "bitmath.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>


#define SPI_SS   RB2
#define SPI_MISO RB4
#define SPI_MOSI RB3
#define SPI_SCK  RB5

#define SPI_TRANSFER_DONE    1
#define SPI_TRANSFER_ONGOING 0

#define SPI_IRQ_ENABLE  SET_BIT(SPCR,SPIE)
#define SPI_IRQ_DISABLE CLR_BIT(SPCR,SPIE)

typedef enum
{
	POL0_PHA0,
	POL0_PHA1,
	POL1_PHA0,
	POL1_PHA1,
	
}DataMode_t;


typedef enum
{
	SPI_DIV_4,
	SPI_DIV_16,
	SPI_DIV_64,
	SPI_DIV4_128,
	SPI_DIV4_2,
	SPI_DIV4_8,
	SPI_DIV4_32,
	
}spiClk_t;

void SPI_MstrInit(spiClk_t div, DataMode_t mode);
void SPI_SlavInit(DataMode_t mode);

void SPI_Send(uint8_t data);
void SPI_WriteNoBlock(uint8_t data);

uint8_t SPI_Receive(void);
uint8_t SPI_ReceiveNoBlock(uint8_t *data);

void SetSPI_CallBack(void(*pf)(void));

#endif