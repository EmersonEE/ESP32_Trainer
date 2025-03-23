#include "PWM.h"

PWM::PWM(uint8_t _pinPWM, uint8_t _pinPot)
{
    pinPWM = _pinPWM;
    pinPot = _pinPot;
}

void PWM::init(uint8_t channel, uint32_t frecuency, uint8_t resolution)
{
    ledChannel = channel;
    ledcSetup(ledChannel, frecuency, resolution);
    ledcAttachPin(pinPWM, ledChannel);
}

void PWM::writePWM(uint8_t pwmValue)
{
    ledcWrite(ledChannel, pwmValue);
}

uint8_t PWM::readPot()
{
    int readPot = analogRead(pinPot);
    return map(readPot, 0, 4095, 0, 255);
}

float PWM::showVoltage(uint8_t pwmValue)
{
    int readPot = analogRead(pinPot);
    int volMap = map(readPot, 0, 4095, 0, 255);
    float valueVol = (3.30) * volMap / 255.0;
    return valueVol;
}