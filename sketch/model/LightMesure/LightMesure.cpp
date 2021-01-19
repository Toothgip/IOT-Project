#include "LightMesure.h"

LightMesure::LightMesure (float r,float g,float b, float paramC, float paramCct, float paramLux){
    rgb = "("+String(r)+","+String(g)+","+String(b)+")";
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

JsonObject LightMesure::toJson(void){
    //256 Calculate with https://arduinojson.org/v5/assistant/
    DynamicJsonDocument doc(256);
    String input = "{\"rgb\":\""+rgb+"\",\"c\":"+String(c)+",\"lux\":"+String(lux)+",\"cct\":"+String(cct)+",\"time\":"+String(elapsedTime)+"}";
    deserializeJson(doc, input);
    return doc.as<JsonObject>();
}