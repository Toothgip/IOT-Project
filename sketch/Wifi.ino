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
  unsigned long timeout = millis();
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
    if (millis() - timeout > 2000) {
      WiFi.begin(SSID, pwd);
    }
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
}


bool isWifiConnected() {
  return WiFi.status() == WL_CONNECTED;
}
