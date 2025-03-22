#ifndef BOTONES_H
#define BOTONES_H

#include <Arduino.h>
class BOTONES
{
public:
    BOTONES(uint8_t _pinB1, uint8_t _pinB2);
    void init();
    bool readButtonB1();
    bool readButtonB2();

private:
    uint8_t pinB1;
    uint8_t pinB2;
    uint8_t lastStateB1, lastStateB2;
};

#endif