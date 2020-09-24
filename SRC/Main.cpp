#include "lib/GPIO.hpp"

int main() {
    GPIO g(21, GPIO::OUTPUT);
    g.setLevel(true);
}
