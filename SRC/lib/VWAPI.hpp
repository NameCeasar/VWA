#pragma once
#include "IO.hpp"
#include "ADC.hpp"
#include "LED.hpp"
#include "GPIO.hpp"
#include "Timer.hpp"
#include "SPIDevice.hpp"

namespace VWAPI {
    void init() {
        GPIO(18, GPIO::OUTPUT).setLevel(true);
    }
}