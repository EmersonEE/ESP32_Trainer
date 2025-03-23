#include <Arduino.h>
#include "PWM.h"

PWM pwm1(26,32);
void setup()
{
  Serial.begin(115200);
  pwm1.init(1, 5000, 8);
}

void loop()
{
  Serial.println(pwm1.readPot());
  pwm1.writePWM(pwm1.readPot());
  Serial.print("Voltaje: ");
  Serial.println(pwm1.showVoltage(pwm1.readPot()));
}