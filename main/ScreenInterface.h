#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

class Screen
{
private:
    uint8_t pin;
public:
    Screen(uint8_t pin);
    void display(int entryCounter);
};

#endif