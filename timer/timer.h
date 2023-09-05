


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#define NULL (void *)0

typedef void(*FunPtr_t)(void);

#define Set_DC_A Set_Compare_A
#define Set_DC_B Set_Compare_B

/*---------------------------------------------------------------------------*/

#define T0OV_INT_ON()  (TIMSK0 |= (1<<TOIE0))
#define T0OV_INT_OFF() (TIMSK0 &= ~(1<<TOIE0))

#define T0COMA_INT_ON() (TIMSK0 |= (1<<OCIE0A))
#define T0COMB_INT_ON() (TIMSK0 |= (1<<OCIE0B))

#define T0COMA_INT_OFF() (TIMSK0 &= ~(1<<OCIE0A))
#define T0COMB_INT_OFF() (TIMSK0 &= ~(1<<OCIE0B))

/*---------------------------------------------------------------------------*/

typedef enum
{
	NORMAL_MODE = 0x00,
	PHASE_CORRECT_PWM = 0x01,
	CTCA_MODE = 0x02,
	FAST_PWM = 0x03,
	PHASE_CORRECT_CTCA = 0x09,
	FAST_PWM_CTCA = 0x0B
	
}T0_Mode_t;

typedef enum
{
	T0_STOPPED,
	T0_DIV_1,
	T0_DIV_8,
	T0_DIV_64,
	T0_DIV_256,
	T0_DIV_1024,
	EXT_FALLING,
	EXT_RISING
	
}T0Clk_t;

typedef enum
{
	OC_DISCONNECTED,
	PIN_TOGGLE_ON_MATCH,
	PIN_RESET_ON_MATCH,
	PIN_SET_ON_MATCH
	
}OC_PinMode_t;


typedef struct{
	
	T0_Mode_t mode;
	T0Clk_t clk;
	OC_PinMode_t oca_mode;
	OC_PinMode_t ocb_mode;
	
}Timer0_cfg_t;

//void T0_Init(T0_Mode_t mode, T0Clk_t clk, OC_PinMode_t pinmode_a, OC_PinMode_t pinmode_b);
void T0_Init(Timer0_cfg_t *T0_cfg);

void Set_Compare_A(uint8_t val);
void Set_Compare_B(uint8_t val);

void Set_COMA_Handler(FunPtr_t pf);
void Set_COMB_Handler(FunPtr_t pf);
void Set_OVF_Handler(FunPtr_t pf);


#endif /* TIMER_H_ */