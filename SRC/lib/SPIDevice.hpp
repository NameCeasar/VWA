#pragma once
#include "GPIO.hpp"

class SPIDevice {
    char cs;
    char mode;
    bool pulse;
    unsigned int freq;
    volatile unsigned int* reg;
public:
    SPIDevice() {}

    SPIDevice(char cs, char mode, bool pulse, unsigned int freq) {
        this->reg = (unsigned int*) 0x20204000;
        this->cs = cs;
        this->mode = mode;
        this->pulse = pulse;
        this->freq = (125000000/freq)*2;
        GPIO(9, GPIO::ALT0);
        GPIO(10, GPIO::ALT0);
        GPIO(11, GPIO::ALT0);
        GPIO(cs, GPIO::OUTPUT).setLevel(true);
    }

    void setFrequency(unsigned int freq) {
        this->freq = (125000000/freq)*2;
    }

    void setMode(char mode) {
        this->mode = mode;
    }

    void setPulse(bool pulse) {
        this->pulse = pulse;
    }

    unsigned char transfer(unsigned char data) {
        GPIO(cs).setLevel(false);
        reg[0] = (mode << 2);
        reg[2] = freq;
        reg[0] |= (3 << 4) | (1 << 7);
        reg[1] = data;
        while(!(reg[0] & (1<<16)));
        GPIO(cs).setLevel(true);
        return reg[1];
    }

    unsigned char* transfer(unsigned char* data, unsigned int len) {
        unsigned char out[len];
        if(pulse) {
            for(int i = 0; i < len; i++) out[i] = transfer(data[i]);
        } else {
            GPIO(cs).setLevel(false);
            reg[0] = (mode << 2);
            reg[2] = freq;
            reg[0] |= (3 << 4) | (1 << 7);
            for(int i = 0; i < len; i++) reg[1] = data[i];
            while(!(reg[0] & (1<<16)));
            for(int i = 0; i < len; i++) out[i] = reg[1];
            GPIO(cs).setLevel(true);
        } unsigned char* ptr = out;
        return ptr;
    }
};