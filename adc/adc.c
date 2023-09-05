

#include "adc.h"
static void (*handler)(void);

static adc_cfg_t *config;

void ADC_Init(adc_cfg_t *cfg)
{
	ADMUX = 0;
	ADCSRA = 0;
	ADCSRB = 0;
	
	/* Reference voltage */
	ADMUX |= (cfg->ref << 6);
	
	/* Channel */
	ADMUX |= cfg->channel;
	
	
	/* Pre-scaler */
	ADCSRA |= cfg->scaler;
	
	/* Trigger source if in auto trigger mode */
	ADCSRA |= (cfg->mode << 5);
	
	if(NONE != cfg->trigger_src){
		ADCSRB |= cfg->trigger_src;
	}
	
	/* Enable */
	SET_BIT(ADCSRA,ADEN);
	
	config = cfg;
}

uint16_t ADC_Read(Channel_t ch){
	
	uint16_t res;
	/* Channel */
	ADMUX &= 0xF0;
	ADMUX |= ch;
	
	SET_BIT(ADCSRA,ADSC); /* Start conversion */
	while(GET_BIT(ADCSRA,ADSC)); /* Wait for conversion */
	
	res = ADCL + (ADCH << 8);
	return res;
}

void ADC_SetCallBack(void(*pf)(void)){
	handler = pf;
}

void ADC_ReadAsync(void(*pf)(void)){
	handler = pf;
	SET_BIT(ADCSRA,ADSC);
}

void ADC_Start(void){
	
	SET_BIT(ADCSRA,ADSC);
}

uint16_t ADC_GetResult(void){
	uint16_t res;
	res = ADCL + (ADCH << 8);
	return res;
}

ISR(ADC_vect)
{
	if(handler)
		handler();
}