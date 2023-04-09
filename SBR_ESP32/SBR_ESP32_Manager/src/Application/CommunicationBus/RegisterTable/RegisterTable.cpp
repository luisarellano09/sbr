/**
 * @file RegisterTable.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe the Data Table
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "RegisterTable.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

RegisterTable::RegisterTable(Node* NodeESP32, Node* NodeLinux){
    // Check if the pointer is null
    if (NodeESP32 == NULL){
        Log.fatalln("[RegisterTable::RegisterTable] NodeESP32 NULL_POINTER");
        return;
    }

    // Check if the pointer is null
    if (NodeLinux == NULL){
        Log.fatalln("[RegisterTable::RegisterTable] NodeLinux NULL_POINTER");
        return;
    }

    this->m_NodeESP32 = NodeESP32;
    this->m_NodeLinux = NodeLinux;

    // Clean all registers
    if (CleanRegisters() != RC_e::SUCCESS){
        Log.errorln("[RegisterTable::RegisterTable] Error in CleanRegisters()");
    }

    Log.traceln("[RegisterTable::RegisterTable] RegisterTable initialization finished");
}


//=====================================================================================================

RegisterTable::~RegisterTable(){}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e RegisterTable::AddSubscriber(COM_REQUEST_REG_ID_e regId, DEVICE_e subscriber){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check Register
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Log.fatalln("[RegisterTable::AddSubscriber] regId ERROR_INVALID_REG_ID");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Check subscriber
    if (subscriber >= DEVICE_e::LENGTH_DEVICE || subscriber < DEVICE_e::NONE_DEVICE){
        Log.fatalln("[RegisterTable::AddSubscriber] subscriber ERROR_INVALID_SUBSCRIBER");
        return RC_e::ERROR_INVALID_SUBSCRIBER;
    }

    // Add subscriber
    if ((retCode = this->m_registers[regId].AddSubscriber(subscriber)) != RC_e::SUCCESS){
        Log.errorln("[RegisterTable::AddSubscriber] Error in AddSubscriber()");
        return retCode;
    }

    Log.traceln("[RegisterTable::AddSubscriber] Subscriber added Subscriber[%d]->Register[%d]", subscriber, regId);

    return retCode;
}


//=====================================================================================================

RC_e RegisterTable::UpdateRegister(COM_REQUEST_REG_ID_e regId, int32_t data){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check register ID validity
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Log.fatalln("[RegisterTable::UpdateRegister] regId ERROR_INVALID_REG_ID");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Update value
    this->m_registers[regId].m_value = data;

    // Add request to subscribers
    if ((retCode = this->AddRequestToSubscribers(regId, data)) != RC_e::SUCCESS){
        Log.errorln("[RegisterTable::UpdateRegister] Error in AddRequestToSubscribers()");
        return retCode;
    }

    Log.traceln("[RegisterTable::UpdateRegister] Register updated: [%u]=%d", regId, data);

    return retCode;
}


//=====================================================================================================

RC_e RegisterTable::HandleRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::SUCCESS;
    
    // Check if the pointer is null
    if (request == NULL){
        Log.fatalln("[RegisterTable::HandleRequest] request ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check register ID validity
    if (request->regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || request->regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Log.fatalln("[RegisterTable::HandleRequest] regId ERROR_INVALID_REG_ID");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    Log.traceln("[RegisterTable::HandleRequest] Request received: nodeId=%d, reqType=%d, regId=%d, data=%d, CRC=%d", request->nodeId, request->reqType, request->regId, request->data, request->CRC);

    // Evaluate type of Request from node
    if (request->reqType == COM_REQUEST_TYPE_e::REQUEST_WRITE){
        // Update Register
        if ((retCode = this->UpdateRegister((COM_REQUEST_REG_ID_e)request->regId, request->data)) != RC_e::SUCCESS){
            Log.errorln("[RegisterTable::HandleRequest] Error in UpdateRegister()");
            return retCode;
        }
    } else if (request->reqType == COM_REQUEST_TYPE_e::REQUEST_READ){
        //ToDo implement read request
    }

    Log.traceln("[RegisterTable::HandleRequest] Request handled");

    return retCode;
}


//=====================================================================================================

RC_e RegisterTable::AddRequestToSubscribers(COM_REQUEST_REG_ID_e regId, int32_t data){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check register ID validity
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Log.fatalln("[RegisterTable::AddRequestToSubscribers] regId ERROR_INVALID_REG_ID");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Iterate through devices
    for (int i=0; i<DEVICE_e::LENGTH_DEVICE; i++){
        // Get subscriber
        DEVICE_e subscriber = this->m_registers[(COM_REQUEST_REG_ID_e)regId].m_subscribers[i];

        // Select the device to add the request
        if (subscriber == DEVICE_e::LINUX){

            Log.traceln("[RegisterTable::AddRequestToSubscribers] Adding request to Linux Node: [%u]=%d", regId, data);

            if ((retCode = this->m_NodeLinux->AddRequest((DEVICE_e)subscriber, COM_REQUEST_TYPE_e::REQUEST_WRITE, (COM_REQUEST_REG_ID_e)regId, data)) != RC_e::SUCCESS){
                Log.errorln("[RegisterTable::AddRequestToSubscribers] Error in AddRequest()");
                return retCode;
            }

            Log.traceln("[RegisterTable::AddRequestToSubscribers] Request added Linux Node");

        } else if (subscriber>DEVICE_e::NONE_DEVICE || subscriber<DEVICE_e::LINUX){

            Log.traceln("[RegisterTable::AddRequestToSubscribers] Adding request to ESP32 Node[%u]: [%u]=%d", subscriber, regId, data);
            
            if ((retCode = this->m_NodeESP32->AddRequest((DEVICE_e)subscriber, COM_REQUEST_TYPE_e::REQUEST_WRITE, (COM_REQUEST_REG_ID_e)regId, data)) != RC_e::SUCCESS){
                Log.errorln("[RegisterTable::AddRequestToSubscribers] Error in AddRequest()");
                return retCode;
            }
            
            Log.traceln("[RegisterTable::AddRequestToSubscribers] Request added to ESP32 Node[%u]", subscriber);
        }
    }

    return retCode;
}


//=====================================================================================================

RC_e RegisterTable::PrintRegister(COM_REQUEST_REG_ID_e regId){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check register ID validity
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Log.fatalln("[RegisterTable::PrintRegister] redId ERROR_INVALID_REG_ID");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Print register
    if ((retCode = this->m_registers[regId].Print(regId)) != RC_e::SUCCESS){
        Log.errorln("[RegisterTable::PrintRegister] Error in Print()");
        return retCode;
    }

    Log.traceln("[RegisterTable::PrintRegister] Register printed");

    return retCode;
}


//=====================================================================================================

RC_e RegisterTable::PrintTable(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Iterate through registers
    for (uint16_t i=(COM_REQUEST_REG_ID_e::NONE_REG_ID+1); i<COM_REQUEST_REG_ID_e::LENGTH_REG_ID; i++){
        // Print register
        if ((retCode = this->m_registers[i].Print((COM_REQUEST_REG_ID_e)i)) != RC_e::SUCCESS){
            Log.errorln("[RegisterTable::PrintTable] Error in Print()");
            return retCode;
        }
    }

    Log.traceln("[RegisterTable::PrintTable] Table printed");

    return retCode;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e RegisterTable::CleanRegisters(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Iterate all registers
    for (uint16_t i=0; i<COM_REQUEST_REG_ID_e::LENGTH_REG_ID; i++){
        // Clean register
        if ((retCode = this->m_registers[i].Clean()) != RC_e::SUCCESS){
            Log.errorln("[RegisterTable::CleanRegisters] Error in Clean()");
            return retCode;
        }
    }

    Log.traceln("[RegisterTable::CleanRegisters] Registers cleaned");

    return retCode;
}
