#include "ScreenInterface.h"


ScreenInterface::ScreenInterface(uint8_t rows, uint8_t cols){
    this->rows = rows;
    this->cols = cols;
    this->screen = NULL;
}

void ScreenInterface::setup()
{
    Wire.begin();
    uint8_t error, address;
    Serial.println("Scanning I2C devices...");
    for(address = 1; address < 127; address++ )
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            break;
        }
    }
    Serial.print("Found screen at address ");
    Serial.println(address);

    this->screen = new LiquidCrystal_I2C(address, this->cols, this->rows);
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