#pragma once
#include "GPIO.hpp"

class I2CDevice {
    volatile unsigned int* reg;
    char address;
    int freq;
    int csto;
public:
    I2CDevice() {}

    I2CDevice(char address, int freq, int csto) {
        this->reg = (unsigned int*) 0x20804000;
        this->address = address & 0x7F;
        this->freq = (125000000/freq)*2;
        this->csto = csto ? csto : 0x40;
        GPIO(2, GPIO::ALT0);
        GPIO(3, GPIO::ALT0);
        reg[0] |= (1 << 15);
    }

    void setFrequency(int freq) {
        this->freq = (125000000/freq)*2;
    }

    void setClockStrechTimeout(int csto) {
        this->csto = csto ? csto : 0x40;
    }

    void write(char data) {
        reg[2] = 1;
        reg[3] = a;
        reg[4] = data;
        reg[5] = freq;
        reg[7] = csto;
        reg[0] &= ~(1);
        reg[0] |= (1 << 7);
        while(!(reg[1] & 0x102));
        r[1] |= 0x102;
    }

    void write(char* data, int len) {
        reg[2] = len;
        reg[3] = a;
        for(int i = 0; i < len; i++) reg[4] = data[i];
        reg[5] = freq;
        reg[7] = csto;
        reg[0] &= ~(1);
        reg[0] |= (1 << 7);
        while(!(reg[1] & 0x102));
        r[1] |= 0x102;
    }

    char read() {

    }

    char* read(int len) {

    }

    char transfer(char data) {

    }

    char* transfer(char* data, int wlen, int rlen) {

    }
}