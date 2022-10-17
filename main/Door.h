#ifndef DOOR_H
#define DOOR_H
#include <stdint.h>
#include <Servo.h>
#include <Arduino.h>

class Door
{
private:
    uint8_t pin;
public:
    unsigned long lastOpen;
    Door(uint8_t pin);
    void setup();
    void open();
    void close();
    bool isOpen();
};

#endif