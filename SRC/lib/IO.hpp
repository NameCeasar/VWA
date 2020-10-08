#pragma once
#include "SPIDevice.hpp"

class IO {
    char id;
    SPIDevice mega;
public:
    enum Mode {INPUT, OUTPUT = 0x10};

    IO () {}

    IO(char id) {
        this->id = id > 8 ? 8 : (id < 1 ? 1 : id);
        this->mega = SPIDevice(22, 0, true, 300000);
    }

    IO(char id, Mode m) {
        this->id = id > 8 ? 8 : (id < 1 ? 1 : id);
        this->mega = SPIDevice(22, 0, true, 300000);
        this->mega.transfer(m + this->id - 1);
    }

    void setMode(Mode m) {
        this->mega.transfer(m + this->id - 1);
    }

    void setLevel(bool lvl) {
        this->mega.transfer((lvl ? 0x30 : 0x20) + this->id - 1);
    }

    bool getLevel() {
        mega.transfer(0x40 + this->id - 1);
        return (bool) this->mega.transfer(0x00);
    }
};