#include <LightMesure.h>
#include <HumidityTemperatureMesure.h>
#include <ArduinoJson.h>


//Constant for integreated ked
const int BUTTON_PIN = 15;     // D5
const int LED_PIN =  13;      // the number of the LED pin

//Constant for interaction button
int buttonState = 0;         // variable for reading the pushbutton status
int food = 0;

//Constant for rgb led
bool blinking = false;

void setup() {  
  switchOnRGB(255, 0, 0);
  pinMode(BUTTON_PIN, INPUT);
  
  Serial.begin(115200);
  intializeDHTSensor();
  initializeLightSensor();  
  loginWifi();
  //Interruption quand on clique sur le bouton
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonClicked, FALLING);
  delay(100);


  //There was no problem during initialization => Green light
  if(!blinking) {
    switchOnRGB(0, 255, 0);
  }
}



void loop() {  
  HumidityTemperatureMesure htm = getHumidityAndTemperature();
  LightMesure lm = getLight();
  sendData(htm, lm);
  food = 0;
  Serial.println("\n----");
  delay(3000);  
}

//Envoi des données à l'API
void sendData(HumidityTemperatureMesure htm, LightMesure lm) {
  DynamicJsonDocument jsonBuffer(512);
  jsonBuffer["lightMesure"] = lm.toJson();
  jsonBuffer["humidityTemperatureMesure"] = htm.toJson();
  jsonBuffer["food"] = food;
  post("aqueous-oasis-80188.herokuapp.com", "/api/data", jsonBuffer);
  //Quand l'API est sur un réseau local
  //post("192.168.1.7", "/api/data", jsonBuffer);
}


void buttonClicked() {
  buttonState = digitalRead(BUTTON_PIN);
  switchTemporaryBlinkRGB(255, 255, 0, 1500);
  Serial.println("Button pressed");
  food++;
  
}
