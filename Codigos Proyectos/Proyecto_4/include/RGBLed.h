#ifndef RGB_LED_H
#define RGB_LED_H

#include "Arduino.h"

const int LED_R = 1;
const int LED_G = 4;
const int LED_B = 6;

void initRGBLed();

void writeRGBLed(int r, int g, int b);

#endif
