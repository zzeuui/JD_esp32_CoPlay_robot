#include <ArduinoWebsockets.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define M1_B    26
#define M1_A    27
#define M2_B    12
#define M2_A    14
#define M3_B    15
#define M3_A    2
#define M4_B    4
#define M4_A    16

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
  SerialBT.begin("JD 4wheel robot"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M2_A, OUTPUT);
  pinMode(M2_B, OUTPUT);
  pinMode(M3_A, OUTPUT);
  pinMode(M3_B, OUTPUT);
  pinMode(M4_A, OUTPUT);
  pinMode(M4_B, OUTPUT);
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
