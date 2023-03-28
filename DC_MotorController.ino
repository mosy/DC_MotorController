/*
  Modbus-Arduino Example - Test Holding Register (Modbus IP ESP8266)
  Configure Holding Register (offset 100) with initial value 0xABCD
  You can get or set this holding register
  Original library
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino

  Current version
  (c)2017 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

//#ifdef ESP8266
// #include <ESP8266WiFi.h>
//#else //ESP32
 #include <WiFi.h>
//#endif
#include <ModbusIP_ESP8266.h>
#include "arduino_secrets.h"
const int DO1 = 21; //GPIO0
const int DO2 = 23; //GPIO0



//ModbusIP object
ModbusIP mb;
  
void setup() {
  Serial.begin(115200);
 
  //WiFi.begin("your_ssid", "your_password");
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

mb.server();
pinMode(DO1, OUTPUT);
pinMode(DO2, OUTPUT);
ledcSetup(0, 1000, 16);
ledcSetup(1, 1000, 16);
ledcAttachPin(DO1, 0);
ledcAttachPin(DO2, 1);
mb.addHreg(1,0,2);
}
 
void loop() {
   //Call once inside loop() - all magic here
   mb.task();
	ledcWrite(0, mb.Hreg(1));
	ledcWrite(1, mb.Hreg(2));
   delay(10);
}
