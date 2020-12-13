#include "lib/VWAPI.hpp"

int main() {
  VWAPI::init();
  UART u;
  u.write("\n\n==============\n VWAPI SERIAL\n==============\n\n");
  I2CDevice bno(0x29, 10000, 1000);
  char data[2] = {0x3D, 0x0C};
  bno.write(data,2);
  wait_ms(50);
  while(true) {
    int value = (bno.transfer(0x1A) >> 4) | ((int) bno.transfer(0x1B) << 4);
    u.write(toString(value));
    u.write("\n");
    wait_ms(100);
  }
}
