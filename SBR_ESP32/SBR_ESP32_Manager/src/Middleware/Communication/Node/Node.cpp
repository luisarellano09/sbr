/**
 * @file Node.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief class to Manage the nodes
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */


/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Node.h"
#include "../Utility/Utility.h"

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

Node::Node(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX){    
    // Check if the pointer is null
    if (serial == NULL){
        Debug("Error: serial NULL_POINTER in Node::Node()");
    }

    this->m_requestBuffer = new RequestBuffer();
    this->m_serial = serial;

    this->ConfigureSerial(baud, RX, TX);
}

//=====================================================================================================
Node::~Node(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e Node::AddRequest(DEVICE_e nodeId, COM_REQUEST_TYPE_e reqType, COM_REQUEST_REG_ID_e regId, uint32_t data){
    // Result code
    RC_e retCode = RC_e::ERROR;

    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Debug("Error: ERROR_INVALID_REG_ID in Node::AddRequest()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    if ((retCode = this->m_requestBuffer->AddRequest(nodeId, reqType, regId, data)) != RC_e::SUCCESS) {
        Debug("Error: AddRequest in Node::AddRequest()");
        return retCode;
    }
    
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::AddRequest(Request request){
    // Result code
    RC_e retCode = RC_e::ERROR;

    if ((retCode = this->AddRequest((DEVICE_e)request.nodeId, (COM_REQUEST_TYPE_e)request.reqType, (COM_REQUEST_REG_ID_e)request.regId, request.data)) != RC_e::SUCCESS) {
        Debug("Error: AddRequest in Node::AddRequest()");
        return retCode;
    }
    
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::SendNextRequest(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    Request* request = new Request();

    if ((retCode = this->m_requestBuffer->ConsumeRequest(request)) != RC_e::SUCCESS) {
        Debug("Error: ConsumeRequest in Node::SendNextRequest()");
        return retCode;
    }

    if (request != NULL){
        this->SendRequest(*request);
    }
    
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::Listen(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    if (this->m_serial->available()){
        Request request;
        if ((retCode = this->ReadNextRequest(&request)) == RC_e::SUCCESS){
            this->HandleRequest(&request);
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::PrintBuffer(){
    // Check if array is null
    if (this->m_requestBuffer == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::PrintBuffer()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Iterate through the requests
    m_requestBuffer->PrintBuffer();

    return RC_e::SUCCESS;
}  

//=====================================================================================================
RC_e Node::EnableDebugMode(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_debugMode = true;

    if ((retCode = this->m_requestBuffer->EnableDebugMode()) != RC_e::SUCCESS){
        Debug("Error: EnableDebugMode in Node::EnableDebugMode()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::DisableDebugMode(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_debugMode = false;

    if ((retCode = this->m_requestBuffer->DisableDebugMode()) != RC_e::SUCCESS){
        Debug("Error: DisableDebugMode in Node::DisableDebugMode()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e Node::ConfigureSerial(uint32_t baud, uint8_t RX, uint8_t TX){

    pinMode(RX, PULLUP);
    pinMode(TX, PULLUP);

    // Begin serial
    this->m_serial->begin(baud, SERIAL_8N1, RX, TX);

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::SendRequest(Request request){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Buffer
    uint8_t _buffer[NODE_REQUEST_SIZE] = {0};;

    // Convert request to buffer  
    if ((retCode = RequestToBuffer(&request, _buffer)) != RC_e::SUCCESS){
        Debug("Error: RequestToBuffer in Node::SPI_SendWriteRequest()");
        return retCode;
    }
    
    // Send Request
    this->m_serial->write(_buffer, NODE_REQUEST_SIZE);

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::ReadRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::SPI_ReadSlaveRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Buffer
    uint8_t _buffer[NODE_REQUEST_SIZE] = {0};

    // Read request
    this->m_serial->readBytes(_buffer, NODE_REQUEST_SIZE);
    
    // Convert buffer to request
    if ((retCode = BufferToRequest(_buffer, request)) != RC_e::SUCCESS){
        Debug("Error: BufferToRequest in Node::ReadRequest()");
        return retCode;
    }

    // Check CRC
    if (!CheckCRC(request)){
        Debug("Error: CalculateCrcFromRequest in Node::ReadRequest()");
        return RC_e::ERROR_CRC;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::ReadNextRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::ERROR;

    if ((retCode = this->ReadRequest(request)) != RC_e::SUCCESS) {
        Debug("Error: ReadRequest in Node::ReadNextRequest()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}