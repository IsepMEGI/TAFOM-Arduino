#include "LightInterface.h"


LightInterface::LightInterface(uint8_t pinGreen, uint8_t pinYellow, uint8_t pinRed)
{
    this->pinGreen = pinGreen;
    this->pinYellow = pinYellow;
    this->pinRed = pinRed;
}

void LightInterface::setup() {
   // Leds ligadas aos pinos 7, 8,9
   pinMode(this->pinGreen, OUTPUT); // Verde
   pinMode(this->pinYellow, OUTPUT); // Amarelo
   pinMode(this->pinRed, OUTPUT); // Vermelho
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
        digitalWrite(pinGreen,HIGH);
        digitalWrite(pinYellow,LOW);
        digitalWrite(pinRed,LOW);
        break;
    case LightColor::YELLOW:
        digitalWrite(pinYellow,HIGH);
        digitalWrite(pinGreen,LOW);
        digitalWrite(pinRed,LOW);
        break;
    case LightColor::RED:
        digitalWrite(pinGreen,LOW);
        digitalWrite(pinYellow,LOW);
        digitalWrite(pinRed,HIGH);
        break;
    default:
        digitalWrite(pinGreen,HIGH);
        digitalWrite(pinYellow,LOW);
        digitalWrite(pinRed,LOW);
        break;
    }
    this->currentColor = color;
}