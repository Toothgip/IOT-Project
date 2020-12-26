// ========================== Bluetooth handler ========================
//

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void initializeBluetooth() {
  SerialBT.begin("ESP32Tamagochi"); //Bluetooth device name
}

void writeData(float data) {
  if(SerialBT.hasClient()) {
    Serial.println("Impossible d'envoyer des data pas de client connecté");
    return;  
  }
  //SerialBT.write(data);
}

//TODO Faire une tâche d'interruption pour dire qu'on est connecter en bluetooth
