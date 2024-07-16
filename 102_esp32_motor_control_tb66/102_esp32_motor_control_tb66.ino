#include <driver/ledc.h>
// This code run on TB66112FNG jd esp32 motor controller 

#define MSLEEP  16
#define IA1     26
#define IB1     27
#define PWM1    25
#define IA2     14
#define IB2     12
#define PWM2    13


//#define DEFAULT_LEDC_FREQ 20000
//#define DEFAULT_LEDC_RANGE LEDC_TIMER_10_BIT

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


void motor_enable(int m_sleep){
  pinMode(m_sleep, OUTPUT);
  digitalWrite(m_sleep, HIGH);
}

void motor1_move_forward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA1, HIGH);
  digitalWrite(IB1, LOW);
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

void motor1_move_backward(int speed){
  if(speed < 0)
    speed = 0;
  if(speed > 255)
    speed = 255;
  digitalWrite(IA1, LOW);
  digitalWrite(IB1, HIGH);
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

void setup() {
  Serial.begin(115200);
  motor1_begin(IA1, IB1, PWM1);
  motor2_begin(IA2, IB2, PWM2);
  //motor3_setup(IA1, IB1, PWM3);
  //motor4_setup(IA1, IB1, PWM4);
  motor_enable(MSLEEP);
  delay(1000);
  Serial.println("started...");
}

void loop() {
  motor1_move_forward(170);
  motor2_move_forward(170);
  delay(1000);
  motor1_stop();
  motor2_stop();
  delay(1000);
  motor1_move_backward(170);
  motor2_move_backward(170);
  delay(1000);
}