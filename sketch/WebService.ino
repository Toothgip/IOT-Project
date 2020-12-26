// ========================== Handle HTTP Request ========================
//
#include <WiFiClient.h>

//TODO Quand on envoit des données mettre a jour le elapsed time  en faisant current - NewTime
const uint16_t httpPort = 80;
char* methodHttp = "POST";
const char* httpVersion = "HTTP/1.1";
WiFiClient client;

bool initHttpRequest(char* host) {
  
  if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return false;
  }
  return true;
}

void post(char* host, String path, String data) {
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
  client.println(methodHttp+ ' '+path+ ' '+httpVersion);
  client.println("Host: " + String(host));
  client.println("Connection: close");
  client.println(); // end HTTP header

  // send HTTP body
  //client.println(queryString);
}
