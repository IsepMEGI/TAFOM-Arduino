#include "Ventilator.h"

Ventilator::Ventilator(int pin){
    // implement...
}

void Ventilator::run(){
    if(this->isRunning){
        return;
    }
    // implement...
    this->isRunning = true;
}

void Ventilator::stop(){
    if(this->isRunning == false){
        return;
    }
    // implement...
    this->isRunning = false;
}
