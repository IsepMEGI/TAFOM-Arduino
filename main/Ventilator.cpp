#include "Ventilator.h"
#include <Arduino.h>

Ventilator::Ventilator(uint8_t pinSpeed, uint8_t pinDirA, uint8_t pinDirB){
    this->pinSpeed = pinSpeed;
    this->pinDirA = pinDirA;
    this->pinDirB = pinDirB;
}
void Ventilator::setup(){
    pinMode(this->pinSpeed,OUTPUT);
    pinMode(this->pinDirA,OUTPUT);
    pinMode(this->pinDirB,OUTPUT);
    // Always rotating in the same direction (clockwise)
    digitalWrite(this->pinDirA,HIGH);
    digitalWrite(this->pinDirB,LOW);
    // Startup high to ensure the thing moves
    digitalWrite(this->pinSpeed,HIGH);
    delay(1000);
}

void Ventilator::run(VentilatorSpeed speed){
    if (speed == this->currentSpeed)
    {
        return;
    }
    
    switch (speed) {
    case VentilatorSpeed::MINIMUM:
        analogWrite(this->pinSpeed,90);
        break;
    case VentilatorSpeed::MEDIUM:
        analogWrite(this->pinSpeed,150);
        break;
    case VentilatorSpeed::MAXIMUM:
        analogWrite(this->pinSpeed,200);
        break;
    default:
        analogWrite(this->pinSpeed,90);
        break;
    }
    this->currentSpeed = speed;
}

