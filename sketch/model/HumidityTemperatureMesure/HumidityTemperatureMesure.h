#ifndef HumidityTemperatureMesure_h
#define HumidityTemperatureMesure_h

#include <Arduino.h>
#include <ArduinoJson.h>

class HumidityTemperatureMesure {
  public:
    HumidityTemperatureMesure (float h,float t,float hi);
    float getTemperature(void);
    float getHeatIndex(void);
    float getHumidity(void);
    unsigned long getElapsedTime(void);
    JsonObject toJson(void);
  private:
    float humidity;
    float temperature;
    float heatIndex;
    unsigned long elapsedTime;
};
#endif