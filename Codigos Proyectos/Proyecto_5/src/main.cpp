#include <Arduino.h>
#include "HC_SR04.h"
#include "PantallitaXD.h"
HC_SR04 sensor1(4, 18);

int distancia_sensada = 3; //CM
PantallitaXD pantalla1;
void setup()
{
  Serial.begin(115200);
  pantalla1.init();
  pinMode(2, OUTPUT);

}

void loop()
{
  // Serial.print("Distancia en Cm: ");
  // Serial.println(sensor1.getDistanceCM());
  // Serial.print("Distancia en Inch: ");
  // Serial.println(sensor1.getDistanceInch());
  // Serial.print("Distancia en M: ");
  // Serial.println(sensor1.getDistanceM());
  // Serial.print("Distancia en MM: ");
  // Serial.println(sensor1.getDistanceMM());
  // Serial.println("-------------------------------------------------");
  pantalla1.printHC_SR04(sensor1.getDistanceMM(), sensor1.getDistanceCM(), sensor1.getDistanceM(), sensor1.getDistanceInch());

  if(sensor1.getDistanceCM() < distancia_sensada)
  {
    Serial.println("El objeto está muy cerca");
    digitalWrite(2, HIGH);
  }
  else
  {
    Serial.println("El objeto está lejos");
    digitalWrite(2, LOW);
  }
  delay(500);
}