/**
 * @file TableRegister.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe the Data Table
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "./TableRegister.h"

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

TableRegister::TableRegister(Node* NodeESP32, Node* NodeLinux){
    // Check if the pointer is null
    if (NodeESP32 == NULL){
        Debug("Error: NodeESP32 is NULL_POINTER in TableRegister::TableRegister()");
    }

    // Check if the pointer is null
    if (NodeLinux == NULL){
        Debug("Error: NodeLinux NULL_POINTER in TableRegister::TableRegister()");
    }

    this->m_NodeESP32 = NodeESP32;
    this->m_NodeLinux = NodeLinux;

    // Clean all registers
    if (CleanRegisters() != RC_e::SUCCESS){
        Debug("Error: CleanRegisters in TableRegister::TableRegister()");
    }
}

//=====================================================================================================
TableRegister::~TableRegister(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e TableRegister::AddSubscriber(COM_REQUEST_REG_ID_e regId, DEVICE_e subscriber){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check Register
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Debug("Error: INVALID_REG_ID in TableRegister::AddSubscriber()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Check subscriber
    if (subscriber >= DEVICE_e::LENGTH_DEVICE || subscriber < DEVICE_e::NONE_DEVICE){
        Debug("Error: INVALID_SUBSCRIBER in TableRegister::AddSubscriber()");
        return RC_e::ERROR_INVALID_SUBSCRIBER;
    }

    // Add subscriber
    if ((retCode = this->m_registers[regId].AddSubscriber(subscriber)) != RC_e::SUCCESS){
        Debug("Error: AddSubscriber in TableRegister::AddSubscriber()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRegister::UpdateRegister(COM_REQUEST_REG_ID_e regId, int32_t data){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check Register
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Debug("Error: INVALID_REG_ID in TableRegister::UpdateRegister()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Update value
    this->m_registers[regId].m_value = data;

    // Add request to subscribers
    if ((retCode = this->AddRequestToSubscribers(regId, data)) != RC_e::SUCCESS){
        Debug("Error: AddRequestToSubscribers in TableRegister::UpdateRegister()");
        return retCode;
    }

    return RC_e::SUCCESS;
}


//=====================================================================================================
RC_e TableRegister::HandleRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::ERROR;
    
    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in TableRegister::HandleRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    if (request->regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || request->regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Debug("Error: ERROR_INVALID_REG_ID in TableRegister::HandleRequest()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Types of Request from the Slave
    if (request->reqType == COM_REQUEST_TYPE_e::WRITE){
        // Update Register
        if ((retCode = this->UpdateRegister((COM_REQUEST_REG_ID_e)request->regId, request->data)) != RC_e::SUCCESS){
            Debug("Error: UpdateRegister in TableRegister::HandleRequest()");
            return retCode;
        }
    } else if (request->reqType == COM_REQUEST_TYPE_e::READ){
        //TODO implement read request
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRegister::AddRequestToSubscribers(COM_REQUEST_REG_ID_e regId, int32_t data){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check Register
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Debug("Error: INVALID_REG_ID in TableRegister::AddRequestToSubscribers()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Iterate through devices
    for (int i=0; i<DEVICE_e::LENGTH_DEVICE; i++){
        // Get subscriber
        DEVICE_e subscriber = this->m_registers[(COM_REQUEST_REG_ID_e)regId].m_subscribers[i];

        // Select the devices
        if (subscriber == DEVICE_e::LINUX){
            if ((retCode = this->m_NodeLinux->AddRequest((DEVICE_e)subscriber, COM_REQUEST_TYPE_e::WRITE, (COM_REQUEST_REG_ID_e)regId, data)) != RC_e::SUCCESS){
                Debug("Error: AddRequest in TableRegister::AddRequestToSubscribers()");
                return retCode;
            }
        } else if (subscriber>DEVICE_e::NONE_DEVICE || subscriber<=DEVICE_e::BROADCAST_ESP32){
            if ((retCode = this->m_NodeESP32->AddRequest((DEVICE_e)subscriber, COM_REQUEST_TYPE_e::WRITE, (COM_REQUEST_REG_ID_e)regId, data)) != RC_e::SUCCESS){
                Debug("Error: AddRequest in TableRegister::AddRequestToSubscribers()");
                return retCode;
            }
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRegister::Print(COM_REQUEST_REG_ID_e regId){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check Register
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Debug("Error: INVALID_REG_ID in TableRegister::Print()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    if ((retCode = this->m_registers[regId].Print(regId)) != RC_e::SUCCESS){
        Debug("Error: Print in TableRegister::Print()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRegister::PrintTable(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    for (uint16_t i=(COM_REQUEST_REG_ID_e::NONE_REG_ID+1); i<COM_REQUEST_REG_ID_e::LENGTH_REG_ID; i++){
        if ((retCode = this->m_registers[i].Print((COM_REQUEST_REG_ID_e)i)) != RC_e::SUCCESS){
            Debug("Error: Print in TableRegister::PrintTable()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRegister::EnableDebugMode(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_debugMode = true;

    // Iterate all registers
    for (uint16_t i=0; i<COM_REQUEST_REG_ID_e::LENGTH_REG_ID; i++){
        if ((retCode = this->m_registers[i].EnableDebugMode()) != RC_e::SUCCESS){
            Debug("Error: EnableDebugMode in TableRegister::EnableDebugMode()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRegister::DisableDebugMode(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_debugMode = false;

    // Iterate all registers
    for (uint16_t i=0; i<COM_REQUEST_REG_ID_e::LENGTH_REG_ID; i++){
        if ((retCode = this->m_registers[i].DisableDebugMode()) != RC_e::SUCCESS){
            Debug("Error: DisableDebugMode in TableRegister::DisableDebugMode()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e TableRegister::CleanRegisters(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Iterate all registers
    for (uint16_t i=0; i<COM_REQUEST_REG_ID_e::LENGTH_REG_ID; i++){
        if ((retCode = this->m_registers[i].Clean()) != RC_e::SUCCESS){
            Debug("Error: Clean in TableRegister::CleanRegisters()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e TableRegister::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}