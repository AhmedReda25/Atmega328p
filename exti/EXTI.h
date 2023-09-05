

#ifndef EXTI_H
#define EXTI_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bitmath.h"

typedef enum
{
	EXTI0 = 0,
	EXTI1
}EXTI_Line_t;

typedef enum
{
	EXTI_LOW,
	EXTI_CHANGE,
	EXTI_FALLING,
	EXTI_RISING
	
}EXTI_TrigSrc_t;

void EXTI_Enable(EXTI_Line_t line);
void EXTI_Disable(EXTI_Line_t line);

void EXTI_Trigger(EXTI_Line_t line, EXTI_TrigSrc_t edge);
void EXTI_ClearFlag(EXTI_Line_t line);

void EXTI_SetHandler(EXTI_Line_t line, void (*pf)(void));

void EXTI_Init(EXTI_Line_t line, EXTI_TrigSrc_t edge, void (*pf)(void));
#endif