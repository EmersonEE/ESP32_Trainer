#include <Arduino.h>
#include "LED.h"
#include "PWM.h"
LED ledgpio25(25);
LED ledgpio02(2);
PWM pot1(32);

void setup()
{   
    ledgpio02.init(LED::DEACTIVE);
}

void loop()
{
    // ledgpio02.ledBlink(100);
    ledgpio02.ledPWM(&pot1);
}