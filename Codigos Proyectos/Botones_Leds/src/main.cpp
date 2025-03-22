#include <Arduino.h>
#include "Botones.h"
#include "LEDS.h"
#include "DEF.h"

BOTONES botones(BOTON1, BOTON2);

LEDS Leds(LED1, LED2, LED3, LED4);
int conteo = 0;
void setup()
{
  botones.init();
  Leds.init();
  Serial.begin(115200);
}

void loop()
{

  if (botones.readButtonB1())
  {
    Serial.println("Boton 1 Presionado");
    conteo = conteo +1;
    Leds.OnLed(LED2);
    Leds.OffLed(LED3);
    Serial.println(conteo);
  }
  else if (botones.readButtonB2())
  {
    Serial.println("Boton 2 Presionado");
    Leds.OnLed(LED3);
    Leds.OffLed(LED2);
  }
  else
  {
    // Serial.println("Ningun Boton Presionado");
  }
}