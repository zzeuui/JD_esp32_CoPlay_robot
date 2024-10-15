#include "Wire.h"
#include "BluetoothSerial.h"
#include <SPI.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

#define MSLEEP  16
#define IA1     14
#define IB1     12
#define PWM1    13
#define IA2     27
#define IB2     26
#define PWM2    25
#define IA3     17
#define IB3     5
#define PWM3    18
#define IA4     4
#define IB4     2
#define PWM4    15
#define CONNECTED   23

//#define WIFI_SSID  "SK_WiFiGIGA73BA_2.4G"
//#define WIFI_PASSWD "1609043407"


#define WIFI_SSID  "ConnectValue_A403_2G"
#define WIFI_PASSWD "CVA403!@#$"

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
    motor1_move_forward(255);
    motor2_move_forward(255);
    motor3_move_forward(255);
    motor4_move_forward(255);
   
}

void go_backward(){
    Serial.println("backward");
    motor1_move_backward(255);
    motor2_move_backward(255);
    motor3_move_backward(255);
    motor4_move_backward(255);
}

void turn_right(){
    Serial.println("right");
    motor1_move_forward(255);
    motor2_move_forward(255);
    motor3_move_backward(255);
    motor4_move_backward(255);
}

void turn_left(){
    Serial.println("left");
    motor1_move_backward(255);
    motor2_move_backward(255);
    motor3_move_forward(255);
    motor4_move_forward(255);
}

void stop(){
    Serial.println("stop");
     motor1_stop();
     motor2_stop();
      motor3_stop();
     motor4_stop();
    delay(200);
}

void motor_enable(int m_sleep){
  pinMode(m_sleep, OUTPUT);
  digitalWrite(m_sleep, HIGH);
}

void motor1_begin(int ia1, int ib1, int pwm1){
  pinMode(ia1, OUTPUT);
  pinMode(ib1, OUTPUT);
  //ledcSetup(LEDC_CHANNEL_0, DEFAULT_LEDC_FREQ, LEDC_TIMER_10_BIT);
  ledcAttach(pwm1, 5000, 8 );
}

void motor2_begin(int ia2, int ib2, int pwm2 ){
  pinMode(ia2, OUTPUT);
  pinMode(ib2, OUTPUT);
  //ledcSetup(LEDC_CHANNEL_0, DEFAULT_LEDC_FREQ, DEFAULT_LEDC_RANGE);
  ledcAttach(pwm2, 5000, 8);
}

void motor3_begin(int ia3, int ib3, int pwm3){
  pinMode(ia3, OUTPUT);
  pinMode(ib3, OUTPUT);
  //ledcSetup(LEDC_CHANNEL_0, DEFAULT_LEDC_FREQ, LEDC_TIMER_10_BIT);
  ledcAttach(pwm3, 5000, 8 );
}

void motor4_begin(int ia4, int ib4, int pwm4 ){
  pinMode(ia4, OUTPUT);
  pinMode(ib4, OUTPUT);
  //ledcSetup(LEDC_CHANNEL_0, DEFAULT_LEDC_FREQ, DEFAULT_LEDC_RANGE);
  ledcAttach(pwm4, 5000, 8);
}

void motor1_move_forward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA1, LOW);
  digitalWrite(IB1, HIGH);
  ledcWrite(PWM1, speed);
}

void motor2_move_forward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA2, HIGH);
  digitalWrite(IB2, LOW);
  ledcWrite(PWM2, speed);
}

void motor3_move_forward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA3, HIGH);
  digitalWrite(IB3, LOW);
  ledcWrite(PWM3, speed);
}

void motor4_move_forward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA4, LOW);
  digitalWrite(IB4, HIGH);
  ledcWrite(PWM4, speed);
}

void motor1_move_backward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA1, HIGH);
  digitalWrite(IB1, LOW);
  ledcWrite(PWM1, speed);
}

void motor2_move_backward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA2, LOW);
  digitalWrite(IB2, HIGH);
  ledcWrite(PWM2, speed);
}

void motor3_move_backward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA3, LOW);
  digitalWrite(IB3, HIGH);
  ledcWrite(PWM3, speed);
}

void motor4_move_backward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA4, HIGH);
  digitalWrite(IB4, LOW);
  ledcWrite(PWM4, speed);
}


void motor1_stop(){
  digitalWrite(IA1, LOW);
  digitalWrite(IB1, LOW);
  ledcWrite(PWM1, 0);
}

void motor2_stop(){
  digitalWrite(IA2, LOW);
  digitalWrite(IB2, LOW);
  ledcWrite(PWM2, 0);
}

void motor3_stop(){
  digitalWrite(IA3, LOW);
  digitalWrite(IB3, LOW);
  ledcWrite(PWM3, 0);
}

void motor4_stop(){
  digitalWrite(IA4, LOW);
  digitalWrite(IB4, LOW);
  ledcWrite(PWM4, 0);
}


void setup() {
    Serial.begin(115200);
    Serial.print("ACT ground robot Start...");

    motor1_begin(IA1, IB1, PWM1);
    motor2_begin(IA2, IB2, PWM2);
    motor3_begin(IA3, IB3, PWM3);
    motor4_begin(IA4, IB4, PWM4);
    motor_enable(MSLEEP);

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
    // 2024/09/25 test0 bq5ame6g10l3jia3h0ng
    while (!client.connect(websockets_server_host, websockets_server_port, "/pang/ws/pub?channel=bq5ame6g10l3jia3h0ng&track=colink&mode=bundle"))
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
