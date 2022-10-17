#include "Door.h"
Servo servo; // criar um objeto servo

// TODO Implement door opening and closing

Door::Door(uint8_t pin) // funçao que se chama door e tem variavel PIN é a funçao door servo pin.
{
    this->pin = pin;
}

void Door::setup()
{
    servo.attach(this->pin); // Associar o objeto servo ao pin de controlo
    servo.write(0); // posição inicial da porta
    delay(20 * 180);
}

void Door::open()
{
    //delay(20);  Tempo que demora a mover um grau

    if (servo.read() == 0)
    {
        servo.write(90);
        this->lastOpen = millis();
    }

}

void Door::close()
{
    if (servo.read() == 90)
    {
        servo.write(0);
    }
}

bool Door::isOpen()
{
    return servo.read() == 90;
}