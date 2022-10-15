#include "LightInterface.h"


LightInterface::LightInterface(uint8_t pin)
{
    this->pin = pin;
}

void setup() {
   // Leds ligadas aos pinos 7, 8,9
   pinMode(7, OUTPUT); // Verde
   pinMode(8, OUTPUT); // Amarelo
   pinMode(9, OUTPUT); // Vermelho
}

void LightInterface::set(LightColor color)
{


    if(temp > DANGER_TEMP_THRESHOLD || hum > DANGER_HUM_THRESHOLD){
        digitalWrite[7,HIGH];
        digitalWrite[8,LOW]
        digitalWrite[9,LOW]
    }

    if(temp > IRREGULAR_TEMP_THRESHOLD || hum > IRREGULAR_HUM_THRESHOLD){
        digitalWrite[7,LOW];
        digitalWrite[8,HIGH]
        digitalWrite[9,LOW]
    }
    return digitalWrite[7,LOW];
        digitalWrite[8,LOW]
        digitalWrite[9,HIGH]


    
}