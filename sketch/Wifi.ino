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


void isWifiConnected() {
  return Wifi.status() == WL_CONNECTED;
}
