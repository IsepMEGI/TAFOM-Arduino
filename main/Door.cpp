#include "Door.h"

// TODO Implement door opening and closing

Door::Door(uint8_t pin) // funçao que se chama door e tem variavel PIN é a funçao door this->servo pin.
{
    this->pin = pin;
}

void Door::setup()
{
    this->servo = Servo();
    this->servo.attach(this->pin); // Associar o objeto this->servo ao pin de controlo
    this->servo.write(0); // posição inicial da porta
    delay(20 * 180);
}

void Door::open()
{
    //delay(20);  Tempo que demora a mover um grau

    if (this->servo.read() == 0)
    {
        this->servo.write(90);
        this->lastOpen = millis();
    }

}

void Door::close()
{
    if (this->servo.read() == 90)
    {
        this->servo.write(0);
    }
}

bool Door::isOpen()
{
    return this->servo.read() == 90;
}