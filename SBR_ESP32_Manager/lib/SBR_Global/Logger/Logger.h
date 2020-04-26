/**
 * \file Logger.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 26 April 2020
 *
 * \brief Class to create log through Wifi using Wifi socket client.
 *
 * 
 * 
 * Changes
 * 26.04.2020: Create Class
 * 
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/

#include <WiFi.h>
#include <ArduinoJson.h>
#include "../Definition/GlobalDef.h"

/*******************************************************************************************************************************************
 *  												DEFINE
 *******************************************************************************************************************************************/

#define JSON_MESSAGE_SIZE 500

/*******************************************************************************************************************************************
 *  												WifiManager Class
 *******************************************************************************************************************************************/

/**
 * \brief Class to Manage the Wifi.
 */
class Logger
{
public:  

    /**
     * \brief Constructor.
     * \param host Socket server hostname.
     * \param port Socket server port.
     */
    Logger(char* host, uint16_t port);

    /**
     * \brief Destructor.
     */
    ~Logger();

    /**
     * \brief Function to execute the Manager.
     * \param msg Message to send.
     * \return Error Code.
     */  
    RC_e Write(char* msg);
    
private:
    char * m_host;                                      /** Socket server hostname */
    uint16_t m_port;                                    /** Socket server port */
    WiFiClient m_client;                                /** Wifi Client used for socket connection */

    /**
     * \brief Function to configure.
     *
     * \return Error Code.
     */  
    RC_e Configure();

};

#endif // LOGGER_H