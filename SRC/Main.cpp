#include "lib/VWAPI.hpp"

int main() {
  VWAPI::init();
  UART u;
  u.write("\n\n==============\n VWAPI SERIAL\n==============\n\n");
  while(true) {
    wait_ms(1000);
  }
}
