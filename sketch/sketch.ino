
// ========================= Humidity sensor ==============================

#include "DHT.h"

#define DHTPIN 14     // Digital pin correpond to D2
#define DHTTYPE DHT22   // Sensor type DHT 22  (AM2302), AM2321


// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

// ========================== Light sensor ========================


#include <Wire.h>

#include "Seeed_TMG3993.h"
TMG3993 tmg3993;

void setup() {
  Serial.begin(9600);
  dht.begin();

  Wire.begin();

   if (tmg3993.initialize() == false) {
      Serial.println("Device not found. Check wiring.");
      while (1);
  }
  tmg3993.setADCIntegrationTime(0xdb); // the integration time: 103ms
  tmg3993.enableEngines(ENABLE_PON | ENABLE_AEN | ENABLE_AIEN);

}


void getHumidityAndTemperature() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print(F("Humidity: "));
  Serial.println(h);

  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

   Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.println(F("°C "));
  
}

void getLight() {
  if (tmg3993.getSTATUS() & STATUS_AVALID) {
        uint16_t r, g, b, c;
        int32_t lux, cct;
        tmg3993.getRGBCRaw(&r, &g, &b, &c);
        lux = tmg3993.getLux(r, g, b, c);
        //the calculation of CCT is just from the `Application Note`,
        //from the result of our test, it might have error.
        cct = tmg3993.getCCT(r, g, b, c);

        Serial.print("RGBC Data: ");
        Serial.print(r);
        Serial.print("\t");
        Serial.print(g);
        Serial.print("\t");
        Serial.print(b);
        Serial.print("\t");
        Serial.println(c);

        Serial.print("Lux: ");
        Serial.print(lux);
        Serial.print("\tCCT: ");
        Serial.println(cct);
        Serial.println("----");

        // don't forget to clear the interrupt bits
        tmg3993.clearALSInterrupts();
    }
}



void loop() {
  // put your main code here, to run repeatedly:
  delay(10000);
  getHumidityAndTemperature();
  getLight();
}
