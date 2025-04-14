#include <PWM.h>

PWM::PWM(uint8_t _pinSens)
{
    pinSens = _pinSens;
    pinMode(pinSens,INPUT);
}

uint16_t PWM::readRaw()
{
    return analogRead(pinSens);
}

uint8_t PWM::readMapped()
{
    return map(analogRead(pinSens), 0, 4095, 0, 255);
}

float PWM::readVoltage()
{
    return 3.30 * readRaw() / 4095.0;
}
