// install TB6612FNG library
//https://github.com/vincasmiliunas/ESP32-Arduino-TB6612FNG

#include <TB6612FNG.h>

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
Tb6612fng motors2(16, 5, 17, 18, 4, 2, 15);
void go_forward(){
  Serial.println("forward");
  motors1.drive(1);
  motors2.drive(1);
}

void go_backward(){
  Serial.println("backward");
  motors1.drive(-1);
  motors2.drive(-1);
}

void turn_right(){
  Serial.println("right");
  motors1.drive(1);
  motors2.drive(-1);
}

void turn_left(){
  Serial.println("left");
  motors1.drive(-1);
  motors2.drive(1); 
}

void stop(){
  Serial.println("stop");
  motors1.drive(0);
  motors2.drive(0);
  delay(200);
}

void setup() {
  Serial.begin(115200);
  Serial.print("motor test start...");

  motors1.begin();
  motors2.begin();

}

void loop() {
    go_forward();
    delay(1000);
    go_backward();
    delay(1000);
    turn_left();
    delay(1000);
    turn_right();
    delay(1000);
}
