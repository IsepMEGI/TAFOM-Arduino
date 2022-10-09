#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#include "Interface.h"

class ScreenInterface: public Interface
{
private:
    uint8_t rows;
    uint8_t cols;
    LiquidCrystal_I2C lcd;
public:
    Screen(uint8_t rows, uint8_t cols);
    void display(float temp, float hum, int entryCounter);
    void setup();
};

#endif