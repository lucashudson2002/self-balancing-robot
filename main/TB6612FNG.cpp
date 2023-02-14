#include "TB6612FNG.h"

TB6612FNG::TB6612FNG(byte IN1_left, byte IN2_left, byte IN1_right, byte IN2_right, byte PWM_left, byte PWM_right , byte STBY)
  :in1_left(IN1_left), in2_left(IN2_left), in1_right(IN1_right), in2_right(IN2_right), pwm_left(PWM_left), pwm_right(PWM_right), stby(STBY)
{
  pinMode(in1_left, OUTPUT);
  pinMode(in2_left, OUTPUT);
  pinMode(in1_right, OUTPUT);
  pinMode(in2_right, OUTPUT);
  pinMode(stby, OUTPUT);
  channel_left = 0;
  ledcAttachPin(pwm_left, channel_left);
  ledcSetup(channel_left, 20000, 8);
  channel_right = 1;
  ledcAttachPin(pwm_right, channel_right);
  ledcSetup(channel_right, 20000, 8);
  digitalWrite(stby, HIGH);
  set_pwm(0,0);
  stop();
}

void TB6612FNG::set_pwm(int PWM_left, int PWM_right){
  ledcWrite(channel_left, PWM_left);
  ledcWrite(channel_right, PWM_right);
}

void TB6612FNG::stop(){
  digitalWrite(in1_right, LOW);
  digitalWrite(in2_right, LOW);
  digitalWrite(in1_left, LOW);
  digitalWrite(in2_left, LOW);
}
void TB6612FNG::brake(){
  digitalWrite(in1_right, HIGH);
  digitalWrite(in2_right, HIGH);
  digitalWrite(in1_left, HIGH);
  digitalWrite(in2_left, HIGH);
}
void TB6612FNG::forward(){
  digitalWrite(in1_right, HIGH);
  digitalWrite(in2_right, LOW);
  digitalWrite(in1_left, HIGH);
  digitalWrite(in2_left, LOW);
}
void TB6612FNG::backward(){
  digitalWrite(in1_right, LOW);
  digitalWrite(in2_right, HIGH);
  digitalWrite(in1_left, LOW);
  digitalWrite(in2_left, HIGH);
}
void TB6612FNG::right(){
  digitalWrite(in1_right, LOW);
  digitalWrite(in2_right, HIGH);
  digitalWrite(in1_left, HIGH);
  digitalWrite(in2_left, LOW);
}
void TB6612FNG::left(){
  digitalWrite(in1_right, HIGH);
  digitalWrite(in2_right, LOW);
  digitalWrite(in1_left, LOW);
  digitalWrite(in2_left, HIGH);
}