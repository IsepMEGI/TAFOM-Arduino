#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#define DANGER_TEMP_THRESHOLD 25
#define DANGER_HUM_THRESHOLD 80
#define IRREGULAR_TEMP_THRESHOLD 23
#define IRREGULAR_HUM_THRESHOLD 50


enum EnvironmentStatus {CONFORMANT, IRREGULAR, DANGER};

class Environment
{
public:
    static EnvironmentStatus evaluate(float temp, float hum);
};

#endif