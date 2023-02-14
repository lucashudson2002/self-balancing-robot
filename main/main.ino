#include <Kalman.h>
#include "i2cMPU6050.h"
#include "TB6612FNG.h"
#include <PID_v1.h>

#define STBY 27
#define IN1A 26
#define IN2A 25
#define PWMA 33
#define IN1B 14
#define IN2B 12
#define PWMB 13

TB6612FNG VSSS(IN1A, IN2A, IN2B, IN1B, PWMA, PWMB, STBY);

double Setpoint=2, Input=0, Output=0;
float kp=8.1, ki=0, kd=0;

PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

Point3lf acc, gyro;
Kalman KalmanX;
double gyroXangle;

uint32_t timer;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  init_mpu();

  acc = readAccel();
  gyro = readGyro();

  double roll = atan(acc.y/sqrt(acc.x * acc.x + acc.z * acc.z)) * RAD_TO_DEG;
  KalmanX.setAngle(roll);
  gyroXangle = gyro.x / 131.0;
  Input = roll;

  myPID.SetSampleTime(1);
  myPID.SetOutputLimits(40, 190);
  myPID.SetMode(AUTOMATIC);
  timer = micros();
}

void loop() {
  acc = readAccel();
  gyro = readGyro();

  double dt = (double)(micros() - timer)/1000000;
  timer = micros();

  double roll = atan(acc.y/sqrt(acc.x * acc.x + acc.z * acc.z)) * RAD_TO_DEG;
  gyroXangle = gyro.x / 131.0;
  Input = KalmanX.getAngle(roll, gyroXangle, dt);
  Serial.print(Input); Serial.print("\n");
  
  if (Input>Setpoint){
    Input *= -1;
    VSSS.forward();
  }
  else if (Input<Setpoint){
    VSSS.backward();
  }
  else{
    VSSS.brake();
  }
  myPID.Compute();
  //Serial.println(Output);
  VSSS.set_pwm(Output, Output);

  delay(10);
}