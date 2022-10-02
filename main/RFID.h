#ifndef RFID_H
#define RFID_H

#include <Arduino.h>

class RFID
{
public:
    String cardInfo;
    RFID(int pin);
    bool checkCard();
};

#endif