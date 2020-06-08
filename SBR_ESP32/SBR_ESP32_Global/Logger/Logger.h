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
 * 01.05.2020: Add WriteValue
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
#include "SocketIoClient.h"
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
     * \brief Function to configure.
     *
     * \return Error Code.
     */  
    RC_e Configure();

    /**
     * \brief Function to send a message to the logger.
     * \param msg Message to send.
     * \return Error Code.
     */  
    RC_e Write(char* msg);

    /**
     * \brief Function to send a value to the logger.
     * \param value Message to send.
     * \return Error Code.
     */  
    RC_e WriteValue(u16_t msg);

     void Run();
    
private:
    char * m_host;                  /** Socket server hostname */
    uint16_t m_port;                /** Socket server port */
    SocketIoClient webSocket;       /** Wifi Client used for socket connection */
    uint8_t m_flagSend;

   
};

#endif // LOGGER_H