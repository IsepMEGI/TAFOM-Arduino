#include "LightInterface.h"

LightInterface::LightInterface(uint8_t pinGreen, uint8_t pinYellow, uint8_t pinRed)
{
    this->pinGreen = pinGreen;
    this->pinYellow = pinYellow;
    this->pinRed = pinRed;
}

void LightInterface::setup()
{
   
    pinMode(this->pinGreen, OUTPUT); 
    pinMode(this->pinYellow, OUTPUT);
    pinMode(this->pinRed, OUTPUT);    
    
    digitalWrite(pinGreen, HIGH);
    digitalWrite(pinYellow, LOW);
    digitalWrite(pinRed, LOW);
}

void LightInterface::set(LightColor color)
{
    if (color == this->currentColor)
    {
        return;
    }

    switch (color)
    {
    case LightColor::GREEN:
        digitalWrite(pinGreen, HIGH);
        digitalWrite(pinYellow, LOW);
        digitalWrite(pinRed, LOW);
        break;
    case LightColor::YELLOW:
        digitalWrite(pinYellow, HIGH);
        digitalWrite(pinGreen, LOW);
        digitalWrite(pinRed, LOW);
        break;
    case LightColor::RED:
        digitalWrite(pinGreen, LOW);
        digitalWrite(pinYellow, LOW);
        digitalWrite(pinRed, HIGH);
        break;
    default:
        digitalWrite(pinGreen, HIGH);
        digitalWrite(pinYellow, LOW);
        digitalWrite(pinRed, LOW);
        break;
    }
    this->currentColor = color;
}