#include "ScreenInterface.h"


ScreenInterface::ScreenInterface(uint8_t rows, uint8_t cols){
    this->rows = rows;
    this->cols = cols;
    this->screen = NULL;
}

void ScreenInterface::setup()
{
    Wire.begin();
    byte error, address, screenAddress;
    int Devices;
    spl("Scanning...");
    Devices = 0;
    for(address = 1; address < 127; address++ )
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            sp("I2C device found at address 0x");
            if (address<16)
                sp("0");
            sp(address);
            spl("  !");
            Devices++;
            screenAddress = address;
        }
        else if (error==4)
        {
            sp("Unknown error at address 0x");
            if (address<16)
                sp("0");
            spl(address)
        }
    }
    if (Devices == 0)
        spl("No I2C devices found\n");

    this->screen = new LiquidCrystal_I2C(screenAddress, this->cols, this->rows);
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