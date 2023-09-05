

#include "EXTI.h"

static void(*EXTI_Handler[2])(void) = {0};

void EXTI_Enable(EXTI_Line_t line){
	
	SET_BIT(EIMSK,line);
}
void EXTI_Disable(EXTI_Line_t line){
	
	CLR_BIT(EIMSK,line);
}

void EXTI_Trigger(EXTI_Line_t line, EXTI_TrigSrc_t edge){
	
	uint8_t idx = line<<1;
	
	EICRA &= ~(3<<idx);
	EICRA |= edge;
}
void EXTI_ClearFlag(EXTI_Line_t line){
	
	SET_BIT(EIFR,line);
}

void EXTI_SetHandler(EXTI_Line_t line, void (*pf)(void)){
	
	EXTI_Handler[line] = pf;
}


void EXTI_Init(EXTI_Line_t line, EXTI_TrigSrc_t edge, void (*pf)(void)){
	
	EXTI_ClearFlag(line);
	
	EXTI_Trigger(line, edge);
	EXTI_SetHandler(line, pf);
}

ISR(INT0_vect){
	if(EXTI_Handler[0]){
		(*EXTI_Handler[0])();
	}
}

ISR(INT1_vect){
	if(EXTI_Handler[1]){
		(*EXTI_Handler[1])();
	}
}