

#include "gpio.h"

void PinDir(PinType_t pin, uint8_t dir)
{
	uint8_t idx = pin;
	
	if(dir == OUTPUT){
		
		if(pin <= RB7){
			SET_BIT(DDRB,idx);
		}
		else if(pin <= RC7){
			idx = pin - 8;
			SET_BIT(DDRC,idx);
		}
		else if(pin <= RD7){
			idx = pin - 16;
			SET_BIT(DDRD,idx);
		}
	}
	
	else{
		
		if(pin <= RB7){
			CLR_BIT(DDRB,idx);
		}
		else if(pin <= RC7){
			idx = pin - 8;
			CLR_BIT(DDRC,idx);
		}
		else if(pin <= RD7){
			idx = pin - 16;
			CLR_BIT(DDRD,idx);
		}
		
	}
}



void PinWrite(PinType_t pin, uint8_t val)
{
	uint8_t idx = pin;
	
	if(val == HIGH){
		
		if(pin <= RB7){
			SET_BIT(PORTB,idx);
		}
		else if(pin <= RC7){
			idx = pin - 8;
			SET_BIT(PORTC,idx);
		}
		else if(pin <= RD7){
			idx = pin - 16;
			SET_BIT(PORTD,idx);
		}
		
	}
	
	else{
		
		if(pin <= RB7){
			CLR_BIT(PORTB,idx);
		}
		else if(pin <= RC7){
			idx = pin - 8;
			CLR_BIT(PORTC,idx);
		}
		else if(pin <= RD7){
			idx = pin - 16;
			CLR_BIT(PORTD,idx);
		}
		
	}
}


void PinToggle(PinType_t pin)
{
	uint8_t idx = pin;
	
	if(pin <= RB7){
		TOGGLE_BIT(PORTB,idx);
	}
	else if(pin <= RC7){
		idx = pin - 8;
		TOGGLE_BIT(PORTC,idx);
	}
	else if(pin <= RD7){
		idx = pin - 16;
		TOGGLE_BIT(PORTD,idx);
	}
	
}
uint8_t GetPin(PinType_t pin)
{
	uint8_t idx = pin;
	
	if(pin <= RB7){
		return GET_BIT(PINB,idx);
	}
	else if(pin <= RC7){
		idx = pin - 8;
		return GET_BIT(PINC,idx);
	}
	else if(pin <= RD7){
		idx = pin - 16;
		return GET_BIT(PIND,idx);
	}
	return 0;
}

void PortDir(PortType_t port, uint8_t dir){
	
	if(dir == OUTPUT){
		switch(port){
			case PRTB: DDRB = 0xFF; break;
			case PRTC: DDRC = 0xFF; break;
			case PRTD: DDRD = 0xFF; break;
		}
	}
	else{
		switch(port){
			case PRTB: DDRB = 0x00; break;
			case PRTC: DDRC = 0x00; break;
			case PRTD: DDRD = 0x00; break;
		}
	}
}
void PortWrite(PortType_t port, uint8_t val){
	if(val == HIGH){
		switch(port){
			case PRTB: PORTB = 0xFF; break;
			case PRTC: PORTC = 0xFF; break;
			case PRTD: PORTD = 0xFF; break;
		}
	}
	else{
		switch(port){
			case PRTB: PORTB = 0x00; break;
			case PRTC: PORTC = 0x00; break;
			case PRTD: PORTD = 0x00; break;
		}
	}
}
uint8_t ReadPort(PortType_t port){
	
	switch(port){
		case PRTB: return PINB;
		case PRTC: return PINC;
		case PRTD: return PIND;
	}
	return 0;
}