// ========================== Handle HTTP Request ========================
//
#include <WiFiClient.h>

//En local
//const uint16_t httpPort = 4000;
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
  //Faire une fonction génerique de Headers HTTP

  if(!isWifiConnected()) {
    Serial.println("Erreur d'envoi de la requete Wifi non connecté");
  }
  if(!initHttpRequest(host)) {
    Serial.print("Erreur impossible de se connecter à l'host: ");
    Serial.println(host);
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
}

void readResponse() {
    while(client.connected()) {
      delay(10);
      String line = client.readStringUntil('\r');
      Serial.print(line);
       
    }
}
