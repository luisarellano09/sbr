/**
 * @file WifiManager.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the ESP32 Wifi
 * @version 1.0
 * @date 16.10.2022
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

#include "../../Definition/Global/RC.h"

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
    WifiManager(String ssid, String password, String hostName);

    /**
     * @brief Constructor
     * 
     */
    WifiManager();

    /**
     * @brief Destructor
     * 
     */
    ~WifiManager();

    /**
     * @brief Function to connect to Wifi services
     * 
     * @return RC_e Result code
     */
    RC_e Connect();

    /**
     * @brief Function to run OTA service
     * 
     * @return RC_e Result code
     */
    RC_e RunOTA();

    /**
     * @brief Function to set the Wifi credencials
     * 
     * @return RC_e Result code
     */
    RC_e SetWifiCredencials(String ssid, String password, String hostName);


private:
    String m_ssid;               /**@brief Wifi name */
    String m_password;           /**@brief Password */ 
    String m_hostName;           /**@brief ESP32 Hostname */

    /**
     * @brief Function to configure the Wifi
     * 
     * @return RC_e Ressult code
     */
    RC_e ConfigureWifi();

    /**
     * @brief Function to connect to a Wifi
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
    void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info);

    /**
     * @brief Function to configure the OTA service
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