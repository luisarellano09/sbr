/**
 * @file NodeEsp32.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the NodeEsp32
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "NodeEsp32.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

NodeEsp32::NodeEsp32(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX) : Node(serial, baud, RX, TX){    

}


//=====================================================================================================

NodeEsp32::~NodeEsp32(){}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e NodeEsp32::ConnectRegisterTable(RegisterTable* tableRegister){
    this->m_tableRegister = tableRegister;
    Log.traceln("[NodeEsp32::ConnectRegisterTable] Register Table connected");
    return RC_e::SUCCESS;
}


//=====================================================================================================

RC_e NodeEsp32::Run(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Run the node
    Node::Run(COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_ESP32_COUNTER_R);

    // Check WatchDog
    if ( Node::m_internalCounter % NODE_WATCHDOG_TIMEOUT == 0 ) {
        if (Node::m_error == true ) {
            this->m_tableRegister->UpdateRegister(COM_REQUEST_REG_ID_e::STATUS_NODE_ESP32_R, 0);
            Log.errorln("[NodeEsp32::Run] Error in WatchDog");
        } else {
            this->m_tableRegister->UpdateRegister(COM_REQUEST_REG_ID_e::STATUS_NODE_ESP32_R, 1);
        }
    } 

    return retCode;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e NodeEsp32::HandleRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (this->m_tableRegister == NULL){
        Log.fatalln("[NodeEsp32::HandleRequest] m_tableRegister ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if the pointer is null
    if (request == NULL){
        Log.fatalln("[NodeEsp32::HandleRequest] request ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    Log.traceln("[NodeEsp32::HandleRequest] Request received: nodeId=%d, reqType=%d, regId=%d, data=%d, CRC=%d", request->nodeId, request->reqType, request->regId, request->data, request->CRC);

    // Handle request in table Register
    if ((retCode = this->m_tableRegister->HandleRequest(request)) != RC_e::SUCCESS){
        Log.fatalln("[NodeEsp32::HandleRequest] Error in HandleRequest()");
        return retCode;
    }

    // Check if the function is null
    if (this->ExtHandler == NULL){
        Log.fatalln("[NodeEsp32::HandleRequest] ExtHandler ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    if ((retCode = this->ExtHandler(request)) != RC_e::SUCCESS){
        Log.errorln("[NodeEsp32::HandleRequest] Error in ExtHandler()");
        return retCode;
    }

    Log.traceln("[NodeEsp32::HandleRequest] Request handled");
    
    return retCode;
}

