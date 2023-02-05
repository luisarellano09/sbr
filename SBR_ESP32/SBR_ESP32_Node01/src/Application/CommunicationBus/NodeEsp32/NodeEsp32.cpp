/**
 * @file Node01.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the Node
 * @version 1.0
 * @date 16.10.2022
 * 
 * 
 */


/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "NodeEsp32.h"

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
        Debug("Error: INVALID_REG_ID in NodeEsp32::UpdateRegister()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Add request to manager
    if ((retCode = this->AddRequest(DEVICE_e::MANAGER, COM_REQUEST_TYPE_e::WRITE, regId, data)) != RC_e::SUCCESS){
        Debug("Error: this->AddRequest(...) in NodeEsp32::UpdateRegister()");
        return retCode;
    }

    return retCode;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e NodeEsp32::HandleRequest(Request* request){

    request->Print();
    return RC_e::SUCCESS;

}

