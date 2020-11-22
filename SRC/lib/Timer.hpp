#pragma once

class Timer {
    bool paused;
    unsigned int val;
    unsigned int started;
    volatile unsigned int* reg;
public:
    Timer() {
        reg = (volatile unsigned int*) 0x20003000;
        val = 0;
        started = 0;
        paused = true;
    }

    void start() {
        started = reg[1];
        paused = false;
        val = 0;
    }

    void stop() {
        paused = true;
        val += reg[1] - started;
        started = 0;
    }

    void pause() {
        paused = true;
        val += reg[1] - started;
        started = 0;
    }

    void resume() {
        if(!paused) return;
        paused = false;
        started = reg[1];
    }

    bool isRunning() {
        return !paused;
    }

    unsigned int get() {
        return (val + paused?0:(reg[1] - started)) / 1000000;
    }

    unsigned int get_ms() {
         return (val + paused?0:(reg[1] - started)) / 1000;
    }

    unsigned int get_us() {
         return val + paused?0:(reg[1] - started);
    }
};

void wait(unsigned int seconds) {
    seconds = (seconds * 1000000) + *((volatile unsigned int*) 0x20003004);
    while(*((volatile unsigned int*) 0x20003004) < seconds);
}

void wait_ms(unsigned int millis) {
    millis = (millis * 1000) + *((volatile unsigned int*) 0x20003004);
    while(*((volatile unsigned int*) 0x20003004) < millis);
}

void wait_us(unsigned int micros) {
    micros = micros + *((volatile unsigned int*) 0x20003004);
    while(*((volatile unsigned int*) 0x20003004) < micros);
}