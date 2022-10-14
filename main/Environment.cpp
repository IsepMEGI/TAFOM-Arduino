#include "Environment.h"

EnvironmentStatus Environment::evaluate(float temp, float hum)
{
    // TODO Implement environment evaluation method
    if(temp <= 20 && hum <= 50) {
        EnvironmentStatus = CONFORMANT;
    } 
    else if (temp>20 && temp <= 23 && hum <=70 )
    {
        EnvironmentStatus = IRREGULAR;
    }
    else {
        EnvironmentStatus = DANGER;
    }

}