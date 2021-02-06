// ========================== Handle HTTP Request ========================
//
#include <WiFiClient.h>

//const uint16_t httpPort = 4000; //Local
const uint16_t httpPort = 80;
String methodHttp = "POST";
const char* httpVersion = "HTTP/1.1";
WiFiClient client;

bool initHttpRequest(char host[]) {
  
  if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return false;
  }
  return true;
}

void post(char host[], String path, DynamicJsonDocument data) {

  if(!isWifiConnected()) {
    Serial.println("Erreur d'envoi de la requete Wifi non connecté");
    if(!blinking){
      switchTemporaryBlinkRGB(255, 0,0, 1500);
    }
    return;
  }
  if(!initHttpRequest(host)) {
    Serial.print("Erreur impossible de se connecter à l'host: ");
    Serial.println(host);
    switchTemporaryBlinkRGB(0, 255,0, 1500);
    
    return;
  }
  //Header
  methodHttp = "POST";
  String dataStr = "";
  
  serializeJson(data, dataStr);
  client.println(methodHttp+ ' '+path+ ' '+httpVersion);
  client.println("Host: " + String(host));
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(dataStr.length()+1);
  client.println();
    
  // send HTTP body
  client.println(dataStr);

  readResponse();
  client.stop();
  delay(100);
}

//Affiche le résultat de la requête dans le moniteur de série
void readResponse() {
      delay(10);
      String line = client.readStringUntil('\n');
      if(line.indexOf("201") == -1){
        switchTemporaryBlinkRGB(0, 255, 0, 1500);
      }
      Serial.println(line);
      
}
