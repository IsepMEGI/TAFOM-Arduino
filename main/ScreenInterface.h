#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <stdint.h>
#include "Interface.h"

class ScreenInterface: public Interface
{
private:
    uint8_t pin;
public:
    Screen(uint8_t pin);
    void display(float temp, float hum, int entryCounter);
};

#endif