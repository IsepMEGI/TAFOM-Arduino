#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <stdint.h>

class RFID
{
private:
    uint8_t pin;
public:
    String cardInfo;
    RFID(uint8_t pin);
    bool checkCard();
};

#endif