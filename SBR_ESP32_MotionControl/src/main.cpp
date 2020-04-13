#include <Arduino.h>
#include "../lib/SBR_Global/WifiManager/WifiManager.h"
#include "../lib/SBR_Global/Definition/GlobalDef.h"

WifiManager *myWifiManager; 

void setup() {

}



void loop() {

    int a = READ; 


    Serial.begin(115200);
    myWifiManager = new WifiManager("luiss10", "12345678", "SBR_ESP32_MotionControl");

    
    while(true)
    {
        myWifiManager->HandleOTA();
        //Serial.println("handle");
    }

    return;

}