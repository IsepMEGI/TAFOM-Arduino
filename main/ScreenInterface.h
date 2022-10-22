#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "Interface.h"
#include "Comment.h"

class ScreenInterface: public Interface
{
private:
    uint8_t rows;
    uint8_t cols;
    LiquidCrystal_I2C* screen;
public:
    /// @brief Liquid Crystal LCD screen for Arduino using I2C interface
    /// @param rows Screen row count
    /// @param cols Screen column count
    ScreenInterface(uint8_t rows, uint8_t cols);
    void display(float temp, float hum, int entryCounter);
    void setup();
};

#endif