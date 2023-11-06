#pragma once
#include <BluetoothSerial.h>
#include <ArduinoJson.h>

BluetoothSerial SerialBT;

StaticJsonDocument<200> jsonPID;

bool readBluetooth(){
    if(SerialBT.available()){
        String data = SerialBT.readStringUntil('}') + String("}");
        deserializeJson(jsonPID, data);
        Serial.println(data);
        return true;
    }
    return false;
}

void sendBluetooth(double msg){
    SerialBT.println(msg);
}