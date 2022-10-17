#include "Environment.h"


EnvironmentStatus Environment::evaluate(float temp, float hum)
{
    if(temp > DANGER_TEMP_THRESHOLD || hum > DANGER_HUM_THRESHOLD){
        return EnvironmentStatus::DANGER;
    }

    if(temp > IRREGULAR_TEMP_THRESHOLD || hum > IRREGULAR_HUM_THRESHOLD){
        return EnvironmentStatus::IRREGULAR;
    }

    return EnvironmentStatus::CONFORMANT;
}