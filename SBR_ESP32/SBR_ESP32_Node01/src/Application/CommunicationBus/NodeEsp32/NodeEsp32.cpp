/**
 * @file Node01.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the Node
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

RC_e NodeEsp32::UpdateRegister(COM_REQUEST_REG_ID_e regId, int32_t data){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check register ID validity
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Log.fatalln("[NodeEsp32::UpdateRegister] redId ERROR_INVALID_REG_ID");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    Log.traceln("[NodeEsp32::UpdateRegister] Sending update register: [%u]=%d", regId, data);

    // Add request to manager
    if ((retCode = this->AddRequest(DEVICE_e::NODE_MANAGER, COM_REQUEST_TYPE_e::REQUEST_WRITE, regId, data)) != RC_e::SUCCESS){
        Log.errorln("[NodeEsp32::UpdateRegister] Error in AddRequest()");
        return retCode;
    }

    Log.traceln("[NodeEsp32::UpdateRegister] Register update sent");

    return retCode;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e NodeEsp32::HandleRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (request == NULL){
        Log.fatalln("[NodeEsp32::HandleRequest] request ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    Log.traceln("[NodeEsp32::HandleRequest] Request received: nodeId=%d, reqType=%d, regId=%d, data=%d, CRC=%d", request->nodeId, request->reqType, request->regId, request->data, request->CRC);

    // Check if the function is null
    if (this->ExtHandler == NULL){
        Log.fatalln("[NodeEsp32::HandleRequest] ExtHandler ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    if ((retCode = this->ExtHandler(request)) != RC_e::SUCCESS){
        Log.errorln("[NodeEsp32::HandleRequest] Error in ExtHandler()");
        return retCode;
    }

    return retCode;
}

