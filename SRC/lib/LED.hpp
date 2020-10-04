#pragma once
#include "GPIO.hpp"

class LED {
public:
    enum Color {OFF, RED, GREEN, YELLOW};
    
    LED() {
       GPIO(24,GPIO::OUTPUT);
       GPIO(25,GPIO::OUTPUT);
    }

    void set(Color c) {
        GPIO(25).setLevel(c & 0x01);
        GPIO(24).setLevel(c & 0x02);
    }
};