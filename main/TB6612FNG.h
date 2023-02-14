#ifndef TB6612FNG_H
#define TB6612FNG_H

#include <Arduino.h>

class TB6612FNG{
private:
  byte in1_left, in1_right, in2_left, in2_right;
  byte pwm_left, pwm_right, stby;
  byte channel_left, channel_right;
public:
  TB6612FNG(byte IN1_left, byte IN2_left, byte IN1_right, byte IN2_right, byte PWM_left, byte PWM_right , byte STBY);
  void set_pwm(int PWM_left, int PWM_right);
  void stop();
  void brake();
  void forward();
  void backward();
  void right();
  void left();
};

#endif
