#include <Arduino.h>
#include "../lib/esp32_common/BluetoothManager/BluetoothManager.h"
#include "../lib/esp32_common/WifiManager/WifiManager.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define LED_BUILTIN 2

#define NumbersOfBytes 4   

//BluetoothSerial SerialBT;
BluetoothManager *myBluetoothManager;
char* buffer;


void setup() {
    //SerialBT.begin("ESP32_UTIL");       //name of device bluetooth
    //SerialBT.setTimeout(100);           //100 miliseconds
    pinMode(LED_BUILTIN, OUTPUT);       // Config Output LED on board ESP32
    
}

void loop() {

    myBluetoothManager = new BluetoothManager(buffer,NumbersOfBytes, "SBR_ESP32_Util", (int)1000);
    while(1){
         myBluetoothManager->updateBuffer();
         delay(20);
     }

    delay(20);
    
}