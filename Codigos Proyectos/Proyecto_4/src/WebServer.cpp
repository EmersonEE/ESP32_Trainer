#include "WebServer.h"
#include "WebSocket.h"
#include <ArduinoJson.h>

AsyncWebServer server(80);

String processor(const String& var) {
  if(var == "WEB_SERVER_IP") {
    return WiFi.localIP().toString();
  }
  return String();
}

// Setup WebServer routes
void setupRoutes() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", String(), false, processor);
  });
}

// Initialize LittleFS
void initLittleFS() {
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
}

void setupWebServer() {
  initLittleFS();
  setupRoutes();
  server.serveStatic("/", LittleFS, "/");
  server.begin();
  server.addHandler(&ws);
}
