#include "SerialInterface.h"


void SerialInterface::display(float temp, float hum, int entryCounter){
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.print(" ");
    Serial.print((char)176);
    Serial.print("C | ");
    Serial.print(" ");
    Serial.print("Humidity = ");
    Serial.print(humidity);
    Serial.println(" % ");
    Serial.println("");

}