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

    Configure();
}

Logger::~Logger(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

RC_e Logger::Setup(char* host, uint16_t port){
    this->m_host = host;
    this->m_port = port;

    if(Configure() != RC_e::SUCCESS){
        return RC_e::ERROR_WIFI_CONNECTION;
    }
}

RC_e Logger::Write(char* msg){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if the socket client is connected to the server
    if(!this->m_client.connected()){
        if((retCode=Configure()) != RC_e::SUCCESS){
            return retCode;
        }
    }

    // Json and buffer
    StaticJsonDocument<JSON_MESSAGE_SIZE> logJson;
    char logBuffer[JSON_MESSAGE_SIZE];

    // Add nessage to the Json
    logJson["msg"] = msg;

    // Create buffer from Json
    serializeJson(logJson, logBuffer);

    // Send message
    this->m_client.println(logBuffer);

    return RC_e::SUCCESS;
}

RC_e Logger::WriteValue(u16_t value){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if the socket client is connected to the server
    if(!this->m_client.connected()){
        if((retCode=Configure()) != RC_e::SUCCESS){
            return retCode;
        }
    }

    // Json and buffer
    StaticJsonDocument<JSON_MESSAGE_SIZE> logJson;
    char logBuffer[JSON_MESSAGE_SIZE];

    // Add nessage to the Json
    logJson["val"] = value;

    // Create buffer from Json
    serializeJson(logJson, logBuffer);

    // Send message
    this->m_client.println(logBuffer);

    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

RC_e Logger::Configure(){
    // Connect to socket server
    if (!this->m_client.connect(this->m_host, this->m_port)){
        return RC_e::ERROR_WIFI_CONNECTION;
    }

    Write("Connected");

    return RC_e::SUCCESS;
}