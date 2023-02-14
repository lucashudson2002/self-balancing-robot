#pragma once

#include <Arduino.h>

class PID{
private:
  float kp, ki, kd;
  float prevError;
  float integral;
  unsigned long prevTime;
  int minOutput, maxOutput;
public:
  PID(float kp_, float ki_, float kd_);
  void calibrate(float input, float &output, float setPoint);
  void set_kp(float kp_){
    kp = kp_;
  }
  void set_ki(float ki_){
    ki = ki_;
  }
  void set_kd(float kd_){
    kd = kd_;
  }
};
