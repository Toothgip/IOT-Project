#include "LightMesure.h"

LightMesure::LightMesure (float r,float g,float b, float paramC, float paramCct, float paramLux){
    rgb = "rgb(";
    rgb += r+','+g+','+b+')';
    c = paramC;
    cct = paramCct;
    lux = paramLux;
    elapsedTime = millis();
}
String LightMesure::getRgb(void){
    return rgb;
}

float LightMesure::getC(void){
    return c;
}
float LightMesure::getCCT(void){
    return cct;
}
float LightMesure::getLux(void){
    return lux;
}
unsigned long LightMesure::getElapsedTime(void){
    return elapsedTime;
}