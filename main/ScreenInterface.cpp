#include "ScreenInterface.h"


ScreenInterface::Screen(uint8_t rows, uint8_t cols){
    this->rows = rows;
    this->cols = cols;
}

ScreenInterface::setup()
{
    Wire.begin();
    byte error, address;
    Serial.println("Scanning...");
    for(address = 1; address < 127; address++ )
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            break;
        }
    }
    LiquidCrystal_I2C lcd(address, this->cols, this->rows);
    lcd.begin();
    lcd.backlight();

    this->lcd = lcd;
}

void ScreenInterface::display(float temp, float hum, int entryCounter){
    lcd.clear();
    lcd.setCursor(0,0); 
	lcd.print("T: ");
    lcd.print(temp);
	lcd.print((char)223);
	lcd.print("C");
    lcd.print("  ");
    lcd.print("H:");
    lcd.print(hum);
    lcd.print("%");

    lcd.setCursor(0,1);
    lcd.print("Entrys: ");
    lcd.print(entryCounter);
}