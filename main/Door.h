#ifndef DOOR_H
#define DOOR_H

#include <stdint.h>

class Door
{
private:
    uint8_t pin;
public:
    bool isOpen;
    unsigned long lastOpen;
    Door(uint8_t pin);
    void open();
    void close();
};

#endif