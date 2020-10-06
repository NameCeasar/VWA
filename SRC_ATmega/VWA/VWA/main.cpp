#include <avr/io.h>
#include <avr/interrupt.h>

char iomap[11] = {0xD0, 0xD2, 0xD1, 0xC3, 0xC2, 0xC1, 0xD3, 0xC0, 0xA1, 0xA2, 0xA3};
int adc[7] = {0, 0, 0, 0, 0, 0, 0};
char pwm[5] = {0, 0, 0, 0, 0};
char spi[3] = {0, 0, 0};
bool adc_sec;

ISR(ADC_vect) {
	if(adc_sec) {
		int adc_l = ADCL;
		int adc_h = ADCH;
		adc[ADMUX + 1] = adc_l | (adc_h << 8);
		ADMUX = (ADMUX < 7) ? (ADMUX + 1) : 1;
	} else {
		ADCL;
		ADCH;
	} ADCSRA |= (1 << ADSC) | (1 << ADIF);
	adc_sec = !adc_sec;
}

ISR(SPI_STC_vect) {
	if(spi[0] == 0) {
		spi[2] = SPDR;
		spi[1] = 0;
	} if(spi[2] >= 0x00 && spi[2] < 0x0B) {
		char loc = iomap[SPDR & 0x0F];
		if((loc & 0xF0) == 0xA0) DDRA &= ~(1 << (loc & 0x0F));
		else if((loc & 0xF0) == 0xC0) DDRC &= ~(1 << (loc & 0x0F));
		else if((loc & 0xF0) == 0xD0) DDRD &= ~(1 << (loc & 0x0F));
		SPDR = 0x00;
	} else if(spi[2] >= 0x10 && spi[2] < 0x1B) {
		char loc = iomap[SPDR & 0x0F];
		if((loc & 0xF0) == 0xA0) DDRA |= (1 << (loc & 0x0F));
		else if((loc & 0xF0) == 0xC0) DDRC |= (1 << (loc & 0x0F));
		else if((loc & 0xF0) == 0xD0) DDRD |= (1 << (loc & 0x0F));
		SPDR = 0x00;
	} else if(spi[2] >= 0x20 && spi[2] < 0x2B) {
		char loc = iomap[SPDR & 0x0F];
		if((loc & 0xF0) == 0xA0) PORTA &= ~(1 << (loc & 0x0F));
		else if((loc & 0xF0) == 0xC0) PORTC &= ~(1 << (loc & 0x0F));
		else if((loc & 0xF0) == 0xD0) PORTD &= ~(1 << (loc & 0x0F));
		SPDR = 0x00;
	} else if(spi[2] >= 0x30 && spi[2] < 0x3B) {
		char loc = iomap[SPDR & 0x0F];
		if((loc & 0xF0) == 0xA0) PORTA |= (1 << (loc & 0x0F));
		else if((loc & 0xF0) == 0xC0) PORTC |= (1 << (loc & 0x0F));
		else if((loc & 0xF0) == 0xD0) PORTD |= (1 << (loc & 0x0F));
		SPDR = 0x00;
	} else if(spi[2] >= 0x40 && spi[2] < 0x4B) {
		spi[1] = 1;
		if(spi[0] == 0) {
			char loc = iomap[SPDR & 0x0F];
			if((loc & 0xF0) == 0xA0) SPDR = PINA  >> (loc & 0x0F) & 1;
			else if((loc & 0xF0) == 0xC0) SPDR = PINC  >> (loc & 0x0F) & 1;
			else if((loc & 0xF0) == 0xD0) SPDR = PIND  >> (loc & 0x0F) & 1;
			else SPDR = 0x00;
		} else SPDR = 0x00;
	} else if(spi[2] >= 0x50 && spi[2] < 0x57) {
		spi[1] = 2;
		if(spi[0] == 0) SPDR = adc[spi[2] & 0x0F] >> 8;
		else if(spi[0] == 1) SPDR = adc[spi[2] & 0x0F] & 0xFF;
		else SPDR = 0x00;
	}  else if(spi[2] >= 0x60 && spi[2] < 0x64) {
		pwm[spi[2] & 0x0F] = 0;
		pwm[4] &= ~(3 << ((spi[2] & 0x0F) * 2));
		SPDR = 0x00;
	}  else if(spi[2] >= 0x64 && spi[2] < 0x6C) {
		spi[1] = 1;
		if(spi[0] == 1) {
			char off = (spi[2] & 0x0F) % 4;
			pwm[off] = SPDR;
			pwm[4] &= ~(3 << (off*2));
			pwm[4] |= ((spi[2] > 0x68 ? 1 : 2) << (off*2));
		} SPDR = 0x00;
	}  else if(spi[2] == 0x6E) {
		spi[1] = 5;
		if(spi[0] > 0) pwm[spi[0] - 1] = SPDR;
		SPDR = 0x00;
	}  else if(spi[2] == 0x6F) {
		pwm[0] = 0;
		pwm[1] = 0;
		pwm[2] = 0;
		pwm[3] = 0;
		pwm[4] = 0;
		SPDR = 0x00;
	} else if(spi[2] == 0xFF) {
		spi[1] = 1;
		if(spi[0] == 0) SPDR = 0xAC;
		else SPDR = 0x00;
	} spi[0] = (spi[0] < spi[1]) ? (spi[0]+1) : 0;
	if(spi[1] == 0) SPDR = 0x00;
}

int main(void) {
	DDRA = 0x00;
	DDRB = 0x4F;
	DDRC = 0xF0;
	DDRD = 0xF0;
	
	PORTD = 0x01; //remove
	
	TCCR1A = 0b10100001;
	TCCR1B = 0b00001010;

	TCCR2A = 0b10100011;
	TCCR2B = 0b00000010;

	ADMUX = 0x00;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIE);
	SPCR = (1<<SPE) | (1<<SPIE);
	SPDR = 0x00;
	sei();
	
	while (1) {
		PORTB = (PORTB & 0xF0) | (pwm[4] >> 4);
		PORTC = (PORTC & 0x0F) | (pwm[4] << 4);
		OCR2A = pwm[0];
		OCR2B = pwm[1];
		OCR1A = pwm[2];
		OCR1B = pwm[3];
	}
}

