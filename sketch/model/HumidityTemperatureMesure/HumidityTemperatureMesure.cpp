#include "HumidityTemperatureMesure.h"

HumidityTemperatureMesure::HumidityTemperatureMesure (float h,float t,float hi){
    humidity = h;
    temperature = t;
    heatIndex = hi;
    elapsedTime = millis();
}
float HumidityTemperatureMesure::getTemperature(void){
    return temperature;
}
float HumidityTemperatureMesure::getHeatIndex(void){
    return heatIndex;
}
float HumidityTemperatureMesure::getHumidity(void){
    return humidity;
}
unsigned long HumidityTemperatureMesure::getElapsedTime(void){
    return elapsedTime;
}