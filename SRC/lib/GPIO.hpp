#pragma once

class GPIO {
    volatile unsigned int* reg;
    char id;
public:
    enum Mode { INPUT, OUTPUT, ALT0 = 4, ALT1 = 5, ALT2 = 6, ALT3 = 7, ALT4 = 3, ALT5 = 2};

    GPIO() {}

    GPIO(char pin) {
        reg = (unsigned int*) 0x20200000;
        id = pin;
    }

    GPIO(char pin, Mode mode) {
        reg = (unsigned int*) 0x20200000;
        id = pin;
        setMode(mode);
    }

    Mode getMode() {
        return static_cast<Mode>((reg[id/10] >> ((id % 10) * 3)) & 0x07);
    }

    void setMode(Mode mode) {
        reg[id/10] &= ~(0x07 << ((id % 10) * 3));
        reg[id/10] |= ((mode & 0x07) << ((id % 10) * 3));
    }

    bool getLevel()  {
        return reg[13 + id/32] & (1 << (id % 32));
    }

    void setLevel(bool lvl) {
        reg[lvl?7:10 + (id/32)] = (1 << (id % 32));
    }
}; 