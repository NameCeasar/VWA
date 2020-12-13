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
        reg[3] = address;
        reg[4] = data;
        reg[5] = freq;
        reg[7] = csto;
        reg[0] &= ~(1);
        reg[0] |= (1 << 7);
        while(!(reg[1] & 0x102));
        reg[1] |= 0x102;
    }

    void write(char* data, int len) {
        reg[2] = len;
        reg[3] = address;
        for(int i = 0; i < len; i++) reg[4] = data[i];
        reg[5] = freq;
        reg[7] = csto;
        reg[0] &= ~(1);
        reg[0] |= (1 << 7);
        while(!(reg[1] & 0x102));
        reg[1] |= 0x102;
    }

    char read() {
        reg[2] = 1;
        reg[3] = address;
        reg[5] = freq;
        reg[7] = csto;
        reg[0] |= (1 << 7) | 1;
        while(!(reg[1] & 0x102));
        reg[1] |= 0x102;
        return reg[4];
    }

    char* read(int len) {
        char out[len];
        reg[2] = len;
        reg[3] = address;
        reg[5] = freq;
        reg[7] = csto;
        reg[0] |= (1 << 7) | 1;
        while(!(reg[1] & 0x102));
        reg[1] |= 0x102;
        for(int i = 0; i < len; i++) out[i] = reg[4];
        char* ptr = out;
        return ptr;
    }

    char transfer(char data) {
        reg[2] = 1;
        reg[3] = address;
        reg[4] = data;
        reg[5] = freq;
        reg[7] = csto;
        reg[0] &= ~(1);
        reg[0] |= (1 << 7);
        while(!(reg[1] & 1));
        reg[0] |= (1 << 7) | 1;
        while(!(reg[1] & 0x102));
        reg[1] |= 0x102;
        return reg[4];
    }

    char* transfer(char* data, int wlen, int rlen) {
        char out[rlen];
        reg[2] = wlen;
        reg[3] = address;
        for(int i = 0; i < wlen; i++) reg[4] = data[i];
        reg[5] = freq;
        reg[7] = csto;
        reg[0] &= ~(1);
        reg[0] |= (1 << 7);
        while(!(reg[1] & 1));
        reg[2] = rlen;
        reg[0] |= (1 << 7) | 1;
        while(!(reg[1] & 0x102));
        reg[1] |= 0x102;
        for(int i = 0; i < rlen; i++) out[i] = reg[4];
        char* ptr = out;
        return ptr;
    }
};