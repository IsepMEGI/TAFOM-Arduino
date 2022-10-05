#ifndef LIGHT_INTERFACE_H
#define LIGHT_INTERFACE_H

#include <stdint.h>

enum LightColor {GREEN, YELLOW, RED};

class LightInterface
{
private:
    uint8_t pin;
public:
    LightInterface(uint8_t pin);
    void set(LightColor color);
};


#endif