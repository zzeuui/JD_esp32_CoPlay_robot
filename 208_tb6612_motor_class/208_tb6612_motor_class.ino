#include <driver/ledc.h>

class Tb6612_motor{
public:
  Tb6612_motor(int ia_, int ib_, int pwm_){
    ia = ia_;
    ib = ib_;
    pwm = pwm_;
    speed = 0;
  }

  void begin(){
    pinMode(ia, OUTPUT);
    pinMode(ib, OUTPUT);
    pinMode(16, OUTPUT);
    digitalWrite(16, HIGH);
    ledcAttach(pwm, 5000, 8 );
  }

  void move_forward(int speed_){
    speed = speed_;
    if(speed < 0)
      speed = 0;
    if(speed > 255)
      speed = 255;
    digitalWrite(ia, HIGH);
    digitalWrite(ib, LOW);
    ledcWrite(pwm, speed);
  }

  void move_backward(int speed_){
    speed = speed_;
    if(speed < 0)
      speed = 0;
    if(speed > 255)
      speed = 255;
    digitalWrite(ia, LOW);
    digitalWrite(ib, HIGH);
    ledcWrite(pwm, speed);
  }

  void motor_stop(){
    speed = 0;
    digitalWrite(ia, LOW);
    digitalWrite(ib, LOW);
    ledcWrite(pwm, speed);
  }

  int ia;
  int ib;
  int pwm;
  int speed;
};

#define MSLEEP  16
#define IA1     26
#define IB1     27
#define PWM1    25
#define IA2     14
#define IB2     12
#define PWM2    13


Tb6612_motor mt1(IA1, IB1, PWM1);
//Tb6612_motor mt2(IA2, IB2, PWM2);

void setup() {
  mt1.begin();
  //mt2.begin();
  Serial.begin(115200);
}

void loop() {
  mt1.move_forward(1000);
  //mt2.move_forward(1000);
  delay(1000);
  mt1.move_backward(1000);
  //mt2.move_backward(1000);
  delay(1000);

}
