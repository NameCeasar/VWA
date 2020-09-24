#pragma once

class Timer {
    bool paused;
    unsigned int val;
    unsigned int start;
    volatile unsigned int* reg;
public:
    Timer() {
        reg = (volatile unsigned int*) 0x20003000;
        val = 0;
        start = 0;
        paused = true;
    }

    void start() {
        start = reg[1];
        paused = false;
        val = 0;
    }

    void stop() {
        paused = false;
        val = reg[1] - start;
        start = 0;
    }

    void pause();
    void resume();
    unsigned int get();
    unsigned int get_ms();
    unsigned int get_ys();
};