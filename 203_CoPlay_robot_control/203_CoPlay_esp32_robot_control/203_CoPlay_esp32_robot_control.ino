#include "Wire.h"
#include "BluetoothSerial.h"
#include <SPI.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

#define M1_B    26
#define M1_A    27
#define M2_B    12
#define M2_A    14
#define M3_B    15
#define M3_A    2
#define M4_B    4
#define M4_A    16

#define CONNECTED   23

#define WIFI_SSID  "SK_WiFiGIGA73BA_2.4G"
#define WIFI_PASSWD "1609043407"

String macAddress = "";
String ipAddress = "";

const char *websockets_server_host = "cobot.center";
const uint16_t websockets_server_port = 8286;
//const char *websockets_server_host = "192.168.0.77";
//const uint16_t websockets_server_port = 8276;
using namespace websockets;
WebsocketsClient client;

int beat_count = 0;

bool isTurnOver = true;
void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    if (message.isText())
    {
        const char *command = message.c_str();
        Serial.println(command);
    }
     
    if (message.isText())
    {
        const char *command = message.c_str();
        //Serial.println(command);
        if (strcmp(command, "AU") == 0){
            go_forward();
        }
        if (strcmp(command, "AD") == 0){
            go_backward();
        }
        if (strncmp(command, "AL", 2) == 0){
            turn_left();
        }
        if (strncmp(command, "AR", 2) == 0){
            turn_right();
        }
        if (strcmp(command, "STOP") == 0){
            stop();
        }
    }
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
        digitalWrite(CONNECTED, HIGH);
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        digitalWrite(CONNECTED, LOW);
        delay(100);
        Serial.println("Connnection Closed... Rebooting");
        ESP.restart();
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}

void go_forward(){
    Serial.println("forward");
    digitalWrite(M1_A, LOW);
    digitalWrite(M1_B, HIGH);
    digitalWrite(M2_A, LOW);
    digitalWrite(M2_B, HIGH);

    digitalWrite(M3_A, HIGH);
    digitalWrite(M3_B, LOW);
    digitalWrite(M4_A, HIGH);
    digitalWrite(M4_B, LOW);
   
}

void go_backward(){
    Serial.println("backward");
    digitalWrite(M1_A, HIGH);
    digitalWrite(M1_B, LOW);
    digitalWrite(M2_A, HIGH);
    digitalWrite(M2_B, LOW);

    digitalWrite(M3_A, LOW);
    digitalWrite(M3_B, HIGH);
    digitalWrite(M4_A, LOW);
    digitalWrite(M4_B, HIGH);
}

void turn_right(){
    Serial.println("right");
    digitalWrite(M1_A, LOW);
    digitalWrite(M1_B, HIGH);
    digitalWrite(M2_A, LOW);
    digitalWrite(M2_B, HIGH);

    digitalWrite(M3_A, LOW);
    digitalWrite(M3_B, HIGH);
    digitalWrite(M4_A, LOW);
    digitalWrite(M4_B, HIGH);
}

void turn_left(){
    Serial.println("left");
    digitalWrite(M1_A, HIGH);
    digitalWrite(M1_B, LOW);
    digitalWrite(M2_A, HIGH);
    digitalWrite(M2_B, LOW);

    digitalWrite(M3_A, HIGH);
    digitalWrite(M3_B, LOW);
    digitalWrite(M4_A, HIGH);
    digitalWrite(M4_B, LOW);
}

void stop(){
    Serial.println("stop");
    digitalWrite(M1_A, LOW);
    digitalWrite(M1_B, LOW);
    digitalWrite(M2_A, LOW);
    digitalWrite(M2_B, LOW);
    
    digitalWrite(M3_A, LOW);
    digitalWrite(M3_B, LOW);
    digitalWrite(M4_A, LOW);
    digitalWrite(M4_B, LOW);
    delay(200);
}


void setup() {
    Serial.begin(115200);
    Serial.print("ACT ground robot Start...");

    pinMode(M1_A, OUTPUT);
    pinMode(M1_B, OUTPUT);
    pinMode(M2_A, OUTPUT);
    pinMode(M2_B, OUTPUT);
    pinMode(M3_A, OUTPUT);
    pinMode(M3_B, OUTPUT);
    pinMode(M4_A, OUTPUT);
    pinMode(M4_B, OUTPUT);

    pinMode(CONNECTED, OUTPUT);

    // wait until serial port opens for native USB devices
    while (! Serial) {
        delay(1);
    }

    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi Connected.");

    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);
    // c3rl3c86n88jq9lrl3gg MarsRover-1
    while (!client.connect(websockets_server_host, websockets_server_port, "/pang/ws/pub?channel=c3rl3c86n88jq9lrl3gg&track=colink&mode=bundle"))
    {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("Websocket Connected.");
    Wire.begin();
    delay(500);

}


void loop() {
    if(Serial.available() > 0){
        char c = Serial.read();
        Serial.println(c);
        if(c == 'f'){    
            go_forward();
        }else if(c == 'b'){
            go_backward();
        }else if(c == 'l'){
            turn_left();
        }else if(c == 'r'){
            turn_right(); 
        }else if(c == 'p'){
            stop();
        }
    }
    client.poll();
    beat_count++;
    if(beat_count > 500){
        client.send("beat");
        beat_count = 0;
    }
}
