#pragma once
#include "GPIO.hpp"

class UART {
    volatile unsigned int* reg;
public:
    UART() {
        reg = (unsigned int*) 0x20215000;
        GPIO(14, GPIO::ALT5);
        GPIO(15, GPIO::ALT5);
        reg[1] = 1;
        reg[19] = 1 << 7;
        reg[16] = 0x0E;
        reg[17] = 0x01;
        reg[19] = 1;
        reg[24] = 3;
    }

    void print(char* string) {
        while(*string) {
            while(!(reg[25] & (1 << 3)));
            reg[16] = *(string++);
        }
    }
};