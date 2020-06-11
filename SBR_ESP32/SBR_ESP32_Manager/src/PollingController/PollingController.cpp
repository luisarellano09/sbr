/**
 * \file PollingController.cpp
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 08 Jun 2020
 *
 * \brief Class to describe a register of the Data Table in Runtime.
 *
 * 
 * 
 * Changes
 * 07.06.2020: Create Class.
 * 
 *
 */


/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "./PollingController.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/
PollingController::PollingController(SPI_MasterManager* spiMasterManager){

    // Check if the pointers is null
    if (spiMasterManager != NULL){
        m_spiMasterManager = spiMasterManager;
    }

    m_currentStateEsp32Polling = StateEsp32Polling::IDLE;
    m_nextStateEsp32Polling = StateEsp32Polling::IDLE;
    m_commandEsp32Polling = CommandEsp32Polling::ESP32_POLLING_STOP;
}

PollingController::~PollingController(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

RC_e PollingController::RunESP32(){
    SM_Esp32Polling();
    return RC_e::SUCCESS;
}

RC_e PollingController::StartEsp32Polling(){
    m_commandEsp32Polling = CommandEsp32Polling::ESP32_POLLING_START;
    return RC_e::SUCCESS;
}

RC_e PollingController::StopEsp32Polling(){
    m_commandEsp32Polling = CommandEsp32Polling::ESP32_POLLING_STOP;
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

RC_e PollingController::SM_Esp32Polling(){

    // Check if the pointers is null
    if (m_spiMasterManager == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if the command is STOP
    if (m_commandEsp32Polling == CommandEsp32Polling::ESP32_POLLING_STOP){
        m_nextStateEsp32Polling = StateEsp32Polling::IDLE;
    }

    // Update current state
    m_currentStateEsp32Polling = m_nextStateEsp32Polling;

    // State Machine
    switch (m_currentStateEsp32Polling)
    {
        case StateEsp32Polling::IDLE:
            // Condition next step
            if(m_commandEsp32Polling == CommandEsp32Polling::ESP32_POLLING_START){
                m_nextStateEsp32Polling = StateEsp32Polling::SEND_REQ;
            }
            break;

        case StateEsp32Polling::SEND_REQ:
            // Send request to slaves
            for(auto i=0; i<ESP32_Slave_e::SLAVE_LENGTH; i++){
                m_spiMasterManager->SendWriteRequests((ESP32_Slave_e)i);
            }

            // Next step
            m_nextStateEsp32Polling = StateEsp32Polling::RECV_REQ;
            break;

        case StateEsp32Polling::RECV_REQ:
            // Recieve request to slaves
            for(auto i=0; i<ESP32_Slave_e::SLAVE_LENGTH; i++){
                m_spiMasterManager->ReadSlaveRequests((ESP32_Slave_e)i);
            }

            // Next step
            m_nextStateEsp32Polling = StateEsp32Polling::SEND_REQ;
            break;

    }

    delay(1);

    return RC_e::SUCCESS;
}