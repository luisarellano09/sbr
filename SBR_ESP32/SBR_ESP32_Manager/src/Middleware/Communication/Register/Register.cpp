/**
 * @file Register.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a register
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Register.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

Register::Register(){
    // Init
    this->m_value = 0;
    this->m_subscribers_index = -1;

    if (Clean() != RC_e::SUCCESS){
        Debug("Error: Clean in Register::Register()");
    }
}

//=====================================================================================================
Register::~Register(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

RC_e Register::AddSubscriber(DEVICE_e subscriber){
    // Check subscriber
    if (subscriber >= DEVICE_e::LENGTH_DEVICE || subscriber < DEVICE_e::NONE_DEVICE){
        Debug("Error: INVALID_SUBSCRIBER in Register::AddSubscriber()");
        return RC_e::ERROR_INVALID_SUBSCRIBER;
    }

    // Check if max index is reached
    if (this->m_subscribers_index >= DEVICE_e::LENGTH_DEVICE){
        Debug("Error: MAX_NUMBER_SUBSCRIBERS in Register::AddSubscriber()");
        return RC_e::ERROR_MAX_NUMBER_SUBSCRIBERS;
    }

    // Increase index
    this->m_subscribers_index++;

    // Add subscriber
    this->m_subscribers[this->m_subscribers_index] = subscriber;
    
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Register::Clean(){
    
    this->m_value = 0;

    for (int i=0; i<DEVICE_e::LENGTH_DEVICE; i++){
        this->m_subscribers[i] = DEVICE_e::NONE_DEVICE;
    }

    this->m_subscribers_index = -1;

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Register::Print(COM_REQUEST_REG_ID_e regId){

    if (regId==NONE_REG_ID){
        Serial.println("*****************");
    } else {
        Serial.printf("[%d]*****************\r\n", regId);
    }

    Serial.printf("* value: %d\r\n", this->m_value);
    Serial.printf("* number of subscribers: %d\r\n", this->m_subscribers_index);  

    for (int i=0; i<=this->m_subscribers_index; i++){
        Serial.printf("* subs(%d) = %d\r\n", i, this->m_subscribers[this->m_subscribers_index]);
    }
    
    Serial.println("*****************");
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Register::EnableDebugMode(){
    this->m_debugMode = 1;
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Register::DisableDebugMode(){
    this->m_debugMode = 0;
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

RC_e Register::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}