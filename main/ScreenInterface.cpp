#include "ScreenInterface.h"


ScreenInterface::ScreenInterface(uint8_t rows, uint8_t cols){
    this->rows = rows;
    this->cols = cols;
    this->screen = NULL;
}

void ScreenInterface::setup()
{
    this->screen = new LiquidCrystal_I2C(I2C_ADDRESS, this->cols, this->rows);
    this->screen->init();
    this->screen->backlight();
}

void ScreenInterface::display(float temp, float hum, int entryCounter){
    screen->clear();
    screen->setCursor(0,0); 
	screen->print("T:");
    screen->print(temp, 1);
	screen->print((char)223);
	screen->print("C");
    screen->print(" ");
    screen->print("H:");
    screen->print(hum,1);
    screen->print("%");

    screen->setCursor(0,1);
    screen->print("Entries: ");
    screen->print(entryCounter);
}