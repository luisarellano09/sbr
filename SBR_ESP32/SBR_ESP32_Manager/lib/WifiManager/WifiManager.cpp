/**
 * @file WifiManager.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the Wifi
 * @version 1.0
 * @date 14-06-2020
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "WifiManager.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

//=====================================================================================================
WifiManager::WifiManager(char* ssid, char* password, char* hostName){
    // Set values
    this->m_ssid = ssid;
    this->m_password = password;
    this->m_hostName = hostName;
}

//=====================================================================================================
WifiManager::~WifiManager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e WifiManager::Connect(){
    // Check if the Wifi is connected
    if (WiFi.status() != WL_CONNECTED) {

        // Configure Wifi
        ConfigureWifi();

        // Configure OTA
        ConfigureOTA();

        // Run
        ConnectWifi();
    }

    return RC_e::SUCCESS;  
}

//=====================================================================================================
RC_e WifiManager::RunOTA(){
    // Error code
    RC_e retCode = RC_e::ERROR;

    // Check if the Wifi is connected
    if (WiFi.status() == WL_CONNECTED) 
    {
        // OTA
        if ((retCode = HandleOTA()) != RC_e::SUCCESS){
            return retCode;        
        }
    }

    return RC_e::SUCCESS;
}


/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e WifiManager::ConfigureWifi(){

    // Station mode
    WiFi.mode(WIFI_STA);
    
    // Define Event
    WiFi.onEvent(
        [this](WiFiEvent_t event,system_event_info_t info) {
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
        WiFi.begin(m_ssid, m_password);

        // Disable reconnection
        WiFi.setAutoConnect(false);
        WiFi.setAutoReconnect(false);

        Serial.println("Connecting...");

        // Set Hostname
        MDNS.begin(this->m_hostName);
        WiFi.setHostname(this->m_hostName);
    }

    return RC_e::SUCCESS;  
}

//=====================================================================================================
void WifiManager::WiFiEvent(WiFiEvent_t event,system_event_info_t info){
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch (event) 
    {
        case SYSTEM_EVENT_WIFI_READY: 
            //Serial.println("WiFi interface ready");
            break;
        case SYSTEM_EVENT_SCAN_DONE:
            //Serial.println("Completed scan for access points");
            break;
        case SYSTEM_EVENT_STA_START:
            //Serial.println("WiFi client started");
            break;
        case SYSTEM_EVENT_STA_STOP:
            //Serial.println("WiFi clients stopped");
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            //Serial.println("Connected to access point");
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("Disconnected from WiFi access point");
            break;
        case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
            //Serial.println("Authentication mode of access point has changed");
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.print("Obtained IP address: ");
            Serial.println(WiFi.localIP());
            Serial.println(WiFi.macAddress());
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
    ArduinoOTA.setHostname(this->m_hostName);

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
        Serial.println("Start updating " + type);
    })
    .onEnd([]() {
        Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
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


