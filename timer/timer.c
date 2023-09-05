

#include "timer.h"

static FunPtr_t Ovf_Handler = NULL;
static FunPtr_t ComA_Handler = NULL;
static FunPtr_t ComB_Handler = NULL;

/*
void T0_Init(T0_Mode_t mode, T0Clk_t clk, OC_PinMode_t pinmode_a, OC_PinMode_t pinmode_b){
	TCCR0A = 0;
	TCCR0B = 0;
	
	/* Mode */
	//TCCR0A |= (mode & 0x03);
	//TCCR0B |= (mode & 0xFC);
	
	/* Clock */
	//TCCR0B |= clk;
	
	/* Pins mode */
	//TCCR0A |= (pinmode_a << 6);
	//TCCR0A |= (pinmode_b << 4);
//}

void T0_Init(Timer0_cfg_t *T0_cfg){
	TCCR0A = 0;
	TCCR0B = 0;
	
	/* Mode */
	TCCR0A |= (T0_cfg->mode & 0x03); //WGM1,0
	TCCR0B |= (T0_cfg->mode & 0x08); //WGM2
	
	/* Clock */
	TCCR0B |= T0_cfg->clk;
	
	/* Pins mode */
	TCCR0A |= (T0_cfg->oca_mode << 6);
	TCCR0A |= (T0_cfg->ocb_mode << 4);
}

void Set_Compare_A(uint8_t val){
	OCR0A = val;
}

void Set_Compare_B(uint8_t val){
	OCR0B = val;
}

void Set_COMA_Handler(FunPtr_t pf){
	ComA_Handler = pf;
}
void Set_COMB_Handler(FunPtr_t pf){
	ComB_Handler = pf;
}
void Set_OVF_Handler(FunPtr_t pf){
	Ovf_Handler = pf;
}



ISR(TIMER0_COMPA_vect){
	
	if(ComA_Handler){
		ComA_Handler();
	}
}

ISR(TIMER0_COMPB_vect){
	
	if(ComB_Handler){
		ComB_Handler();
	}
}

ISR(TIMER0_OVF_vect){
	
	if(Ovf_Handler){
		Ovf_Handler();
	}
}