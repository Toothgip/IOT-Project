// ========================== Wifi handler ========================
//
#include <WiFi.h>

//TODO: Faire une tache asynchrone
//TODO Gerer plusieurs wifi

char* SSID = "OnePlus 6";
char* pwd = "123456789";

void loginWifi() {
  WiFi.begin(SSID, pwd);

  Serial.print("Waiting for WiFi... ");

  while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void connectGoogle() {
  WiFiClient client;
    if (!client.connect("www.google.com", 80)) {
        Serial.println("Connection failed.");
        Serial.println("Waiting 5 seconds before retrying...");
        delay(5000);
        return;
    }
    client.println("GET /search?q=arduino HTTP/1.1");
    client.print(String("GET ") + "www.google.com" + " HTTP/1.1\r\n" +
                 "Host: " + "www.google.com" + "\r\n" +
                 "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }
                 
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }
}
