#include "PID.h"

PID::PID(double &input_, double &output_, double &setPoint_, float kp_, float ki_, float kd_)
  :input(input_), output(output_), setPoint(setPoint_), kp(kp_), ki(ki_), kd(kd_){
  minOutput = -255;
  maxOutput = 255;
  prevTime = millis();
  integral = prevError = 0;
}

void PID::calibrate(){
  unsigned long now = millis();
  unsigned long deltaTime = (now - prevTime);
  
  double error = setPoint - input;
  integral += error * deltaTime;
  double derivative = (error - prevError) / deltaTime;
  
  prevError = error;
  prevTime = now;
  
  output = kp*error + ki*integral + kd*derivative;
  if (output < minOutput) output = minOutput;
  else if (output > maxOutput) output = maxOutput;
}
