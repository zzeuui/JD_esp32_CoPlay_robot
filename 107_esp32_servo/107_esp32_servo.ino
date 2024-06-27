#include <ESP32Servo.h>
#include "BluetoothSerial.h"

#define SERVO1  26
#define SERVO2  27

Servo myservo1, myservo2, myservo3, myservo4;
BluetoothSerial SerialBT;

void servo_center(){
  myservo1.write(90);
  myservo2.write(90);
  Serial.println("Servo control with Blutooth...");
}

void setup() {
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  myservo1.setPeriodHertz(50);    // standard 50 hz servo
  myservo1.attach(SERVO1, 500, 2400);
  myservo2.setPeriodHertz(50); 
  myservo2.attach(SERVO2, 500, 2400);
}

int angle1 = 90;
int angle2 = 90;

void loop() {
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.println(c);
    if(c == 'a'){
      angle1++;
      if(angle1 > 180)
        angle1 = 180;
      myservo1.write(angle1);
    }else if(c == 'd'){
      angle1 --;
      if(angle1 < 0)
        angle1 = 0;
      myservo1.write(angle1);
    }
      
    if(c == 'w'){
      angle2++;
      if(angle2 > 180)
        angle2 = 180;
      myservo2.write(angle2);
    }else if(c == 's'){
      angle2 --;
      if(angle2 < 0)
        angle2 = 0;
      myservo2.write(angle2);
    }
  }

}
