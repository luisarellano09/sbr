/**
 * @file PollingController.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to control the polling of communication.
 * @version 1.0
 * @date 13-06-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "./PollingController.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

//=====================================================================================================
PollingController::PollingController(SPI_MasterManager* spiMasterManager){

    // Check if the pointer is null
    if (spiMasterManager != NULL){
        this->m_spiMasterManager = spiMasterManager;
    }

    // Init
    this->m_currentStateEsp32Polling = StateEsp32Polling::IDLE;
    this->m_nextStateEsp32Polling = StateEsp32Polling::IDLE;
    this->m_commandEsp32Polling = CommandEsp32Polling::ESP32_POLLING_STOP;
}

//=====================================================================================================
PollingController::~PollingController(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e PollingController::RunESP32(){

    // Result code
    RC_e retCode = RC_e::ERROR;

    // Call State Machine
    if((retCode = SM_Esp32Polling()) != RC_e::SUCCESS){
        return retCode;
    }
    
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e PollingController::StartEsp32Polling(){
    this->m_commandEsp32Polling = CommandEsp32Polling::ESP32_POLLING_START;
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e PollingController::StopEsp32Polling(){
    this->m_commandEsp32Polling = CommandEsp32Polling::ESP32_POLLING_STOP;
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e PollingController::SM_Esp32Polling(){

    // Check if the pointer is null
    if (this->m_spiMasterManager == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if the command is STOP
    if (this->m_commandEsp32Polling == CommandEsp32Polling::ESP32_POLLING_STOP){
        this->m_nextStateEsp32Polling = StateEsp32Polling::IDLE;
    }

    // Update current state
    this->m_currentStateEsp32Polling = this->m_nextStateEsp32Polling;

    // State Machine
    switch (this->m_currentStateEsp32Polling)
    {
        case StateEsp32Polling::IDLE:
            // Condition next step
            if(this->m_commandEsp32Polling == CommandEsp32Polling::ESP32_POLLING_START){
                this->m_nextStateEsp32Polling = StateEsp32Polling::SEND_REQ;
            }
            break;

        case StateEsp32Polling::SEND_REQ:
            // Send request to slaves
            for(auto i=0; i<ESP32_Slave_e::SLAVE_LENGTH; i++){
                this->m_spiMasterManager->SendWriteRequests((ESP32_Slave_e)i);
            }

            // Next step
            this->m_nextStateEsp32Polling = StateEsp32Polling::RECV_REQ;
            break;

        case StateEsp32Polling::RECV_REQ:
            // Recieve request from slaves
            for(auto i=0; i<ESP32_Slave_e::SLAVE_LENGTH; i++){
                this->m_spiMasterManager->ReadSlaveRequests((ESP32_Slave_e)i);
            }

            // Next step
            this->m_nextStateEsp32Polling = StateEsp32Polling::SEND_REQ;
            break;
    }

    delay(1);

    return RC_e::SUCCESS;
}