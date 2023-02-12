/**
 * @file NodeEsp32.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the NodeEsp32
 * @version 1.0
 * @date 16.10.2022
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
    return RC_e::SUCCESS;
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

    // Handle request in table Register
    if ((retCode = this->m_tableRegister->HandleRequest(request)) != RC_e::SUCCESS){
        Log.fatalln("[NodeEsp32::HandleRequest] Error in HandleRequest()");
        return retCode;
    }
    
    return retCode;
}

