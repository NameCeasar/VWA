#pragma once
#include "GPIO.hpp"

class PWM {
    char channel;
    volatile unsigned int* reg;
public:
    PWM(char channel) {
        this->reg = (unsigned int*) 0x2020C000;
        this->channel = (channel==1) ? 1 : 2;
        volatile unsigned int* clock = (unsigned int*) 0x201010A0;
        GPIO(this->channel + 11,GPIO::ALT0);
        clock[1] = (0x5a << 24) | (8 << 12);
        clock[0] = (0x5a << 24) | (1 << 4) | 0x01;    //LESSON LEARNED: DONT OR SET WRITE ONLY REGS   
        reg[0] |= (0x81) << (this->channel == 1 ? 0 : 8);
        reg[this->channel * 4] = 1000;
    } 

    void set(double value) {
        value = value > 1.0 ? 1.0 : (value < 0.0 ? 0.0 : value);
        reg[this->channel * 4 + 1] = value * 1000.0;
    }
};