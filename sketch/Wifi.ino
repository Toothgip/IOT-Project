// ========================== Wifi handler ========================
//
#include <WiFi.h>


//Wifi Telephone
/*char* SSID = "OnePlus 6";
char* pwd = "123456789";*/

//Wifi Appart
char* SSID = "Ninebox";
char* pwd = "Quentin2Montargis";

void loginWifi() {
  WiFi.begin(SSID, pwd);

  Serial.print("Waiting for WiFi... ");
  unsigned long timeout = millis();
  delay(500);
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
