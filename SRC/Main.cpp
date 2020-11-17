#include "lib/VWAPI.hpp"

int main() {
  VWAPI::init();
  LED l;
  while(true) {
    l.set(LED::GREEN);
    wait_ms(100);
    l.set(LED::RED);
    wait_ms(100);
  }
}
