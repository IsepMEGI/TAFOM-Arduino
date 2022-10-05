#ifndef VENTILATOR_H
#define VENTILATOR_H

#include <stdint.h>

enum VentilatorSpeed {MINIMUM, MEDIUM, MAXIMUM};

class Ventilator
{
private:
    uint8_t pin;
public:
    VentilatorSpeed currentSpeed;
    Ventilator(uint8_t pin);
    void run(VentilatorSpeed speed);
};

#endif