

#include "uart.h"
#include "uart_config.h"



#if DOUBLE_SPEED_STATE==DISABLE
	#define MYUBRR (F_CPU/16/UART_BAUD-1) 
#elif DOUBLE_SPEED_STATE==ENABLE
	#define MYUBRR (F_CPU/8/UART_BAUD-1) 
#endif



static uint8_t *st_rec;
static uint8_t *pt_send = 0;

static uint8_t strflag = 0;//When the string is received completely
static uint8_t Rx_StLen = 0;


static void (*Tx_Handler)(void) = NULL;
static void (*Rx_Handler)(void) = NULL;

static uint8_t TxState = TxREADY;
static uint8_t RxState = RxREADY;

/*----------------------------------------------------------------*/
static void Rx_StrFun(void)
{
    static uint8_t idx = 0;
    st_rec[idx] = UDR0; /* Read received data */
    idx++;
	Rx_StLen--;
    if(!Rx_StLen)
    {
        st_rec[idx] = 0; //Terminate the string.
        strflag = 1;     //Indicate complete reception
        idx = 0;
		RxState = RxREADY;
		UART_RECEIVE_IRQ_OFF; //Disable reception interrupt
    }
}
static void Tx_StrFun(void)
{
    static uint8_t i = 0;
	if(pt_send[i] != '\0')
		UART_SendNonBlocking(pt_send[i++]);
	
    else{
		
        i = 0;
        UART_DREMPTY_IRQ_OFF;
        TxState = TxREADY;
    }
}
/*----------------------------------------------------------------*/
void UART_Init(void)
{
	/* Speed selection */
#if DOUBLE_SPEED_STATE==ENABLE
	SET_BIT(UCSR0A,U2X0);
#else
	CLR_BIT(UCSR0A,U2X0);
#endif
	
	/* Data length */
#if UART_DATA_SIZE==DATA_5_BIT
	CLR_BIT(UCSR0C,UCSZ00);
	CLR_BIT(UCSR0C,UCSZ01);
	CLR_BIT(UCSR0B,UCSZ02);
	
#elif UART_DATA_SIZE==DATA_6_BIT
	SET_BIT(UCSR0C,UCSZ01);
	CLR_BIT(UCSR0C,UCSZ01);
	CLR_BIT(UCSR0B,UCSZ02);
	
#elif UART_DATA_SIZE==DATA_7_BIT
	CLR_BIT(UCSR0C,UCSZ00);
	SET_BIT(UCSR0C,UCSZ01);
	CLR_BIT(UCSR0B,UCSZ02);
	
#elif UART_DATA_SIZE==DATA_8_BIT
	SET_BIT(UCSR0C,UCSZ00);
	SET_BIT(UCSR0C,UCSZ01);
	CLR_BIT(UCSR0B,UCSZ02);
	
#elif UART_DATA_SIZE==DATA_9_BIT
	SET_BIT(UCSR0C,UCSZ00);
	SET_BIT(UCSR0C,UCSZ01);
	SET_BIT(UCSR0B,UCSZ02);
#else
	#error "unvalid data length"
#endif

	/* Stop bits */
#if UART_STOP==UART_STOP1
	CLR_BIT(UCSR0C,USBS0);
#elif UART_STOP==UART_STOP2
	SET_BIT(UCSR0C,USBS0);
#endif
	
	/* Baud rate register value */
	UBRR0H = (uint8_t)(MYUBRR>>8);
	UBRR0L = (uint8_t)MYUBRR;
	
#if UART_MODE==UART_ASYNC
	CLR_BIT(UCSR0C,UMSEL00);
#elif UART_MODE==UART_SYNC
	SET_BIT(UCSR0C,UMSEL00);
	CLR_BIT(UCSR0A,U2X0);
#endif

#if UART_TRANSMIT_STATE==ENABLE
	SET_BIT(UCSR0B,TXEN0);
#elif UART_TRANSMIT_STATE==DISABLE
	CLR_BIT(UCSR0B,TXEN0);
#endif

#if UART_RECEIVE_STATE==ENABLE
	SET_BIT(UCSR0B,RXEN0);
#elif UART_RECEIVE_STATE==DISABLE
	CLR_BIT(UCSR0B,RXEN0);
#endif

#if PARITY_STATE==NO_PARITY
	CLR_BIT(UCSR0C,UPM00);
	CLR_BIT(UCSR0C,UPM01);
#elif PARITY_STATE==PARITY_ODD
	SET_BIT(UCSR0C,UPM00);
	SET_BIT(UCSR0C,UPM01);
#elif PARITY_STATE==PARITY_EVEN
	SET_BIT(UCSR0C,UPM01);
	CLR_BIT(UCSR0C,UPM00);
#endif
}

void UART_Send(uint8_t data)
{
	while(!GET_BIT(UCSR0A,UDRE0)); //Wait for data register empty
	UDR0 = data;
}

void UART_SendNonBlocking(uint8_t data)
{
	UDR0 = data;
}

uint8_t UART_Read(void)
{
	while(!GET_BIT(UCSR0A,RXC0));
	return UDR0;
}

uint8_t UARTReadNonBlocking(void)
{
	return UDR0;
}

void UART_String(uint8_t *st)
{
	if(NULL != st){
		while(*st)
			UART_Send(*st++);
	}
}

void UART_StringNonBlocking(uint8_t *st)
{
	if(TxREADY == TxState)
    {
        pt_send = st;
        TxState = TxBUSY;
        UART_SetTxHandler(Tx_StrFun);
        
        UART_DREMPTY_IRQ_ON;
		sei();
    }
}

uint8_t UART_ReadStringNonBlocking(uint8_t *st, uint8_t len)
{
	if(RxREADY == RxState){
		
		RxState = RxBUSY;
		Rx_StLen = len;
		st_rec = st;
		UART_SetRxHandler(Rx_StrFun);
		UART_RECEIVE_IRQ_ON; /* Enable Reception interrupt */
		sei();
	}
    if(strflag == 1){
        strflag = 0;
        return 1;
    }
    return 0;
}

void UART_ReadString(uint8_t *st, uint8_t len)
{
	if(NULL != st)
	{
		for(uint8_t i = 0; i < len; i++)
		{
			st[i] = UART_Read();
		}
		st[len] = 0; //Terminate the string.
		
	}
}

void UART_SetTxHandler(void(*pf)(void))
{
	Tx_Handler = pf;
}
void UART_SetRxHandler(void(*pf)(void))
{
	Rx_Handler = pf;
}


ISR(USART_UDRE_vect)
{
	if(Tx_Handler){
		Tx_Handler();
	}
}

ISR(USART_RX_vect)
{
	if(Rx_Handler){
		Rx_Handler();
	}
}