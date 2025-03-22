#include "LEDS.h"

LEDS::LEDS(uint8_t _pinLed1, uint8_t _pinLed2, uint8_t _pinLed3, uint8_t _pinLed4)
{
    pinLed1 = _pinLed1;
    pinLed2 = _pinLed2;
    pinLed3 = _pinLed3;
    pinLed4 = _pinLed4;
}

void LEDS::init()
{
    pinMode(pinLed1, OUTPUT);
    pinMode(pinLed2, OUTPUT);
    pinMode(pinLed3, OUTPUT);
    pinMode(pinLed4, OUTPUT);
    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, LOW);
    digitalWrite(pinLed3, LOW);
    digitalWrite(pinLed4, LOW);
}

void LEDS::SecuenciaUno()
{

    digitalWrite(pinLed1, HIGH);
    digitalWrite(pinLed2, HIGH);
    digitalWrite(pinLed3, HIGH);
    digitalWrite(pinLed4, HIGH);
    delay(1000);
    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, LOW);
    digitalWrite(pinLed3, LOW);
    digitalWrite(pinLed4, LOW);
    delay(1000);
}

void LEDS::SecuenciaDos()
{
    digitalWrite(pinLed1, HIGH);
    delay(500);
    digitalWrite(pinLed2, HIGH);
    delay(500);
    digitalWrite(pinLed3, HIGH);
    delay(500);
    digitalWrite(pinLed4, HIGH);
    delay(500);

    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, LOW);
    digitalWrite(pinLed3, LOW);
    digitalWrite(pinLed4, LOW);
    delay(1000);
}

void LEDS::SecuenciaTres()
{
    digitalWrite(pinLed1, HIGH);
    digitalWrite(pinLed3, HIGH);
    delay(500);
    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed3, LOW);

    digitalWrite(pinLed2, HIGH);
    digitalWrite(pinLed4, HIGH);
    delay(500);
    digitalWrite(pinLed2, LOW);
    digitalWrite(pinLed4, LOW);
    delay(1000);
}

void LEDS::SecuenciaCuatro()
{
    digitalWrite(pinLed4, HIGH);
    delay(500);
    digitalWrite(pinLed3, HIGH);
    delay(500);
    digitalWrite(pinLed2, HIGH);
    delay(500);
    digitalWrite(pinLed1, HIGH);
    delay(500);

    digitalWrite(pinLed4, LOW);
    digitalWrite(pinLed3, LOW);
    digitalWrite(pinLed2, LOW);
    digitalWrite(pinLed1, LOW);
    delay(1000);
}

void LEDS::SecuenciaCinco()
{
    digitalWrite(pinLed1, HIGH);
    delay(300);
    digitalWrite(pinLed2, HIGH);
    delay(300);
    digitalWrite(pinLed3, HIGH);
    delay(300);
    digitalWrite(pinLed4, HIGH);
    delay(300);

    digitalWrite(pinLed3, LOW);
    delay(300);
    digitalWrite(pinLed2, LOW);
    delay(300);
    digitalWrite(pinLed1, LOW);
    delay(300);

    digitalWrite(pinLed2, HIGH);
    delay(300);
    digitalWrite(pinLed3, HIGH);
    delay(300);
    digitalWrite(pinLed4, LOW);
    delay(300);

    digitalWrite(pinLed3, LOW);
    delay(300);
    digitalWrite(pinLed2, LOW);
    delay(300);
    digitalWrite(pinLed1, LOW);
    delay(1000);
}

void LEDS::OnAll()
{
    digitalWrite(pinLed1, HIGH);
    digitalWrite(pinLed2, HIGH);
    digitalWrite(pinLed3, HIGH);
    digitalWrite(pinLed4, HIGH);
}

void LEDS::OffAll()
{
    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, LOW);
    digitalWrite(pinLed3, LOW);
    digitalWrite(pinLed4, LOW);
}

void LEDS::OnLed(uint8_t pinLed)
{
    digitalWrite(pinLed, HIGH);
}

void LEDS::OffLed(uint8_t pinLed)
{
    digitalWrite(pinLed, LOW);
}
