#include <driver/ledc.h>

#define DEFAULT_LEDC_FREQ 20000
#define DEFAULT_LEDC_RANGE LEDC_TIMER_10_BIT

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
    ledcSetup(LEDC_CHANNEL_0, DEFAULT_LEDC_FREQ, LEDC_TIMER_10_BIT);
    ledcAttachPin(pwm, LEDC_CHANNEL_0 );
  }

  void move_forward(int speed_){
    speed = speed_;
    if(speed < 0)
      speed = 0;
    if(speed > 1024)
      speed = 1024;
    digitalWrite(ia, HIGH);
    digitalWrite(ib, LOW);
    ledcWrite(LEDC_CHANNEL_0, speed);
  }

  void move_backward(int speed_){
    speed = speed_;
    if(speed < 0)
      speed = 0;
    if(speed > 1024)
      speed = 1024;
    digitalWrite(ia, LOW);
    digitalWrite(ib, HIGH);
    ledcWrite(LEDC_CHANNEL_0, speed);
  }

  void motor_stop(){
    speed = 0;
    digitalWrite(ia, LOW);
    digitalWrite(ib, LOW);
    ledcWrite(LEDC_CHANNEL_0, speed);
  }

  int ia;
  int ib;
  int pwm;
  int speed;
};

#define MSLEEP  16
//#define IA1     14
//#define IB1     12
//#define PWM1    13
#define IA2     27
#define IB2     26
#define PWM2    25
#define IA3     17
#define IB3     5
#define PWM3    18
#define IA4     4
#define IB4     2
#define PWM4    15

int IA1 = 14;
int IB1 = 12;
int PWM1 = 13; 

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
