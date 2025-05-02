#ifndef __PANTALLITAXD_H__
#define __PANTALLITAXD_H__

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class PantallitaXD
{
    
    public:
    PantallitaXD();
    // ~PantallitaXD();
    void init();
    void printHC_SR04(float distanciamm, float distanciaCM, float distanciaM, float distanciaInch);
    private:
    #define SCREEN_WIDTH 128
    #define SCREEN_HEIGHT 64
    #define OLED_RESET -1
    // Adafruit_SSD1306 _display(SCREEN_WIDTH, SCREEN_HEIGHT &Wire, OLED_RESET);
    Adafruit_SSD1306 _display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
};



#endif // __PANTALLITAXD_H__