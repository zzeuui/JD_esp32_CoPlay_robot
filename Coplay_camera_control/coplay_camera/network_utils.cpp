#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>
using namespace websockets;
#include <esp_camera.h>

#include "network_utils.h"

#define WIFI_SSID  "HCIR2G"
#define WIFI_PASSWD "I222HCIRLAB"

#define CONNECTED_CONTROL   23

String macAddress = "";
String ipAddress = "";

void setupWiFi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  ipAddress = WiFi.localIP().toString();
  macAddress += WiFi.macAddress().substring(0, 5);  
}

void onMessageControl(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    if (message.isText())
    {
        const char *command = message.c_str();
        Serial.println(command);
    }
}

void onEventsControl(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
        digitalWrite(CONNECTED_CONTROL, HIGH);
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        digitalWrite(CONNECTED_CONTROL, LOW);
        Serial.println("Connnection Closed... Rebooting");
        ESP.restart();
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}

void onMessageCamera(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());
}

void onEventsCamera(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed... Rebooting");
        ESP.restart();
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}
