#include "Ventilator.h"

Ventilator::Ventilator(uint8_t pin){
    this->pin = pin;
}

void Ventilator::run(VentilatorSpeed speed){
    // TODO Implement ventilator run method
    this->currentSpeed = speed;
}
