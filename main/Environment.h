#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#define DANGER_TEMP_THRESHOLD
#define DANGER_HUM_THRESHOLD
#define IRREGULAR_TEMP_THRESHOLD
#define IRREGULAR_HUM_THRESHOLD


enum EnvironmentStatus {CONFORMANT, IRREGULAR, DANGER};

class Environment
{
public:
    static EnvironmentStatus evaluate(float temp, float hum);
};

#endif