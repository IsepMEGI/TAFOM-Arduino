#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

#include <Arduino.h>
#include "Interface.h"

class SerialInterface: public Interface
{
public:
    static void display(float temp, float hum, int entryCounter);
};

#endif