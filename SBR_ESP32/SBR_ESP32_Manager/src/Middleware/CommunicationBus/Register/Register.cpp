/**
 * @file Register.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a register
 * @version 1.0
 * @date 14.09.2022
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Register.h"
#include <ArduinoLog.h>

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

Register::Register(){
    // Init
    this->m_value = 0;
    this->m_subscribers_index = -1;

    if (Clean() != RC_e::SUCCESS){
        Log.errorln("[Register::Register] Error in Clean()");
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
        Log.errorln("[Register::AddSubscriber] subscriber INVALID_SUBSCRIBER");
        return RC_e::ERROR_INVALID_SUBSCRIBER;
    }

    // Check if max index is reached
    if (this->m_subscribers_index >= DEVICE_e::LENGTH_DEVICE){
        Log.errorln("[Register::AddSubscriber] m_subscribers_index MAX_NUMBER_SUBSCRIBERS");
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
    // Init Value
    this->m_value = 0;

    // Loop each subscribed device
    for (int i=0; i<DEVICE_e::LENGTH_DEVICE; i++){
        this->m_subscribers[i] = DEVICE_e::NONE_DEVICE;
    }

    // Init index
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
    Serial.printf("* number of subscribers: %d\r\n", this->m_subscribers_index+1);  

    for (int i=0; i<=this->m_subscribers_index; i++){
        Serial.printf("* subs(%d) = %d\r\n", i+1, this->m_subscribers[this->m_subscribers_index]);
    }
    
    Serial.println("*****************");
    return RC_e::SUCCESS;
}

