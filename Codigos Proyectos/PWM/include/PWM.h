#ifndef PWM_H
#define PWM_H
#include <Arduino.h>
class PWM
{

public:
    PWM(uint8_t _pinPWM, uint8_t _pinPot);
    void init(uint8_t channel, uint32_t frecuency, uint8_t resolution);
    void writePWM(uint8_t pwmValue);
    uint8_t readPot();
    float showVoltage(uint8_t pwmValue);

private:
uint8_t pinPWM;
uint8_t ledChannel;
uint8_t pinPot;
};

#endif