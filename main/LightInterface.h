#ifndef LIGHT_INTERFACE_H
#define LIGHT_INTERFACE_H

#include <Arduino.h>
#include <stdint.h>

#include "Comment.h"

enum LightColor {GREEN, YELLOW, RED};

class LightInterface
{
private:
    uint8_t pinGreen;
    uint8_t pinYellow;
    uint8_t pinRed;
    LightColor currentColor = LightColor::GREEN;
public:
    LightInterface(uint8_t pinGreen, uint8_t pinYellow, uint8_t pinRed);
    void setup();
    void set(LightColor color);
};


#endif