#ifndef INTERFACE_H
#define INTERFACE_H

#include <Arduino.h>

class SerialInterface
{
public:
    static void displayth(float temperature, float humidity);
};

#endif