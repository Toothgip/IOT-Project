#include <LightMesure.h>
#include <HumidityTemperatureMesure.h>

//TODO Idée faire clignoter la led intérieur quand un capteur n'est pas branché

void setup() {
  Serial.begin(9600);
  intializeDHTSensor();
  initializeLightSensor();  
  loginWifi();
  millis();
}



void loop() {  
  getHumidityAndTemperature();
  getLight();
  Serial.println("----");
  delay(5000);
  //connectGoogle();
}
