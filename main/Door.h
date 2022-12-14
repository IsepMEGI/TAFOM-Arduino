#ifndef DOOR_H
#define DOOR_H
#include <stdint.h>
#include <Servo.h>
#include <Arduino.h>
#include "Comment.h"

#define OPEN_ANGLE 30
class Door
{
private:
    uint8_t pin;
    Servo servo; 
public:
    unsigned long lastOpen = 0;
    Door(uint8_t pin);
    void setup();
    void open();
    void close();
    bool isOpen();
};

#endif