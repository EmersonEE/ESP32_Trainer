#ifndef __LED_H__
#define __LED_H__
#include <Arduino.h>
#include "PWM.h"
class LED
{

public:
enum LED_USE{
    ACTIVE = true,
    DEACTIVE = false
};
    LED(uint8_t _pinLED);
    void ledON();
    void init(bool selPWM = LED_USE::ACTIVE, uint8_t channel = 0, uint32_t frequency = 5000, uint8_t resolution = 8);
    void ledOFF();
    void ledBlink(unsigned long time);
    void ledPWM(PWM *pwmvalue);

private:
    uint8_t pinLED;
    uint8_t ledChannel =0;
    // uint8_t *pwmValue;
};

#endif // __LED_H__