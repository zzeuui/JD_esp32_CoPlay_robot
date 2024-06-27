// install TB6612FNG library
//https://github.com/vincasmiliunas/ESP32-Arduino-TB6612FNG

#include <TB6612FNG.h>
#include <ArduinoWebsockets.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

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

Tb6612fng motors1(16, 14, 12, 13, 26, 27, 25);
Tb6612fng motors2(16, 5, 17, 18, 2, 4, 15);
void go_forward(){
  Serial.println("forward");
  motors1.drive(0.5);
  motors2.drive(0.5);
}

void go_backward(){
  Serial.println("backward");
  motors1.drive(-0.5);
  motors2.drive(-0.5);
}

void turn_right(){
  Serial.println("right");
  motors1.drive(0.5);
  motors2.drive(-0.5);
}

void turn_left(){
  Serial.println("left");
  motors1.drive(-0.5);
  motors2.drive(0.5); 
}

void stop(){
  Serial.println("stop");
  motors1.drive(0);
  motors2.drive(0);
  delay(200);
}



void setup() {
  Serial.begin(115200);
  SerialBT.begin("JD 4wheel robot"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  motors1.begin();
  motors2.begin();
}

void loop() {
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.println(c);
    if(c == 'f'){
      SerialBT.println("forward");
      go_forward();
    }else if(c == 'b'){
      SerialBT.println("backward");
      go_backward();
    }else if(c == 'l'){
      SerialBT.println("turn left");
      turn_left();
    }else if(c == 'r'){
      SerialBT.println("turn right");
      turn_right(); 
    }else if(c == 'p'){
      stop();
    }
  }
}
