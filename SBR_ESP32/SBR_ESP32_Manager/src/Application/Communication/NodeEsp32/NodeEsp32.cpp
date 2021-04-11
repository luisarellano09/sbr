/**
 * @file NodeEsp32.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the NodeEsp32
 * @version 2.0
 * @date 09.01.2021
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

RC_e NodeEsp32::ConnectTableRegister(TableRegister* tableRegister){
    this->m_tableRegister = tableRegister;
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e NodeEsp32::HeartBitMonitoring(){
    // Check if the pointer is null
    if (this->m_tableRegister == NULL){
        Node::Debug("Error: m_tableRegister is NULL_POINTER in NodeEsp32::HeartBitMonitoring()");
        return RC_e::ERROR_NULL_POINTER;
    }

    if (Node::m_start){

        Serial.printf("\r\nSTATUS: %d \t HEART_BIT01: %d \t HEART_BIT02: %d \t ERRORS: %d", 
            this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT_STATUS].m_value,
            this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT01].m_value,
            this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT02].m_value,
            this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT_ERRORS].m_value);

        if (this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT02].m_value == (this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT01].m_value + 1)){
            this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT_STATUS].m_value = 1;
        } else{
            if (this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT01].m_value != 0){
                this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT_STATUS].m_value = 0;
                this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT_ERRORS].m_value++;
            }
        }

        this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT01].m_value++;
        this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT02].m_value = this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT01].m_value;

        Node::AddRequest(DEVICE_e::MANAGER, COM_REQUEST_TYPE_e::WRITE, COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT01, this->m_tableRegister->m_registers[COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT01].m_value);
    }

    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e NodeEsp32::HandleRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if the pointer is null
    if (this->m_tableRegister == NULL){
        Node::Debug("Error: m_tableRegister is NULL_POINTER in NodeEsp32::HandleRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if the pointer is null
    if (request == NULL){
        Node::Debug("Error: request is NULL_POINTER in NodeEsp32::HandleRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    if (request->regId == COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT01){
        if ((retCode = this->m_tableRegister->UpdateRegister(COM_REQUEST_REG_ID_e::NODE_ESP32_HEART_BIT02, request->data + 1)) != RC_e::SUCCESS){
            Debug("Error: UpdateRegister in NodeEsp32::HandleRequest()");
            return retCode;
        }
    } else{
        if ((retCode = this->m_tableRegister->HandleRequest(request)) != RC_e::SUCCESS){
            Debug("Error: HandleRequest in NodeEsp32::HandleRequest()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

