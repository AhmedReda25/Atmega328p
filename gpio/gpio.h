#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <avr/io.h>
#include "bitmath.h"

#define HIGH 1
#define LOW  0

#define INPUT  1
#define OUTPUT 0



typedef enum
{
	RB0,  /* 0 to 7 (0)*/
	RB1,
	RB2,
	RB3,
	RB4,
	RB5,
	RB6,
	RB7,
	
	RC0,  /* 8 to 15 (8)*/
	RC1,
	RC2,
	RC3,
	RC4,
	RC5,
	RC6,
	RC7,
	
	RD0,  /* 16 to 23 (16) */
	RD1,
	RD2,
	RD3,
	RD4,
	RD5,
	RD6,
	RD7
	
}PinType_t;

typedef enum
{
	PRTB,
	PRTC,
	PRTD
}PortType_t;

void PinDir(PinType_t pin, uint8_t dir);
void PinWrite(PinType_t pin, uint8_t val);
void PinToggle(PinType_t pin);
uint8_t GetPin(PinType_t pin);
void PortDir(PortType_t port, uint8_t dir);
void PortWrite(PortType_t port, uint8_t val);
uint8_t ReadPort(PortType_t port);


#endif