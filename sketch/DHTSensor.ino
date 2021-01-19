// ========================= Humidity sensor ==============================

#include "DHT.h"
#define DHTPIN 14     // Digital pin correpond to D2
#define DHTTYPE DHT22   // Sensor type DHT 22  (AM2302), AM2321

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void intializeDHTSensor() {
  dht.begin();
}

HumidityTemperatureMesure getHumidityAndTemperature() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Erreur impossible de lire le capteur d'humidité"));
    HumidityTemperatureMesure error(-99.99,-99.99,-99.99);
    return error;
  }
  
  Serial.print(F("Humidity: "));
  Serial.println(h);

  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.println(F("°C "));

  HumidityTemperatureMesure mesure(h, t, hic);
  return mesure;
}
