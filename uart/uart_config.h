#ifndef UART_CONFIG_H
#define UART_CONFIG_H

#define F_CPU 16000000

/*
*Double speed mode
*Options: DOUBLE_SPEED_ENABLE
*         DOUBLE_SPEED_DISABLE
*/

#define DOUBLE_SPEED_STATE DOUBLE_SPEED_DISABLE


/*
*Data size
*Options: 5, 6, 7, 8, 9bit
*/

#define UART_DATA_SIZE DATA_8_BIT


/*
*Stop bits
*Options: UART_STOP1, UART_STOP2
*/

#define UART_STOP UART_STOP1

/*
*Baud rate
*/

#define UART_BAUD 9600


/*
*Bus mode
*Options: UART_SYNC, UART_ASYNC
*/

#define UART_MODE UART_ASYNC


/*
*Transmitter state
*Options: TRANSMIT_ENABLE, TRANSMIT_DISABLE
*/

#define UART_TRANSMIT_STATE TRANSMIT_ENABLE


/*
*Receiver state
*Options: RECEIVE_ENABLE, RECIEVE_DISABLE
*/

#define UART_RECEIVE_STATE RECEIVE_ENABLE


/*
*Parity state
*Options: PARITY_ODD, PARITY_EVEN, NO_PARITY
*/

#define PARITY_STATE NO_PARITY




#endif