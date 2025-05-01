#include "WebSocket.h"

AsyncWebSocket ws("/ws");

void notifyClients(int r, int g, int b) {
    const uint8_t size = JSON_OBJECT_SIZE(8);
    StaticJsonDocument<size> json;
    json["status"] = "ok";
    json["r"] = r;
    json["g"] = g;
    json["b"] = b;

    char data[400];
    size_t len = serializeJson(json, data);
    ws.textAll(data, len);
}

void handleCommand(DynamicJsonDocument json) {
  const char* action = json["action"];
  Serial.println(action);

  if ((strcmp(action, "change") == 0)) {
    const int r = json["data"]["r"];
    const int g = json["data"]["g"];
    const int b = json["data"]["b"];
    writeRGBLed(r, g, b);
    notifyClients(r, g, b);
  } else if ((strcmp(action, "init") == 0)) {
    notifyClients(0, 0, 0);
  }
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    
    DynamicJsonDocument json(2048);
    DeserializationError err = deserializeJson(json, data);
    if (err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
      return;
    }

    handleCommand(json);
  }
}

void onSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
    ws.onEvent(onSocketEvent);
    Serial.println("Websocket started");
}
