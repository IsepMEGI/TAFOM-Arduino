#ifndef VENTILATOR_H
#define VENTILATOR_H

class Ventilator
{
public:
    bool isRunning;
    Ventilator(int pin);
    void run();
    void stop();
};

#endif