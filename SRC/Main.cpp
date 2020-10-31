#include "lib/VWAPI.hpp"

int main() {
  VWAPI::init();
  //UART u;
  GPIO a(15, GPIO::OUTPUT);
  GPIO b(14, GPIO::OUTPUT);
  GPIO c(2, GPIO::OUTPUT);
  GPIO d(3, GPIO::OUTPUT);
  while(true) {
    a.setLevel(true);
    b.setLevel(true);
    c.setLevel(true);
    d.setLevel(true);
    wait_ms(100);
    a.setLevel(false);
    b.setLevel(false);
    c.setLevel(false);
    d.setLevel(false);
    wait_ms(100);
  }
}
