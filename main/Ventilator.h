#ifndef VENTILATOR_H
#define VENTILATOR_H

#include <stdint.h>

enum VentilatorSpeed {MINIMUM, MEDIUM, MAXIMUM};

class Ventilator
{
private:
    uint8_t pinSpeed;
    uint8_t pinDirA;
    uint8_t pinDirB;
public:
    VentilatorSpeed currentSpeed;
    Ventilator(uint8_t pinSpeed, uint8_t pinDirA, uint8_t pinDirB);
    void run(VentilatorSpeed speed);
    void setup();
};

#endif