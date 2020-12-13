#pragma once
#include "IO.hpp"
#include "ADC.hpp"
#include "LED.hpp"
#include "PWM.hpp"
#include "GPIO.hpp"
#include "UART.hpp"
#include "Util.hpp"
#include "Timer.hpp"
#include "I2CDevice.hpp"
#include "SPIDevice.hpp"

#include "ext/Nokia5110.hpp"

namespace VWAPI {

    bool active = false;

    void init() {
        GPIO(18, GPIO::OUTPUT).setLevel(true);

        GPIO(5, GPIO::OUTPUT).setLevel(true);
        GPIO(7, GPIO::OUTPUT).setLevel(true);
        GPIO(17, GPIO::OUTPUT).setLevel(true);
        GPIO(22, GPIO::OUTPUT).setLevel(true);
        GPIO(27, GPIO::OUTPUT).setLevel(true);

        GPIO(24, GPIO::OUTPUT).setLevel(false);
        GPIO(25, GPIO::OUTPUT).setLevel(false);

        wait_ms(100);

        SPIDevice mega(22, 0, true, 300000);
        mega.transfer(0xFF);
        GPIO((mega.transfer(0x00) == 0xAC) ? 24 : 25).setLevel(true);
    }
}