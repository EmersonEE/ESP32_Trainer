#include "PantallitaXD.h"

/// @brief Constructor de la clase PantallitaXD. Inicializa la pantalla OLED.
/// @param _display La instancia de la pantalla OLED.
// PantallitaXD::PantallitaXD() : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}
PantallitaXD::PantallitaXD()
{
    // Constructor vacío
}
/// @brief Inicializa la pantalla OLED.
/// @param _display La instancia de la pantalla OLED.
void PantallitaXD::init()
{
    _display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(WHITE);
    _display.setCursor(0, 0);
    _display.display();
}
/// @brief Imprime las distancias medidas por el sensor HC-SR04 en la pantalla OLED.
/// @param distanciamm Distancia medida en milímetros.
/// @param distanciaCM Distancia medida en centímetros.
/// @param distanciaM Distancia medida en metros.
/// @param distanciaInch Distancia medida en pulgadas.
void PantallitaXD::printHC_SR04(float distanciamm, float distanciaCM, float distanciaM, float distanciaInch)
{
    _display.clearDisplay();

    _display.setCursor(0, 0);
    _display.print("mm: ");
    _display.println(distanciamm, 1); // 1 decimal para claridad

    _display.setCursor(0, 16);
    _display.print("cm: ");
    _display.println(distanciaCM, 2); // 2 decimales para cm

    _display.setCursor(0, 32);
    _display.print("m: ");
    _display.println(distanciaM, 3); // más precisión para metros

    _display.setCursor(0, 48);
    _display.print("inch: ");
    _display.println(distanciaInch, 2); // pulgadas con 2 decimales

    _display.display();
}
