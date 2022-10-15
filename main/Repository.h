#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <Arduino.h>

class Repository
{
public:
    void setup();
    void save(float temperature, float humidity);
};

#endif