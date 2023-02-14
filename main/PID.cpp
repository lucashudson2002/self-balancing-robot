#include "PID.h"

PID::PID(float kp_, float ki_, float kd_)
  :kp(kp_), ki(ki_), kd(kd_){
  minOutput = -255;
  maxOutput = 255;
  integral = prevError = 0;
  prevTime = millis();
}

void PID::calibrate(float input, float &output, float setPoint){
  unsigned long now = millis();
  unsigned long deltaTime = (now - prevTime);
  
  float error = setPoint - input;
  integral += error * deltaTime;
  float derivative = (error - prevError) / deltaTime;

  prevError = error;
  prevTime = now;
  
  output = kp*error + ki*integral + kd*derivative;
  if (output < minOutput) output = minOutput;
  else if (output > maxOutput) output = maxOutput;
}