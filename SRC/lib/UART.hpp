#pragma once
#include "GPIO.hpp"

class UART {
    volatile unsigned int* reg;
public:
    UART() {
        reg = (unsigned int*) 0x20201000;
        GPIO(14, GPIO::ALT0);
        GPIO(15, GPIO::ALT0);
        reg[9] = 26;
        reg[10] = 5; 
        reg[11] = (7 << 4);
        reg[12] = (3 << 7) | 0x01;
    }

    void write(char* string) {
        while(*string) {
            while(reg[6] & (1 << 5));
            reg[0] = *(string++);
        }
    }

    char* read(int bytes) {
        if(reg[6] & (1 << 4)) return 0;
        char data[bytes];
        for(int i = 0; !(reg[6] & (1 << 4)); i++) {
            data[i] = reg[0] & 0xFF;
        } char* ptr = data;
        return ptr;
    }
};