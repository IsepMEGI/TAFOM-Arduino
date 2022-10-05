#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

enum EnvironmentStatus {CONFORMANT, IRREGULAR, DANGER};

class Environment
{
public:
    static EnvironmentStatus evaluate(float temp, float hum);
};

#endif