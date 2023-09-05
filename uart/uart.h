#ifndef UART_H
#define UART_H

#include "bitmath.h"
#include "uart_config.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define TxBUSY  0
#define TxREADY 1

#define RxBUSY  0
#define RxREADY 1


#if DOUBLE_SPEED_STATE==DOUBLE_SPEED_DISABLE
	#define MYUBRR (F_CPU/16/UART_BAUD-1) 
#elif DOUBLE_SPEED_STATE==DOUBLE_SPEED_ENABLE
	#define MYUBRR (F_CPU/8/UART_BAUD-1) 
#endif

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

