#include <Arduino.h>
#include "../lib/esp32_common/WifiManager/WifiManager.h"

WifiManager *myWifiManager; 

void setup() {

}



void loop() {


    Serial.begin(115200);
    myWifiManager = new WifiManager("luiss10", "12345678", "SBR_ESP32_RemoteControl");

    
    while(true)
    {
        myWifiManager->HandleOTA();
        //Serial.println("handle");
    }

    return;

}