#include <avr/io.h>

char iomap[8] = {0xD0, 0xD2, 0xD1, 0xC3, 0xC2, 0xC1, 0xD3, 0xC0};

void init() {
	DDRA = 0x00;
	DDRB = 0x4F;
	DDRC = 0xF0;
	DDRD = 0xF0;
}

void setMode(char io) {
	
}

void setLevel(char io, bool lvl) {
	
} 

bool getLevel(char io) {
	
}

int getAnalog(char adc) {
	
}

void setMotor(char motor, char pwm) {
	
} 

int getCS(char motor) {
	
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

