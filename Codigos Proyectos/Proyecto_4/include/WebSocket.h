#include <ArduinoJson.h>
#include "RGBLed.h"
#include "WebServer.h"

extern AsyncWebSocket ws;

void notifyClients();

void handleCommand(DynamicJsonDocument json);

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

void onSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,AwsEventType type,
             void *arg, uint8_t *data, size_t len);

void initWebSocket();
