#include <Arduino.h>
#include "../lib/ESP32_Local/BluetoothManager/BluetoothManager.h"
#include "../lib/ESP32_Local/WifiManager/WifiManager.h"
#include "../lib/SBR_Global/Definition/GlobalDef.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define LED_BUILTIN 2

#define NumbersOfBytes 4   

BluetoothManager *myBluetoothManager;
char buffer[NumbersOfBytes];
boolean validframe;
boolean validData;

void setup() {

    myBluetoothManager = new BluetoothManager(buffer,NumbersOfBytes, "SBR_ESP32_Util", (int)10000);
    pinMode(LED_BUILTIN, OUTPUT);       // Config Output LED on board ESP32

    /*initialize variables*/
    validframe = false;
    validData = false;
}

void loop() {

    /*check if the RX has the number of Byte configured in the frame received (NumberOfBytes)*/
    validframe = myBluetoothManager->GetAllFrame();

    if(validframe == true)
    {
        /*check if the Frame has the Valid Data*/
        validData = myBluetoothManager->CheckAllData();
        if(validData == true)
        {
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        }       
    }
    else
    {
        /*Nothing to do*/
    }

    delay(20);
    
}