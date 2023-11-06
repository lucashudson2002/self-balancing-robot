#pragma once
#include <Arduino.h>

#define PWMA 32
#define AIN2 33
#define AIN1 25
#define STBY 26
#define BIN1 27
#define BIN2 14
#define PWMB 13
#define ENA1 34
#define ENA2 35
#define ENB1 17
#define ENB2 16

#define MOTOR_MIN 500

byte ena1Last;
int pulse_numberA = 0;
bool directionA;

byte enb1Last;
int pulse_numberB = 0;
bool directionB;

void encoderA() {
    int Lstate = digitalRead(ENA1);

    if(!ena1Last && Lstate)
    {
        int val = digitalRead(ENA2);

        if(!val && directionA) directionA = false;
        else if(val && !directionA) directionA = true;
    }

    ena1Last = Lstate;

    if(!directionA)  pulse_numberA++;
    else pulse_numberA--;
}

void encoderB() {
    int Lstate = digitalRead(ENB1);

    if(!enb1Last && Lstate)
    {
        int val = digitalRead(ENB2);

        if(!val && directionB) directionB = false;
        else if(val && !directionB) directionB = true;
    }

    enb1Last = Lstate;

    if(!directionB)  pulse_numberB--;
    else pulse_numberB++;
}

void forward(int left, int right){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    ledcWrite(0, left);
    ledcWrite(1, right);
}

void backward(int left, int right){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(0, left);
    ledcWrite(1, right);
}

void stop(){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    ledcWrite(0, 0);
    ledcWrite(1, 0);
}

void brake(){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, HIGH);
    ledcWrite(0, 4095);
    ledcWrite(1, 4095);
}