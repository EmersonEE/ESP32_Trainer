#ifndef __PWM_H__
#define __PWM_H__
#include <Arduino.h>
class PWM
{
    /* data */
    public:
    PWM(uint8_t _pinSens);
    uint16_t readRaw();
    uint8_t readMapped();
    float readVoltage();

    private:
    uint8_t pinSens;
 
};


#endif // __PWM_H__