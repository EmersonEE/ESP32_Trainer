#ifndef WIFICONTROLLER_H
#define WIFICONTROLLER_H

#include <WiFi.h>
// #include <esp_wifi.h>

#define WIFI_SSID     "Proximus-Home-024432"
#define WIFI_PASSWORD "d6cfnsjuzpmwne6n"

// Init WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
  }
  Serial.println(WiFi.localIP());
}

#endif
