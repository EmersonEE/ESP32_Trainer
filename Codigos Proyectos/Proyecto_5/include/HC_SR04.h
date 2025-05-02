#ifndef __HC_SR04_H__
#define __HC_SR04_H__

#include <Arduino.h>

class HC_SR04
{

public:
    HC_SR04(uint8_t _trigPin, uint8_t _echoPin);
    float getDistanceMM();
    float getDistanceCM();
    float getDistanceM();
    float getDistanceInch();

private:
    float getDistance();
    uint8_t trigPin;
    uint8_t echoPin;
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
    unsigned long duration;
};

#endif // __HC-SR04_H__