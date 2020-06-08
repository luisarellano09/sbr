/**
 * \file WifiManager.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 16 April 2020
 *
 * \brief Class to Manage the Wifi
 *
 * 
 * 
 * Changes
 * 24.05.2020: Delete logger
 * 23.05.2020: Fix bugs
 * 30.04.2020: Logger reference
 * 16.04.2020: Class comments and RC_e concept
 * 13.04.2020: Doc was created
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
 * \brief Class to Manage the Wifi.
 */
class WifiManager
{
public:  

    /**
     * \brief Constructor.
     */
    WifiManager(char* ssid, char* password, char* hostName);

    /**
     * \brief Destructor.
     */
    ~WifiManager();

    /**
     * \brief Function to connect services.
     *
     * \return Error code.
     */
    RC_e Connect();

    /**
     * \brief Function to execute the Manager.
     *
     * \return Error Code.
     */  
    RC_e RunOTA();

private:
    char* m_ssid;               /** Wifi router name */
    char* m_password;           /** Wifi password */ 
    char* m_hostName;           /** ESP32 Hostname */

    /**
     * \brief Function to Configure the Wifi.
     *
     * \return Error code.
     */
    RC_e ConfigureWifi();

    /**
     * \brief Function to connect to a Wifi.
     *
     * \return Error code.
     */
    RC_e ConnectWifi();

    /**
     * \brief Wifi Event handler.
     *
     * \return void
     */
    void WiFiEvent(WiFiEvent_t event,system_event_info_t info);

    /**
     * \brief Wifi Event handler.
     *
     * \return Error code.
     */
    RC_e ConfigureOTA();

    /**
     * \brief Function to Handle the OTA.
     *
     * \return Error Code.
     */
    RC_e HandleOTA();

};

#endif // WIFIMANAGER_H