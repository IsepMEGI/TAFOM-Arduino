#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <stdint.h>
#include <MFRC522.h>
#include <SPI.h>
#include "Comment.h"

class RFID
{
private:
    uint8_t pinSlaveSelect;
    uint8_t pinReset;
    MFRC522 mfrc522;
public:
    String ID;
    RFID(uint8_t pinSlaveSelect, uint8_t pinReset);
    void setup();
    bool checkCard();
};

#endif