



//TODO Iddée faire clignoter la led intérieur quand un capteur n'est pas branché

void setup() {
  Serial.begin(9600);
  intializeDHTSensor();
  initializeLightSensor();  

}








void loop() {  
  getHumidityAndTemperature();
  getLight();
  Serial.println("----");
  delay(5000);
}
