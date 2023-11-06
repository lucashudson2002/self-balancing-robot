#include "pid.h"

PID::PID(double* Input, double* Output, double* Setpoint)
{
    this->Input = Input;
    this->Output = Output;
    this->Setpoint = Setpoint;
    PID::setOutputLimits(-255, 255);

    integral = 0;
    prevError = 0;
    prevTime = millis();
}

void PID::setOutputLimits(double outMin, double outMax) {
    if (outMin < outMax) {
        this->outMin = outMin;
        this->outMax = outMax;
    }
}

void PID::setTunings(double kp, double ki, double kd){
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;

}

void PID::compute(){
    unsigned long time = millis();
    unsigned long dt = time - prevTime;

    double error = *Setpoint - *Input;
    double dError = error - prevError;
    integral += ki * error;

    double output = kp * error + integral * dt - kd * dError / dt;

    if(output > outMax) output = outMax;
    else if(output < outMin) output = outMin;

    *Output = output;

    prevTime = time;
    prevError = error;
}