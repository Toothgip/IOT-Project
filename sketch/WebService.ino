// ========================== Handle HTTP Request ========================
//


const int httpPort = 80;
char[] method = "POST";
const char[] httpVersion = "HTTP/1.1";
void initHttpRequest(host) {
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return false;
  }
  return true;
}

void post(host, path, data) {
  //Faire une fonction génerique de Headers HTTP

  if(!isWifiConnected()) {
    Serial.println("Erreur d'envoi de la requete Wifi non connecté");
  }
  
  initHttpRequest(host);
  //Header
  method = "POST";
  client.println(method+ " "+path+ " "+httpVersion);
  client.println("Host: " + String(host));
  client.println("Connection: close");
  client.println(); // end HTTP header

  // send HTTP body
  client.println(queryString);
}
