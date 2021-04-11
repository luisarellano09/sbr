/**
 * @file Node.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to manage the node
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
RC_e Node::AddRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::AddRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    if ((retCode = this->AddRequest((DEVICE_e)request->nodeId, (COM_REQUEST_TYPE_e)request->reqType, (COM_REQUEST_REG_ID_e)request->regId, request->data)) != RC_e::SUCCESS) {
        Debug("Error: AddRequest in Node::AddRequest()");
        return retCode;
    }
    
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::SendNextRequest(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    Request request;

    if ((retCode = this->m_requestBuffer->ConsumeRequest(&request)) != RC_e::SUCCESS) {
        Debug("Error: ConsumeRequest in Node::SendNextRequest()");
        return retCode;
    }

    if (request.nodeId != DEVICE_e::NONE_DEVICE){
        if ((retCode = this->SendRequest(&request)) != RC_e::SUCCESS) {
            Debug("Error: SendRequest in Node::SendNextRequest()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::ReadNextRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::ReadNextRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check for incomming data
    if (this->m_serial->available()){
        if ((retCode = this->ReadRequest(request)) != RC_e::SUCCESS){
            Debug("Error: ReadRequest in Node::ReadNextRequest()");
            return retCode;
        }
    } else {
        request->nodeId = DEVICE_e::NONE_DEVICE;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::Run(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    if (this->m_start){
        
        Request request;

        // Read Request
        if ((retCode = this->ReadNextRequest(&request)) != RC_e::SUCCESS){
            Debug("Error: ReadNextRequest in Node::Run()");
            return retCode;
        }

        // Check if request was read
        if (request.nodeId != DEVICE_e::NONE_DEVICE) {
            // Check if the NodeId of the request belogns to the device
            if (request.nodeId == NODE_ID){
                if ((retCode = this->HandleRequest(&request)) != RC_e::SUCCESS){
                    Debug("Error: HandleRequest in Node::Run()");
                    return retCode;
                }
            } else {
                if (NODE_ID != DEVICE_e::MANAGER){
                    if ((retCode = this->AddRequest(&request)) != RC_e::SUCCESS){
                        Debug("Error: AddRequest in Node::Run()");
                        return retCode;
                    }
                }
            }
        }

        // Write Request
        if ((retCode = SendNextRequest()) != RC_e::SUCCESS){
            Debug("Error: SendNextRequest in Node::Run()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::Start(){
    this->m_start = true;
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::Stop(){
    this->m_start = false;
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::PrintBuffer(){
    // Check if array is null
    if (this->m_requestBuffer == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::PrintBuffer()");
        return RC_e::ERROR_NULL_POINTER;
    }

    this->m_requestBuffer->PrintBuffer();

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

//=====================================================================================================
RC_e Node::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e Node::ConfigureSerial(uint32_t baud, uint8_t RX, uint8_t TX){

    // Config Pins
    pinMode(RX, PULLUP);
    pinMode(TX, PULLUP);

    // Begin serial
    this->m_serial->begin(baud, SERIAL_8N1, RX, TX);

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Node::SendRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::SendRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Buffer
    uint8_t _buffer[NODE_REQUEST_SIZE] = {0};;

    // Convert request to buffer  
    if ((retCode = RequestToBuffer(request, _buffer)) != RC_e::SUCCESS){
        Debug("Error: RequestToBuffer in Node::SendRequest()");
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
        Debug("Error: ERROR_NULL_POINTER in Node::ReadRequest()");
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
        Debug("Error: CheckCRC in Node::ReadRequest()");
        return RC_e::ERROR_CRC;
    }

    return RC_e::SUCCESS;
}

