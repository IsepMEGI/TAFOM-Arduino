#include "Door.h"


Door::Door(uint8_t pin) 
{
    this->pin = pin;
}

void Door::setup()
{
    this->servo.attach(this->pin); 
    this->servo.write(0); 
    spl("Posição inicial porta");
    delay(20 * 180);
}

void Door::open()
{
    if (this->servo.read() == 0)
    {
        this->servo.write(OPEN_ANGLE);
        this->lastOpen = millis();
    }

}

void Door::close()
{

    if (this->servo.read() == OPEN_ANGLE)
    {
        this->servo.write(0);
    }
}

bool Door::isOpen()
{
    return this->servo.read() == OPEN_ANGLE;
}