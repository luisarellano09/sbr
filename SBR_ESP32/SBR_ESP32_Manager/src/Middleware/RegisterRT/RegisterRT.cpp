/**
 * @file RegisterRT.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a register of the Data Table in Runtime
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "RegisterRT.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

RegisterRT::RegisterRT(){
    // Init
    this->m_value = 0;
    this->m_subscribers_index = -1;

    if (CleanSubscribers() != RC_e::SUCCESS){
        Debug("Error: CleanSubscribers in RegisterRT::RegisterRT()");
    }
}

//=====================================================================================================
RegisterRT::~RegisterRT(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

RC_e RegisterRT::AddSubscriber(Devices_e subscriber){
    // Check subscriber
    if (subscriber >= Devices_e::DEVICE_LENGTH || subscriber < Devices_e::DEVICE_NONE){
        Debug("Error: INVALID_SUBSCRIBER in RegisterRT::AddSubscriber()");
        return RC_e::ERROR_INVALID_SUBSCRIBER;
    }

    // Check if max index is reached
    if (this->m_subscribers_index >= Devices_e::DEVICE_LENGTH){
        Debug("Error: MAX_NUMBER_SUBSCRIBERS in RegisterRT::AddSubscriber()");
        return RC_e::ERROR_MAX_NUMBER_SUBSCRIBERS;
    }

    // Increase index
    this->m_subscribers_index++;

    // Add subscriber
    this->m_subscribers[this->m_subscribers_index] = subscriber;
    
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e RegisterRT::CleanSubscribers(){
    // Iterate through devices
    for (int i=0; i<Devices_e::DEVICE_LENGTH; i++){
        this->m_subscribers[i] = Devices_e::DEVICE_NONE;
    }

    // Init
    this->m_subscribers_index = -1;

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e RegisterRT::EnableDebugMode(){
    this->m_debugMode = 1;
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e RegisterRT::DisableDebugMode(){
    this->m_debugMode = 0;
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

RC_e RegisterRT::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}