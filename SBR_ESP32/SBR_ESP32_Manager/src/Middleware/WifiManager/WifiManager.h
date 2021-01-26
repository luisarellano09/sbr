/**
 * @file WifiManager.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the ESP32 Wifi
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "../../Definition/GlobalDef.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the ESP32 Wifi
 * 
 */
class WifiManager {
public:  

    /**
     * @brief Constructor
     * 
     * @param ssid Wifi name
     * @param password Wifi password
     * @param hostName ESP32 hostname
     */
    WifiManager(char* ssid, char* password, char* hostName);

    /**
     * @brief Destructor
     * 
     */
    ~WifiManager();

    /**
     * @brief Connect to Wifi services
     * 
     * @return RC_e Result code
     */
    RC_e Connect();

    /**
     * @brief Run OTA service
     * 
     * @return RC_e Result code
     */
    RC_e RunOTA();

    /**
     * @brief Enable the debug mode of the class
     * 
     * @return RC_e Result code
     */
    RC_e EnableDebugMode();

    /**
     * @brief Disable the debug mode of the class
     * 
     * @return RC_e Result code
     */
    RC_e DisableDebugMode();

private:
    char* m_ssid;               /**< Wifi name */
    char* m_password;           /**< Wifi password */ 
    char* m_hostName;           /**< ESP32 Hostname */

    bool m_debugMode = false;   /**< Debug Mode */

    /**
     * @brief Configure the Wifi
     * 
     * @return RC_e Ressult code
     */
    RC_e ConfigureWifi();

    /**
     * @brief Connect to a Wifi
     * 
     * @return RC_e Result code
     */
    RC_e ConnectWifi();

    /**
     * @brief Wifi Event handler
     * 
     * @param event Wifi event
     * @param info System information about the event
     */
    void WiFiEvent(WiFiEvent_t event,system_event_info_t info);

    /**
     * @brief Configure the OTA service
     * 
     * @return RC_e Result code
     */
    RC_e ConfigureOTA();

    /**
     * @brief Function to Handle the OTA service
     * 
     * @return RC_e Result code
     */
    RC_e HandleOTA();

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // WIFIMANAGER_H