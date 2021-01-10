/**
 * @file PollingController.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to control the polling of communication.
 * @version 2.0
 * @date 09.01.2021
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "PollingController.h"

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

PollingController::PollingController(SPI_MasterManager* spiMasterManager){

    // Check if the pointer is null
    if (spiMasterManager != NULL){
        this->m_spiMasterManager = spiMasterManager;
    } else {
        Debug("Error: spiMasterManager is NULL in PollingController::PollingController()");
    }

    // Init
    this->m_currentStatePolling = StatePolling::IDLE;
    this->m_nextStatePolling = StatePolling::IDLE;
    this->m_commandPolling = CommandPolling::STOP_POLLING;
}

//=====================================================================================================
PollingController::~PollingController(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e PollingController::Run(){

    // Result code
    RC_e retCode = RC_e::ERROR;

    // Call State Machine
    if((retCode = SM_Polling()) != RC_e::SUCCESS){
        Debug("Error: SM_Polling in PollingController::Run()");
        return retCode;
    }
    
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e PollingController::StartPolling(){
    this->m_commandPolling = CommandPolling::START_POLLING;
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e PollingController::StopPolling(){
    this->m_commandPolling = CommandPolling::STOP_POLLING;
    return RC_e::SUCCESS;
}

//=====================================================================================================
StatePolling PollingController::GetPollingControllerState(){
    return this->m_currentStatePolling;
}

//=====================================================================================================
RC_e PollingController::EnableDebugMode(){
    this->m_debugMode = true;
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e PollingController::DisableDebugMode(){
    this->m_debugMode = false;
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e PollingController::SM_Polling(){

    // Check if the pointer is null
    if (this->m_spiMasterManager == NULL){
        Debug("Error: NULL_POINTER in PollingController::SM_Polling()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if the command is STOP
    if (this->m_commandPolling == CommandPolling::STOP_POLLING){
        this->m_nextStatePolling = StatePolling::IDLE;
    }

    // Update current state
    this->m_currentStatePolling = this->m_nextStatePolling;

    // State Machine
    switch (this->m_currentStatePolling)
    {
        case StatePolling::IDLE:
            // Condition next step
            if (this->m_commandPolling == CommandPolling::START_POLLING){
                this->m_nextStatePolling = StatePolling::RECV_REQ;
            }
            break;

        case StatePolling::RECV_REQ:
            // Recieve request from slaves
            for (int i=0; i<ESP32_SPI_Slave_e::SLAVE_LENGTH; i++){
                if (this->m_spiMasterManager->ReadSlaveRequests((ESP32_SPI_Slave_e)i) != RC_e::SUCCESS){
                    Debug("Error: ReadSlaveRequests in PollingController::SM_Polling()");
                }
            }

            // Next step
            this->m_nextStatePolling = StatePolling::SEND_REQ;
            break;

        case StatePolling::SEND_REQ:
            // Send request to slaves
            for (int i=0; i<ESP32_SPI_Slave_e::SLAVE_LENGTH; i++){
                if (this->m_spiMasterManager->SendWriteRequests((ESP32_SPI_Slave_e)i) != RC_e::SUCCESS){
                    Debug("Error: SendWriteRequests in PollingController::SM_Polling()");
                }
            }

            // Next step
            this->m_nextStatePolling = StatePolling::DONE;
            break;
        
        case StatePolling::DONE:
            // Next step
            this->m_nextStatePolling = StatePolling::RECV_REQ;
            break;
    }

    delayMicroseconds(100); // ToDo: check

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e PollingController::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}