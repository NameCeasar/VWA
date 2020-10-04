#pragma once
#include "SPIDevice.hpp"

class ADC {
    char id;
    SPIDevice mega;
public:
    enum Mode {INPUT, OUTPUT = 0x10};

    ADC() {}

    ADC(char id) {
        this->id = id > 3 ? 3 : (id < 1 ? 1 : id);
        this->mega = SPIDevice(22, 0, true, 1000000);
    }

    ADC(char id, Mode m) {
        this->id = id > 3 ? 3 : (id < 1 ? 1 : id);
        this->mega = SPIDevice(22, 0, true, 1000000);
        this->mega.transfer(m + this->id + 7);
    }

    void setMode(Mode m) {
        this->mega.transfer(m + this->id + 7);
    }

    void setLevel(bool lvl) {
        this->mega.transfer((lvl ? 0x30 : 0x20) + this->id + 7);
    }

    bool getDigital() {
        mega.transfer(0x40 + this->id + 7);
        return (bool) this->mega.transfer(0x00);
    }

    unsigned int getAnalog() {
        mega.transfer(0x4F + this->id);
        unsigned int out = ((unsigned int) mega.transfer(0x00)) << 8;
        return out | mega.transfer(0x00);
    }
};