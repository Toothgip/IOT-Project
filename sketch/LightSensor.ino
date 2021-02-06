// ========================== Light sensor ========================
//

#include <Wire.h>

#include "Seeed_TMG3993.h"
TMG3993 tmg3993;

void initializeLightSensor() {
  Wire.begin();
  
  if (tmg3993.initialize() == false) {
      Serial.println("Device not found. Check wiring.");
      switchTemporaryBlinkRGB(255, 255,255, 1500);
  }
  tmg3993.setADCIntegrationTime(0xdb); // the integration time: 103ms
  tmg3993.enableEngines(ENABLE_PON | ENABLE_AEN | ENABLE_AIEN);
}


//Recupere les mesures
LightMesure getLight() {
  if (tmg3993.getSTATUS() & STATUS_AVALID && tmg3993.getDeviceID() != 15) {
        uint16_t r, g, b, c;
        int32_t lux, cct;
        tmg3993.getRGBCRaw(&r, &g, &b, &c);
        lux = tmg3993.getLux(r, g, b, c);

        cct = tmg3993.getCCT(r, g, b, c);
        //Valeur RGB dépendent de l'intensité lumineuse
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
        //CCT correspond a la chaleur de la temperature en Kelvin
        Serial.print("\tCCT: ");
        Serial.println(cct);
        
        // don't forget to clear the interrupt bits
        tmg3993.clearALSInterrupts();

         LightMesure mesure(r, g, b, c ,cct, lux);
         return mesure;
    }
    else {
      Serial.println("Erreur capteur lumière non reconnu");
      initializeLightSensor();
      LightMesure error(0.00, 0.00, 0.00, 0.00 ,0.00, 0.00);      
      return error;
    }
}
