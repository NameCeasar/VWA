#include "lib/VWAPI.hpp"

int main() {
   VWAPI::init();
   PWM(1).set(0.5);
   while(true) {}
}
