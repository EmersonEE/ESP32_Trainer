#include <LED.h>

/**************************************************************************/
/*!
    @file     LED.h
    @brief    Definición de la clase LED.
    @details  Esta clase permite controlar pines LED en una tarjeta de desarrollo.
              Incluye funciones para encender, apagar, parpadear y controlar
              la intensidad por PWM.
*/
/**************************************************************************/

/**************************************************************************/
/*!
    @brief    Constructor de la clase LED.
    @param    _pinLED    Pin GPIO asociado al LED (GPIO2, GPIO25, GPIO26, GPIO27).
*/
/**************************************************************************/
LED::LED(uint8_t _pinLED)
{
    pinLED = _pinLED;
}

/**************************************************************************/
/*!
    @brief    Inicializa el LED en modo digital o PWM.
    @param    selPWM      Modo de uso del LED. Si es `ACTIVE`, se configura como salida digital.
                          Si es `DEACTIVE`, se configura con salida PWM.
    @param    channel     Canal PWM a utilizar (solo si se usa modo PWM) Por defecto esta el valor de 0.
    @param    frequency   Frecuencia del PWM en Hz (solo si se usa modo PWM) Por defecto esta el valor de 5000.
    @param    resolution  Resolución del PWM en bits (8 para rango 0-255) Por defecto esta el valor de 8.
*/
/**************************************************************************/
void LED::init(bool selPWM, uint8_t channel, uint32_t frequency, uint8_t resolution)
{
    if (selPWM == true)
    {
        pinMode(pinLED, OUTPUT);
    }
    else
    {

        ledChannel = channel;
        ledcSetup(ledChannel, frequency, resolution);
        ledcAttachPin(pinLED, ledChannel);
    }
}

/**************************************************************************/
/*!
    @brief    Enciende el LED (salida digital en alto).
*/
/**************************************************************************/
void LED::ledON()
{
    digitalWrite(pinLED, HIGH);
}

/**************************************************************************/
/*!
    @brief    Apaga el LED (salida digital en bajo).
*/
/**************************************************************************/
void LED::ledOFF()
{
    digitalWrite(pinLED, LOW);
}

/**************************************************************************/
/*!
    @brief    Hace parpadear el LED con un retardo especificado.
    @param    time    Tiempo en milisegundos entre encendido y apagado.
*/
/**************************************************************************/
void LED::ledBlink(unsigned long time)
{
    ledON();
    delay(time);
    ledOFF();
    delay(time);
}

/**************************************************************************/
/*!
    @brief    Controla la intensidad del LED mediante PWM.
    @param    pwmValue   Valor de intensidad PWM (0 a 255, dependiendo de la resolución).
*/
/**************************************************************************/
void LED::ledPWM(PWM *pwmValue)
{
    uint8_t value = pwmValue->readMapped();
    ledcWrite(ledChannel, value);
}
