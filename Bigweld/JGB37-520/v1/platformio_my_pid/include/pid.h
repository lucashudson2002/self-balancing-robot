#pragma once
#include <Arduino.h>

class PID{
public:
    PID(double *Input, double *Output, double *Setpoint);
    void compute();
    void setOutputLimits(double outMin, double outMax);
    void setTunings(double kp, double ki, double kd);
private:
    double *Input, *Output, *Setpoint;
    double kp, ki, kd;
    unsigned long prevTime;
    double prevError, integral;
    double outMin, outMax;
};