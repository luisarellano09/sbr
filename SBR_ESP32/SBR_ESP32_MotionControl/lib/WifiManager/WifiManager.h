/**
 * @file WifiManager.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the Wifi
 * @version 1.0
 * @date 14-06-2020
 * 
 * 
 */

#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "../Definition/GlobalDef.h"

/*******************************************************************************************************************************************
 *  												WifiManager Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the Wifi
 * 
 */
class WifiManager
{
public:  

    /**
     * @brief Construct a new Wifi Manager object
     * 
     * @param ssid Wifi name
     * @param password Wifi password
     * @param hostName ESP32 hostname
     */
    WifiManager(char* ssid, char* password, char* hostName);

    /**
     * @brief Destroy the Wifi Manager object
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

private:
    char* m_ssid;               /**< Wifi name */
    char* m_password;           /**< Wifi password */ 
    char* m_hostName;           /**< ESP32 Hostname */

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

};

#endif // WIFIMANAGER_H