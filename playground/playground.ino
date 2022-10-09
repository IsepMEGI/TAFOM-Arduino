#include "ScreenInterface.h"

ScreenInterface screen(16, 2);

void setup()
{
    Serial.begin(9600);
    screen.setup();
}

void loop()
{
    for (size_t i = 0; i < 10; i++)
    {
        screen.display((float)i/10, (float)i/5, i);
        delay(3000);
    }
    
}

