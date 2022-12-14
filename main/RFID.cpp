#include "RFID.h"

RFID::RFID(uint8_t pinSlaveSelect, uint8_t pinReset)
{
    this->pinSlaveSelect = pinSlaveSelect;
    this->pinReset = pinReset;
}

void RFID::setup()
{
    this->mfrc522 = MFRC522(pinSlaveSelect, pinReset);
    SPI.begin();
    this->mfrc522.PCD_Init();
    spl("rfid setup done");
}

bool RFID::checkCard()
{
    // Getting ready for Reading PICCs
    if (!this->mfrc522.PICC_IsNewCardPresent())
    { // If a new PICC placed to RFID reader continue
        return false;
    }
    if (!this->mfrc522.PICC_ReadCardSerial())
    { // Since a PICC placed get Serial and continue
        return false;
    }
    spl("card is present");
    String tagID = "";
    for (uint8_t i = 0; i < 4; i++)
    { // The MIFARE PICCs that we use have 4 byte UID
        tagID.concat(String(this->mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
    }
    tagID.toUpperCase();
    sp("tagID = ");
    spl(tagID);
    this->ID = tagID;
    this->mfrc522.PICC_HaltA(); // Stop reading
    return true;
}