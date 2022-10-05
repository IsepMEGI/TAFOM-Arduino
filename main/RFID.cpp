#include "RFID.h"

RFID::RFID(uint8_t pin){
    this->pin = pin;
}

bool RFID::checkCard(){
    // TODO Implement rfid card checking/reading method
    // ! remember to save the card info if there is a card present
    return false;
}