/**
 * @file Logger.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to create log through Wifi using Wifi socket client
 * @version 1.0
 * @date 14-06-2020
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
     * @brief Construct a new Logger object
     * 
     * @param host Socket server hostname
     * @param port Socket server port
     */
    Logger(char* host, uint16_t port);

    /**
     * @brief Destroy the Logger object
     * 
     */
    ~Logger();

    /**
     * @brief Configure service
     * 
     * @return RC_e Result code
     */
    RC_e Configure();

    /**
     * @brief Write a message to the logger
     * 
     * @param msg Message to be sent
     * @return RC_e Result code
     */
    RC_e Write(char* msg);

    /**
     * @brief Write a value to the logger
     * 
     * @param msg Value to be sent
     * @return RC_e Result code
     */
    RC_e WriteValue(u16_t msg);

    /**
     * @brief Run the logger service
     * 
     */
    void Run();
    
private:
    char * m_host;                  /**< Socket server hostname */
    uint16_t m_port;                /**< Socket server port */
    SocketIoClient webSocket;       /**< Wifi Client used for socket connection */
    uint8_t m_flagSend;             /**< Flag of data to be sent */

   
};

#endif // LOGGER_H