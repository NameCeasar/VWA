#pragma once
#include "GPIO.hpp"
#include "LED.hpp"

class UART {
    volatile unsigned int* reg;
public:
    UART() {
        reg = (unsigned int*) 0x20201000;
        GPIO(14, GPIO::ALT0);
        GPIO(15, GPIO::ALT0);
        reg[9] = 1;
        reg[10] = 40; 
        reg[11] = (7 << 4);
        reg[12] = (3 << 7) | 0x01;
    }

    void print(char* string) {
        while(*string) {
            while(reg[6] & (1 << 5));
            reg[0] = *(string++);
        }
    }

    char* read(int bytes) {
        return 0;
    }
};