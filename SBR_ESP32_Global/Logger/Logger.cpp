/**
 * \file Logger.cpp
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

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "Logger.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

Logger::Logger(char* host, uint16_t port){
    this->m_host = host;
    this->m_port = port;

    this->m_flagSend = 0;

    Configure();
}

Logger::~Logger(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

RC_e Logger::Configure(){

    // Check if the Wifi is connected
    if (WiFi.status() != WL_CONNECTED) 
    {
        return RC_e::ERROR_WIFI_CONNECTION;
    }

    // Connect to socket server
    webSocket.begin(this->m_host, this->m_port);
    m_flagSend = 1;

    Write("Connected");

    return RC_e::SUCCESS;
}

RC_e Logger::Write(char* msg){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if the Wifi is connected
    if (WiFi.status() != WL_CONNECTED) 
    {
        return RC_e::ERROR_WIFI_CONNECTION;
    }

    // Check if the socket client is connected to the server
    // if(!this->webSocket.connected()){
    //     if((retCode=Configure()) != RC_e::SUCCESS){
    //         return retCode;
    //     }
    // }

    // Json and buffer
    StaticJsonDocument<JSON_MESSAGE_SIZE> logJson;
    char logBuffer[JSON_MESSAGE_SIZE];

    // Add nessage to the Json
    logJson["msg"] = msg;

    // Create buffer from Json
    serializeJson(logJson, logBuffer);

    // Send message
    this->webSocket.emit("data", logBuffer);
    m_flagSend = 1;

    return RC_e::SUCCESS;
}

RC_e Logger::WriteValue(u16_t value){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if the Wifi is connected
    if (WiFi.status() != WL_CONNECTED) 
    {
        return RC_e::ERROR_WIFI_CONNECTION;
    }

    // Check if the socket client is connected to the server
    // if(!this->m_client.connected()){
    //     if((retCode=Configure()) != RC_e::SUCCESS){
    //         return retCode;
    //     }
    // }

    // Json and buffer
    StaticJsonDocument<JSON_MESSAGE_SIZE> logJson;
    char logBuffer[JSON_MESSAGE_SIZE];

    // Add nessage to the Json
    logJson["val"] = value;

    // Create buffer from Json
    serializeJson(logJson, logBuffer);

    // Send message
    this->webSocket.emit("data",logBuffer);
    m_flagSend = 1;

    return RC_e::SUCCESS;
}

void Logger::Run(){
    if(m_flagSend !=0){
        if (WiFi.status() == WL_CONNECTED) 
        {
            webSocket.loop();
            m_flagSend = 0;
        }
    }
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

