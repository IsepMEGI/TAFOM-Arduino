#ifndef DOOR_H
#define DOOR_H

#include <stdint.h>
<<<<<<< HEAD
// include <servo>?? 
=======
#include <Servo.h>
>>>>>>> b209b71bcc92ab2f1031e840733bd76a1bc40040

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