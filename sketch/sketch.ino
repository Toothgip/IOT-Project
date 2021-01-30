#include <LightMesure.h>
#include <HumidityTemperatureMesure.h>
#include <ArduinoJson.h>

const int BUTTON_PIN = 15;     // D5
const int LED_PIN =  13;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status
int food = 0;


void setup() {
  //Initialisation de la led rouge
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
  
  Serial.begin(115200);
  intializeDHTSensor();
  initializeLightSensor();  
  loginWifi();
  //Interruption quand on clique sur le bouton
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonClicked, FALLING);
  delay(200);
  digitalWrite(LED_PIN, HIGH);
}



void loop() {  
  HumidityTemperatureMesure htm = getHumidityAndTemperature();
  LightMesure lm = getLight();
  sendData(htm, lm);
  food = 0;
  Serial.println("\n----");
  delay(2000);
  
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
  Serial.println("Button pressed");
  food++;
  
}
