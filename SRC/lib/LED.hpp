#pragma once
#include "GPIO.hpp"

class LED {
    GPIO* red;
    GPIO* green;
public:
    enum Color {oFF, RED, GREEN, YELLOW};
    
    LED() {
        red = &GPIO(21,GPIO::OUTPUT);
        green = &GPIO(20,GPIO::OUTPUT);
    }

    void set(Color c) {
        red->setLevel(c & 0x01);
        green->setLevel( c & 0x02);
    }
};