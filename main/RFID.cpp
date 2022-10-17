#include "RFID.h"

RFID::RFID(uint8_t pinSlaveSelect, uint8_t pinReset)
{
    this->pinSlaveSelect = pinSlaveSelect;
    this->pinReset = pinReset;
}

void RFID::setup()
{
    this->mfrc522 = MFRC522(pinSlaveSelect, pinReset);
    this->mfrc522.PCD_Init();
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

    /*String tagID = "";
    for ( uint8_t i = 0; i < mfrc522.uid.size; i++) 
    { // I've change with mfrc522.uid.size just to be sure that the code works with different type of rfid tag identifier
    //readCard[i] = mfrc522.uid.uidByte[i];
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Transfoming the bytes of the ID into String object and then join them together
    }
    tagID.toUpperCase(); //This method transfom a String object in the same string but every letters is in CAPSLOCK
    this->ID = tagID; */
    String fakeID = "33 98 34 56";
    this->ID = fakeID;

    this->mfrc522.PICC_HaltA(); // Stop reading
    return true;
}
