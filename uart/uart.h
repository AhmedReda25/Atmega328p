#ifndef UART_H
#define UART_H

#include "bitmath.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000

#define DISABLE 0
#define ENABLE  1

#define DATA_5_BIT 0
#define DATA_6_BIT 1
#define DATA_7_BIT 2
#define DATA_8_BIT 3
#define DATA_9_BIT 4


#define UART_STOP1 0
#define UART_STOP2 1


#define UART_ASYNC 0
#define UART_SYNC  1

#define NO_PARITY   0
#define ODD_PARITY  1
#define EVEN_PARITY 2

/*----------------------------------------------------------------------------*/
#define TxBUSY  0
#define TxREADY 1

#define RxBUSY  0
#define RxREADY 1



#define UART_DREMPTY_IRQ_ON  (SET_BIT(UCSR0B,UDRIE0))
#define UART_DREMPTY_IRQ_OFF (CLR_BIT(UCSR0B,UDRIE0))


#define UART_RECEIVE_IRQ_ON  (SET_BIT(UCSR0B,RXCIE0))
#define UART_RECEIVE_IRQ_OFF (CLR_BIT(UCSR0B,RXCIE0))

void UART_Init(void);
void UART_Receiv_IntEn(void);
void UART_Transmit_IntEN(void);

void UART_Send(uint8_t data);
void UART_SendNonBlocking(uint8_t c);
uint8_t UART_Read(void);
uint8_t UARTReadNonBlocking(void);
void UART_String(uint8_t *st);
void UART_StringNonBlocking(uint8_t *st);
void UART_ReadString(uint8_t *st, uint8_t len);
uint8_t UART_ReadStringNonBlocking(uint8_t *st, uint8_t len);

void UART_SetTxHandler(void(*pf)(void));
void UART_SetRxHandler(void(*pf)(void));

#endif

