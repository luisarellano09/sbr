/**
 * @file WifiManager.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the ESP32 Wifi
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "WifiManager.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

WifiManager::WifiManager(String ssid, String password, String hostName){
    // Set Wifi values
    this->m_ssid = ssid;
    this->m_password = password;
    this->m_hostName = hostName;
}


//=====================================================================================================

WifiManager::WifiManager(){
}


//=====================================================================================================

WifiManager::~WifiManager(){}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e WifiManager::Connect(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the Wifi is connected
    if (WiFi.status() != WL_CONNECTED) {

        if ((retCode = ConfigureWifi()) != RC_e::SUCCESS){
            Log.errorln("[WifiManager::Connect] Error in ConfigureWifi()");
            return retCode;        
        }

        if ((retCode = ConfigureOTA()) != RC_e::SUCCESS){
            Log.errorln("[WifiManager::Connect] Error in ConfigureOTA()");
            return retCode;        
        }

        if ((retCode = ConnectWifi()) != RC_e::SUCCESS){
            Log.errorln("[WifiManager::Connect] Error in ConnectWifi()");
            return retCode;        
        }
    }

    return retCode;  
}


//=====================================================================================================

RC_e WifiManager::RunOTA(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the Wifi is connected
    if (WiFi.status() == WL_CONNECTED) {
        // OTA Handling
        if ((retCode = HandleOTA()) != RC_e::SUCCESS){
            Log.errorln("[WifiManager::RunOTA] Error in HandleOTA()");
            return retCode;        
        }
    }

    return retCode;
}


//=====================================================================================================

RC_e WifiManager::SetWifiCredencials(String ssid, String password, String hostName){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_ssid = ssid;
    this->m_password = password;
    this->m_hostName = hostName;

    return retCode;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e WifiManager::ConfigureWifi(){

    // Station mode
    WiFi.mode(WIFI_STA);
    
    // Define Event
    WiFi.onEvent(
        [this](WiFiEvent_t event,WiFiEventInfo_t info) {
            this->WiFiEvent(event, info);
        });
    
    return RC_e::SUCCESS;
}


//=====================================================================================================

RC_e WifiManager::ConnectWifi(){
    // Check if Wifi is connected
    if (WiFi.status() != WL_CONNECTED) {

        // Station mode
        WiFi.mode(WIFI_STA);

        // Start Wifi
        WiFi.begin(m_ssid.c_str(), m_password.c_str());

        // Disable reconnection
        WiFi.setAutoConnect(false);
        WiFi.setAutoReconnect(false);

        Log.infoln("[WifiManager::ConnectWifi] Connecting...");

        // Set Hostname
        MDNS.begin(this->m_hostName.c_str());
        WiFi.setHostname(this->m_hostName.c_str());
    }

    return RC_e::SUCCESS;  
}


//=====================================================================================================

void WifiManager::WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info){
    // Wifi evento info
    Log.infoln("[WifiManager::WiFiEvent] WifiEvent: %d", event);

    switch (event) 
    {
        case SYSTEM_EVENT_WIFI_READY: 
            //Serial.println("WiFi interface ready");
            break;
        case SYSTEM_EVENT_SCAN_DONE:
            //Serial.println("Completed scan for access points");
            break;
        case SYSTEM_EVENT_STA_START:
            Log.infoln("[WifiManager::WiFiEvent] WiFi started");
            break;
        case SYSTEM_EVENT_STA_STOP:
            //Serial.println("WiFi clients stopped");
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            Log.infoln("[WifiManager::WiFiEvent] Wifi connected");
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Log.infoln("[WifiManager::WiFiEvent] Wifi disconnected");
            break;
        case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
            //Serial.println("Authentication mode of access point has changed");
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            Log.info("[WifiManager::WiFiEvent] IP address assigned: ");
            if (Log.getLevel() >= LOG_LEVEL_INFO) Serial.println(WiFi.localIP());
            Log.info("[WifiManager::WiFiEvent] MAC: ");
            if (Log.getLevel() >= LOG_LEVEL_INFO) Serial.println(WiFi.macAddress());
            break;
        case SYSTEM_EVENT_STA_LOST_IP:
            //Serial.println("Lost IP address and IP address is reset to 0");
            break;
        case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
            //Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
            break;
        case SYSTEM_EVENT_STA_WPS_ER_FAILED:
            //Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
            break;
        case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
            //Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
            break;
        case SYSTEM_EVENT_STA_WPS_ER_PIN:
            //Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
            break;
        case SYSTEM_EVENT_AP_START:
            //Serial.println("WiFi access point started");
            break;
        case SYSTEM_EVENT_AP_STOP:
            //Serial.println("WiFi access point  stopped");
            break;
        case SYSTEM_EVENT_AP_STACONNECTED:
            //Serial.println("Client connected");
            break;
        case SYSTEM_EVENT_AP_STADISCONNECTED:
            //Serial.println("Client disconnected");
            break;
        case SYSTEM_EVENT_AP_STAIPASSIGNED:
            //Serial.println("Assigned IP address to client");
            break;
        case SYSTEM_EVENT_AP_PROBEREQRECVED:
            //Serial.println("Received probe request");
            break;
        case SYSTEM_EVENT_GOT_IP6:
            //Serial.println("IPv6 is preferred");
            break;
        case SYSTEM_EVENT_ETH_START:
            //Serial.println("Ethernet started");
            break;
        case SYSTEM_EVENT_ETH_STOP:
            //Serial.println("Ethernet stopped");
            break;
        case SYSTEM_EVENT_ETH_CONNECTED:
            //Serial.println("Ethernet connected");
            break;
        case SYSTEM_EVENT_ETH_DISCONNECTED:
            //Serial.println("Ethernet disconnected");
            break;
        case SYSTEM_EVENT_ETH_GOT_IP:
            //Serial.println("Obtained IP address");
            break;
         default:
            break;
    }
}


//=====================================================================================================

RC_e WifiManager::ConfigureOTA(){
    // Hostname
    ArduinoOTA.setHostname(this->m_hostName.c_str());

    // Set OTA Port
    ArduinoOTA.setPort(8080);
   
    ArduinoOTA
    .onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else // U_SPIFFS
            type = "filesystem";

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Log.infoln("[WifiManager::ConfigureOTA] Start updating %s", type);
    })
    .onEnd([]() {
        if (Log.getLevel() >= LOG_LEVEL_INFO) Serial.println("");
        Log.infoln("[WifiManager::ConfigureOTA] End");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
        //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        Log.info("[WifiManager::ConfigureOTA] Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
        Log.errorln("[WifiManager::ConfigureOTA] Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Log.errorln("[WifiManager::ConfigureOTA] Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Log.errorln("[WifiManager::ConfigureOTA] Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Log.errorln("[WifiManager::ConfigureOTA] Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Log.errorln("[WifiManager::ConfigureOTA] Receive Failed");
        else if (error == OTA_END_ERROR) Log.errorln("[WifiManager::ConfigureOTA] End Failed");
    });

    ArduinoOTA.begin();

    return RC_e::SUCCESS;
}


//=====================================================================================================

RC_e WifiManager::HandleOTA(){
    ArduinoOTA.handle();
    delay(10);
    return RC_e::SUCCESS;
}
