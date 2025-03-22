#ifndef LED_H
#define LED_H

#include <Arduino.h>
class LEDS
{
public:
    LEDS(uint8_t _pinLed1, uint8_t _pinLed2, uint8_t _pinLed3, uint8_t _pinLed4);
    void init();
    void SecuenciaUno();
    void SecuenciaDos();
    void SecuenciaTres();
    void SecuenciaCuatro();
    void SecuenciaCinco();
    void OnLed(uint8_t pinLed);
    void OffLed(uint8_t pinLed);
    void OnAll();
    void OffAll();

private:
    uint8_t pinLed1;
    uint8_t pinLed2;
    uint8_t pinLed3;
    uint8_t pinLed4;
};

#endif