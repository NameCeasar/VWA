#include "lib/VWAPI.hpp"

int main() {
   VWAPI::init();
   IO pin(2, IO::INPUT);
   while(true) {
      LED().set(pin.getLevel() ? LED::GREEN : LED::RED);
   }
}
