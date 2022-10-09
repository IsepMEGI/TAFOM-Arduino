#include "SerialInterface.h"


void SerialInterface::display(float temp, float hum, int entryCounter){
    if (isnan(hum) || isnan(temp)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    Serial.print("Temperature = ");
    Serial.print(temp);
    Serial.print(" ");
    Serial.print((char)176);
    Serial.print("C | ");
    Serial.print(" ");
    Serial.print("Humidity = ");
    Serial.print(hum);
    Serial.println(" % ");
    Serial.println("");

}

void SerialInterface::setup(){}