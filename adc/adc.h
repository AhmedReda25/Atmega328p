#ifndef ADC_H
#define ADC_H


#include <stdint.h>
#include <avr/io.h>
#include "bitmath.h"


#define ADC_IRQ_ENABLE  (SET_BIT(ADCSRA,ADIE))
#define ADC_IRQ_DISABLE (CLR_BIT(ADCSRA,ADIE))

#define ADC_CLEARFLAG   (SET_BIT(ADCSRA,ADIF))

typedef enum
{
	AREF_PIN,
	AVCC,
	INTERNAL_1_1 = 2
	
}adcRef_t;


typedef enum
{
	ADC_CH0=0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7,
	ADC_CH8,
	
}Channel_t;


typedef enum
{
	
	ADC_DIV2 = 1,
	ADC_DIV4,
	ADC_DIV8,
	ADC_DIV16,
	ADC_DIV32,
	ADC_DIV64,
	ADC_DIV128
	
}adcScaler_t;

typedef enum
{
	SINGLE_CONVERSION,
	AUTO_TRIGGER
}adcMode_t;

typedef enum
{
	
	FREE_RUNNING,
	ANALOG_CMP,
	EXTI0_REQ,
	COMPARE_MATCH0A,
	T0_OVF,
	COMPARE_MATCH1B,
	T1_OVF,
	T1_CAPTURE_EVENT,
	NONE
	
}TriggerSrc_t;



typedef struct
{
	adcRef_t ref;
	adcScaler_t scaler;
	TriggerSrc_t trigger_src;
	adcMode_t mode;
	Channel_t channel;
}adc_cfg_t;

/*----------------------------------------------------------------------------------*/

void ADC_Init(adc_cfg_t *cfg);
uint16_t ADC_Read(Channel_t ch);
void ADC_SetCallBack(void(*pf)(void));
void ADC_ReadAsync(void(*pf)(void));
void ADC_Start(void);
uint16_t ADC_GetResult(void);


#endif