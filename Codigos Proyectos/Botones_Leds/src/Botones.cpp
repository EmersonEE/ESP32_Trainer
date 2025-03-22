#include "Botones.h"

BOTONES::BOTONES(uint8_t _pinB1, uint8_t _pinB2)
{
    pinB1 = _pinB1;
    pinB2 = _pinB2;
    lastStateB1 = HIGH;
    lastStateB2 = HIGH;
}

void BOTONES::init()
{
    pinMode(pinB1, INPUT);
    pinMode(pinB2, INPUT);
}

bool BOTONES::readButtonB1()
{
    bool currentState = digitalRead(pinB1);
    if (currentState == LOW && lastStateB1 == HIGH)
    {
        lastStateB1 = currentState;
        return true;
    }
    lastStateB1 = currentState;
    return false;
}

bool BOTONES::readButtonB2()
{
    bool currentState = digitalRead(pinB2);
    if (currentState == LOW && lastStateB2 == HIGH)
    {
        lastStateB2 = currentState;
        return true;
    }
    lastStateB2 = currentState;
    return false;
}