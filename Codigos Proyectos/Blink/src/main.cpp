#include <Arduino.h>
#include "LEDS.h"
#include "DEF.h"
LEDS leds(LED1, LED2, LED3, LED4);
void setup()
{
  leds.init();
}

void loop()
{
  for (int i = 0; i < 5; i++)
  {
    leds.SecuenciaCinco();
    delay(100);
  }
}