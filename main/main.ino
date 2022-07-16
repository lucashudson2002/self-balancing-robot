/*
Program: Self Balancing Robot (Bluetooth, Stable, Radio)
Author: Lucas Dias Hudson
Date: July 16, 2022
GitHub: https://github.com/lucashudson2002/Self-Balancing-Robot
Prerequisites:
  https://github.com/lucashudson2002/TB6612FNG
  https://github.com/lucashudson2002/HCSR04
  https://github.com/nRF24/RF24
*/

//**LIBRARIES**
#include <HCSR04.h>
#include <TB6612FNG.h>
#include <RF24.h>
#include <SPI.h>
//MPU6050
#include "PID.h"

//**PINOUT**
//ENCODER
#define ENC1 2
#define ENC2 3
//PONTE-H
#define PWMA 5
#define IN1A 4
#define IN2A 7
#define IN1B 8
#define IN2B 9
#define PWMB 6
//MPU6050
#define SDA A4
#define SCL A5
//NRF24L01
#define CSN A0
#define CE A1
#define SCK 13
#define MOSI 11
#define MISO 12
//BLUETOOTH
#define RX 1
#define TX 0
//HCSR04
#define ECHO A2
#define TRIG A3
//BATERIA
#define BATTERY A6
#define LED 10
#define BUZZER A7

//**OTHERS DEFINE**
#define DIST_MIN_CM 30
#define BLUETOOTH 1
#define STABLE 2
#define RADIO 3
#define VOLTAGE_MIN 7 //testar se essa é a mínima
#define VOLTAGE_MAX 8.4 //2 lítios de 4.2V, na realidade é essa?
#define WAITING_TIME_SEND 100

//**VARIABLES**
TB6612FNG robot(IN1B, IN2B, IN1A, IN2A, PWMB, PWMA); //B são as rodas da esquerda, e A são as rodas da direita
HCSR04 hcsr04(TRIG, ECHO);
//objeto pro MPU6050
//objeto pro nrf
float kp = 0;
float ki = 0;
float kd = 0;
double input, output, setPoint = 0;
PID pid(input, output, setPoint, kp, ki, kd);
byte dir = 's';
byte mode = STABLE;
byte battery;
float proportion = 0.5;
byte pwm = 255;
unsigned long waiting_time_send = 0;


//**DECLARATION OF FUNCTIONS FOR THE 3 MODES**
void bluetooth();
void stable();
void radio();

//**DECLARATION OF OTHERS FUNCTIONS**
void measure_battery();
bool obstacle();
void send_data();
void verify_bluetooth();
void verify_radio();

void setup(){
  Serial.begin(9600);
  robot.begin();
  hcsr04.begin();
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BATTERY, INPUT);
  pinMode(ENC1, INPUT);
  pinMode(ENC2, INPUT);
  //interrupção pro encoder
  //FAZER: interrupção pro led de acordo com a bateria e buzzer tocar no nível crítico
}

void loop(){
  
}

//**DEFINITION OF FUNCTIONS**
//ki- kp- kd- d- pwm- prop- m-  
void bluetooth(){
  
}
void stable(){
  
}
void radio(){
  
}

void measure_battery(){
  int sensor = analogRead(BATTERY);
  float voltage = sensor*5.0/341.0;
  voltage = constrain(voltage, VOLTAGE_MIN, VOLTAGE_MAX);
  battery = map(voltage, VOLTAGE_MIN, VOLTAGE_MAX, 0, 100);
}
bool obstacle(){
  float distance = hcsr04.distance_cm();
  if (distance < DIST_MIN_CM && distance != -1 && distance != 0 ){
    robot.brake();
    delay(100);
    robot.set_pwm(255);
    robot.backward();
    delay(500);
    robot.brake();
    robot.set_pwm(pwm);
    return true;
  }
  return false;
}
void send_data(){
  if (millis() - waiting_time_send > WAITING_TIME_SEND){
    waiting_time_send = millis();
    String data = "b-"+String(battery)+"/";
    Serial.print(data);
    switch (mode){
      case BLUETOOTH:
        data = "m-bluetooth/";
        break;
      case STABLE:
        data = "m-stable/";
        break;
      case RADIO:
        data = "m-radio/";
        break;
    }
    Serial.print(data);
    data = "a-"+String(input)+"/";
    Serial.print(data);
    data = "kp-"+String(kp)+"/";
    Serial.print(data);
    data = "ki-"+String(ki)+"/";
    Serial.print(data);
    data = "kd-"+String(kd)+"/";
    Serial.print(data);
  }
}
void verify_bluetooth(){
  
}
void verify_radio(){
  
}
