#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "LittleFS.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

String processor(const String& var);

// Setup WebServer routes
void setupRoutes();

// Initialize LittleFS
void initLittleFS();

void setupWebServer();

#endif
