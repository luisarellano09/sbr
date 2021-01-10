/**
 * @file TableRT.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe the Data Table in Runtime
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "./TableRT.h"

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

TableRT::TableRT(){
    // Clean all registers
    if (CleanRegisters() != RC_e::SUCCESS){
        Debug("Error: CleanRegisters in TableRT::TableRT()");
    }
}

//=====================================================================================================
TableRT::~TableRT(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e TableRT::AddSubscriber(COM_REQUEST_REG_ID_e regID, Devices_e subscriber){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check Register
    if (regID >= COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH || regID < COM_REQUEST_REG_ID_e::REQUEST_INITIAL_RED_ID){
        Debug("Error: INVALID_REG_ID in TableRT::AddSubscriber()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Check subscriber
    if (subscriber >= Devices_e::DEVICE_LENGTH || subscriber < Devices_e::DEVICE_NONE){
        Debug("Error: INVALID_SUBSCRIBER in TableRT::AddSubscriber()");
        return RC_e::ERROR_INVALID_SUBSCRIBER;
    }

    // Add subscriber
    if ((retCode = this->m_Registers[regID].AddSubscriber(subscriber)) != RC_e::SUCCESS){
        Debug("Error: AddSubscriber in TableRT::AddSubscriber()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRT::UpdateRegister(COM_REQUEST_REG_ID_e regID, int32_t data){
    // Check Register
    if (regID >= COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH || regID < COM_REQUEST_REG_ID_e::REQUEST_INITIAL_RED_ID){
        Debug("Error: INVALID_REG_ID in TableRT::UpdateRegister()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Update value
    this->m_Registers[regID].m_value = data;

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRT::EnableDebugMode(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_debugMode = true;

    // Iterate all registers
    for (int i=0; i<COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH; i++){
        if ((retCode = this->m_Registers[i].EnableDebugMode()) != RC_e::SUCCESS){
            Debug("Error: EnableDebugMode in TableRT::EnableDebugMode()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRT::DisableDebugMode(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_debugMode = false;

    // Iterate all registers
    for (int i=0; i<COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH; i++){
        if ((retCode = this->m_Registers[i].DisableDebugMode()) != RC_e::SUCCESS){
            Debug("Error: DisableDebugMode in TableRT::DisableDebugMode()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e TableRT::CleanRegisters(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Iterate all registers
    for (int i=0; i<COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH; i++){
        // Clean subscribers
        if ((retCode = this->m_Registers[i].CleanSubscribers()) != RC_e::SUCCESS){
            Debug("Error: CleanSubscribers in TableRT::CleanRegisters()");
            return retCode;
        }

        this->m_Registers[i].m_value = 0;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRT::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}