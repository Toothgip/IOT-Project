#ifndef LightMesure_h
#define LightMesure_h

#include <Arduino.h>

class LightMesure {
  public:
    LightMesure (float r,float g,float b, float paramC, float paramCct, float paramLux);

    String getRgb(void);

    float getC(void);
    float getCCT(void);
    float getLux(void);
    unsigned long getElapsedTime(void);

  private:
    String rgb;
    float c;
    float cct;
    float lux;
    unsigned long elapsedTime;
};
#endif