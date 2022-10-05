#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

#include <Arduino.h>

class SerialInterface
{
public:
    static void displayth(float temperature, float humidity);
};

#endif