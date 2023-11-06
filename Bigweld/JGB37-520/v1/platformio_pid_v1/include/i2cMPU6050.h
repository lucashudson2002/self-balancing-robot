#pragma once
#include <Wire.h>

const uint8_t IMUAddress = 0x68;
const uint16_t I2C_TIMEOUT = 1000;

uint8_t i2cWrite(uint8_t registerAddress, uint8_t *data, uint8_t length, bool sendStop) {
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  Wire.write(data, length);
  uint8_t rcode = Wire.endTransmission(sendStop);
  if (rcode) {
    //Serial.print(F("i2cWrite failed: "));
    //Serial.println(rcode);
  }
  return rcode;
}

uint8_t i2cWrite(uint8_t registerAddress, uint8_t data, bool sendStop) {
  return i2cWrite(registerAddress, &data, 1, sendStop);
}

uint8_t i2cRead(uint8_t registerAddress, uint8_t *data, uint8_t nbytes) {
  uint32_t timeOutTimer;
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  uint8_t rcode = Wire.endTransmission(false);
  if (rcode) {
    //Serial.print(F("i2cRead failed: "));
    //Serial.println(rcode);
    return rcode;
  }
  Wire.requestFrom(IMUAddress, nbytes, (uint8_t)true);
  for (uint8_t i = 0; i < nbytes; i++) {
    if (Wire.available())
      data[i] = Wire.read();
    else {
      timeOutTimer = micros();
      while (((micros() - timeOutTimer) < I2C_TIMEOUT) && !Wire.available());
      if (Wire.available())
        data[i] = Wire.read();
      else {
        //Serial.println(F("i2cRead timeout"));
        return 5;
      }
    }
  }
  return 0;
}

uint8_t i2c_data[14];

struct Point3lf{
  double x, y, z;
};

void init_mpu(){
  Wire.begin();

  #if ARDUINO >= 157
    Wire.setClock(400000UL);
  #else
    TWBR = ((F_CPU/400000UL) - 16) / 2;
  #endif

  i2c_data[0] = 7;
  i2c_data[1] = 0x00;
  i2c_data[2] = 0x00;
  i2c_data[3] = 0x00;

  while(i2cWrite(0x19, i2c_data, 4, false));

  while(i2cWrite(0x6B, 0x01, true));

  while(i2cRead(0x75, i2c_data, 1));

  if(i2c_data[0] != 0x68){
    //Serial.print("Erro. Placa desconhecida\n");
    while(1){
      //Serial.print("Erro. Conecte a MPU6050 no barramento i2c\n");
    }
  }
}

Point3lf readAccel(){
  Point3lf acc;
  while(i2cRead(0x3B, i2c_data, 14));
  acc.x = (int16_t)((i2c_data[0] << 8) | i2c_data[1]);
  acc.y = (int16_t)((i2c_data[2] << 8) | i2c_data[3]);
  acc.z = (int16_t)((i2c_data[4] << 8) | i2c_data[5]);
  return acc;
}

Point3lf readGyro(){
  Point3lf gyro;
  while(i2cRead(0x3B, i2c_data, 14));
  gyro.x = (int16_t)((i2c_data[8] << 8) | i2c_data[9]);
  gyro.y = (int16_t)((i2c_data[10] << 8) | i2c_data[11]);
  gyro.z = (int16_t)((i2c_data[12] << 8) | i2c_data[13]);
  return gyro;
}