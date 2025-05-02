#include "HC_SR04.h"

/// @brief Constructor de la clase HC_SR04. Inicializa los pines trigger y echo.
/// @param _trigPin El pin digital conectado al pin TRIG del sensor.
/// @param _echoPin El pin digital conectado al pin ECHO del sensor.
HC_SR04::HC_SR04(uint8_t _trigPin, uint8_t _echoPin)
{
    trigPin = _trigPin;
    echoPin = _echoPin;

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    digitalWrite(trigPin, LOW);
    delay(2);
}

/// @brief Realiza una medición de distancia con el sensor HC-SR04.
/// @return La duración del pulso de eco en microsegundos.
float HC_SR04::getDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    return duration = pulseIn(echoPin, HIGH);
}

/// @brief Obtiene la distancia medida por el sensor en milímetros.
/// @return La distancia en milímetros (mm).
float HC_SR04::getDistanceMM()
{
    return getDistanceCM() * 10;
    // 0.034 es la velocidad del sonido en cm/us, y se divide por 2 porque el pulso va y vuelve.
}

/// @brief Obtiene la distancia medida por el sensor en centímetros.
/// @return La distancia en centímetros (cm).
float HC_SR04::getDistanceCM()
{
    return getDistance() * SOUND_SPEED / 2;
}

/// @brief Obtiene la distancia medida por el sensor en metros.
/// @return La distancia en metros (m).
float HC_SR04::getDistanceM()
{
    return getDistanceCM() / 100;
}

/// @brief Obtiene la distancia medida por el sensor en pulgadas.
/// @return La distancia en pulgadas (inch).
float HC_SR04::getDistanceInch()
{
    return getDistanceCM() * CM_TO_INCH;
}