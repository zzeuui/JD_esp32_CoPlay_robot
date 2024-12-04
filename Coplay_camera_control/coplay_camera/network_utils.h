#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include "Arduino.h"
#include "WiFi.h"
#include "ArduinoWebsockets.h"
using namespace websockets;

void setupWiFi();

void onMessageControl(WebsocketsMessage message);
void onEventsControl(WebsocketsEvent event, String data);
void onMessageCamera(WebsocketsMessage message);
void onEventsCamera(WebsocketsEvent event, String data);

#endif //NETWORK_UTILS_H