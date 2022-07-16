#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID{
private:
  float kp, ki, kd;
  int prevError;
  double integral;
  unsigned long prevTime;
  int minOutput, maxOutput;
  double input, output, setPoint;
public:
  PID(double &input_, double &output_, double &setPoint_, float kp_, float ki_, float kd_);
  void calibrate();
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

#endif
