#include <Arduino.h>
#include <Kalman.h>
#include "pid.h"
#include "motor.h"
#include "i2cMPU6050.h"
#include "bluetooth.h"

#define LED 2
#define BUZZER 4

// MPU6050 e KALMAN
Point3lf acc, gyro;
double pitch;
double gyroY;
Kalman KalmanY;
uint32_t timer;
double dt;

// CONTROLE PID
double Input, Output, Setpoint=0;
PID pid(&Input, &Output, &Setpoint);

void setup() {
    Serial.begin(115200);

    SerialBT.begin("Bigweld");

    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    pinMode(PWMA, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(STBY, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);

    ledcAttachPin(PWMA, 0);
    ledcSetup(0, 19500, 12);
    ledcAttachPin(PWMB, 1);
    ledcSetup(1, 19500, 12);

    digitalWrite(STBY, HIGH);

    ledcWrite(0, 0);
    ledcWrite(1, 0);

    pinMode(ENA1, INPUT);
    pinMode(ENA2, INPUT);
    pinMode(ENB1, INPUT);
    pinMode(ENB2, INPUT);

    attachInterrupt(ENA1, encoderA, CHANGE);
    attachInterrupt(ENB1, encoderB, CHANGE);

    init_mpu();

    acc = readAccel();
    gyro = readGyro();
    pitch = atan(-acc.x / sqrt(acc.y * acc.y + acc.z * acc.z)) * RAD_TO_DEG;
    Input = pitch;
    KalmanY.setAngle(Input);

    pid.setOutputLimits(-4095, 4095);

    timer = micros();
}

void loop() {
    if (readBluetooth())
        pid.setTunings(jsonPID["kp"], jsonPID["ki"], jsonPID["kd"]);
    
    sendBluetooth(Input);

    acc = readAccel();
    gyro = readGyro();
    pitch = atan(-acc.x / sqrt(acc.y * acc.y + acc.z * acc.z)) * RAD_TO_DEG;
    gyroY = gyro.y / 131.0;

    dt = (double)(micros() - timer)/1000000;
    timer = micros();

    Input = KalmanY.getAngle(pitch, gyroY, dt);

    pid.compute();

    int pwm = map(abs(Output), 0, 4095, MOTOR_MIN, 4095);
    if (Output > 0)
        forward(pwm, pwm);
    else if (Output < 0)
        backward(pwm, pwm);
    else
        brake();

    // Serial.println(pwm);

    // Serial.printf("%lf\t%f\n", pitch, Input);
}