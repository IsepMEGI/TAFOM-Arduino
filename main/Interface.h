#ifndef INTERFACE_H
#define INTERFACE_H

class Interface
{
public:
    /// @brief Display the temperature, humidity and door entry count
    /// @param temp temperature
    /// @param hum humidity
    /// @param entryCounter door entry counter 
    virtual void display(float temp, float hum, int entryCounter);
};

#endif