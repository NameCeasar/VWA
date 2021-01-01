#pragma once
#include "Timer.hpp"
#include "I2CDevice.hpp"

class BNO055 {
    I2CDevice i2c;
public:
    enum Field {EULER_X = 0x1A, EULER_Y = 0x1C, EULER_Z = 0x1E};
    BNO055() {
        i2c = I2CDevice(0x29, 100000, 1000);
        char data[2] = {0x3D, 0x0C};
        i2c.write(data, 2);
        wait_ms(50);
    }

    double getValue(Field f) {
        char data[1] = {(char) f};
        char* out = i2c.command(data, 1, 2);
        int raw = out[0] | ((int) out[1]);
        return ((double) raw) / 16.0;
    }
};