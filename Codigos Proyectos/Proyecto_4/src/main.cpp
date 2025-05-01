#include <Arduino.h>
#include "WiFiController.h"
#include "RGBLed.h"
#include "WebSocket.h"
#include "WebServer.h"

void setup() {
    Serial.begin(115200);
    delay(10);

    initRGBLed(); // RGBLed.h
    initWiFi(); // WiFi.h
    initWebSocket(); // WebSocket.h
    setupWebServer(); // WebServer.h
}

void loop() {
  ws.cleanupClients();
}