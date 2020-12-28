#include <LightMesure.h>
#include <HumidityTemperatureMesure.h>
#include <ArduinoJson.h>

//TODO Idée faire clignoter la led intérieur quand un capteur n'est pas branché

void setup() {
  Serial.begin(9600);
  intializeDHTSensor();
  initializeLightSensor();  
  loginWifi();
  millis();
}



void loop() {  
  HumidityTemperatureMesure htm = getHumidityAndTemperature();
  LightMesure lm = getLight();
  sendData(htm, lm);
  Serial.println("\n----");
  delay(5000);
}


void sendData(HumidityTemperatureMesure htm, LightMesure lm) {
  DynamicJsonDocument jsonBuffer(512);
  jsonBuffer["lightMesure"] = lm.toJson();
  jsonBuffer["humidityTemperatureMesure"] = htm.toJson();
  //post("localhost:8080", "mesure", root);
  post("httpbin.org", "/post", jsonBuffer);
}
