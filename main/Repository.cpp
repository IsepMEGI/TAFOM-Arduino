#include "Repository.h"

void Repository::setup(){
    Serial.println("CLEARDATA");
    Serial.println("LABEL,Time,Temperature,Humidity");
}

void Repository::save(float temperature, float humidity){
    Serial.println( (String) "DATA,TIME," + temperature + "," + humidity);
}