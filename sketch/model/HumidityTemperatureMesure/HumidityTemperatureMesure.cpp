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

JsonObject HumidityTemperatureMesure::toJson(void){
    //256 Calculate with https://arduinojson.org/v5/assistant/
    DynamicJsonDocument doc(256);
    String input = "{\"humidity\": "+String(humidity)+",\"temperature\":"+String(temperature)+",\"heatIndex\":"+String(heatIndex)+",\"time\":"+String(elapsedTime)+"}";
    deserializeJson(doc, input);
    return doc.as<JsonObject>();
}