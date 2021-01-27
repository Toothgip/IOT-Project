#include <LightMesure.h>
#include <HumidityTemperatureMesure.h>
#include <ArduinoJson.h>
#include "BluetoothSerial.h"

const int buttonPin = 15;     // D5
const int ledPin =  13;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status
int food = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, LOW);
  
  Serial.begin(115200);
  intializeDHTSensor();
  initializeLightSensor();  
  loginWifi();
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonClicked, FALLING);
  delay(200);
  digitalWrite(ledPin, HIGH);
}



void loop() {  
  HumidityTemperatureMesure htm = getHumidityAndTemperature();
  LightMesure lm = getLight();
  sendData(htm, lm);
  food = 0;
  Serial.println("\n----");
  delay(2000);
  
}


void sendData(HumidityTemperatureMesure htm, LightMesure lm) {
  DynamicJsonDocument jsonBuffer(512);
  jsonBuffer["lightMesure"] = lm.toJson();
  jsonBuffer["humidityTemperatureMesure"] = htm.toJson();
  jsonBuffer["food"] = food;
  //post("aqueous-oasis-80188.herokuapp.com", "/api/data", jsonBuffer);
  post("192.168.1.7", "/api/data", jsonBuffer);
}


void buttonClicked() {
  buttonState = digitalRead(buttonPin);
  Serial.println("Button pressed");
  food++;
  
}
