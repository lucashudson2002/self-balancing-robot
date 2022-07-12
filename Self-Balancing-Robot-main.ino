//**bibliotecas**
#include <HCSR04.h>
#include <TB6612FNG.h>
#include <RF24.h>
#include <SPI.h>
//MPU6050

//**pinos**
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
#define DIVISOR A6
#define LED 10
#define BUZZER A7

//**variáveis**
TB6612FNG robo(IN1B, IN2B, IN1A, IN2A, PWMB, PWMA); //B são as rodas da esquerda, e A são as rodas da direita
HCSR04 hcsr04(TRIG, ECHO);
//objeto pro MPU6050
//objeto pro nrf

//**declaração das funções**
void bluetooth();
void estavel();
void radio();

void loop(){
  Serial.begin(9600);
  robo.begin();
  hcsr04.begin();
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(DIVISOR, INPUT);
  pinMode(ENC1, INPUT);
  pinMode(ENC2, INPUT);
  //interrupção pro encoder
}

void setup(){

}

//**definição das funções**
void bluetooth(){
  
}
void estavel(){
  
}
void radio(){
  
}
