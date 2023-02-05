/**
 * @file Node.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to manage the communication node
 * @version 1.0
 * @date 10.09.2022
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

    // Instanciate and connect objects
    this->m_requestBuffer = new RequestBuffer();
    this->m_serial = serial;

    // Configure Serial port 
    this->ConfigureSerial(baud, RX, TX);
}

//=====================================================================================================
Node::~Node(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e Node::AddRequest(DEVICE_e nodeId, COM_REQUEST_TYPE_e reqType, COM_REQUEST_REG_ID_e regId, uint32_t data){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if Register ID is in range
    if (regId >= COM_REQUEST_REG_ID_e::LENGTH_REG_ID || regId <= COM_REQUEST_REG_ID_e::NONE_REG_ID){
        Debug("Error: ERROR_INVALID_REG_ID in Node::AddRequest()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Add request to Request-Buffer
    if ((retCode = this->m_requestBuffer->AddRequest(nodeId, reqType, regId, data)) != RC_e::SUCCESS) {
        Debug("Error: m_requestBuffer.AddRequest(...) in Node::AddRequest()");
        return retCode;
    }
    
    return retCode;
}

//=====================================================================================================
RC_e Node::AddRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::AddRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Add Request
    if ((retCode = this->AddRequest((DEVICE_e)request->nodeId, (COM_REQUEST_TYPE_e)request->reqType, (COM_REQUEST_REG_ID_e)request->regId, request->data)) != RC_e::SUCCESS) {
        Debug("Error: AddRequest(...) in Node::AddRequest()");
        return retCode;
    }
    
    return retCode;
}

//=====================================================================================================
RC_e Node::SendNextRequest(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Temp request
    Request tempRequest;

    // Consume a Request from the Request-Buffer
    if ((retCode = this->m_requestBuffer->ConsumeRequest(&tempRequest)) != RC_e::SUCCESS) {
        Debug("Error: m_requestBuffer.ConsumeRequest(...) in Node::SendNextRequest()");
        return retCode;
    }

    // Check if the ID is not NONE_DEVICE
    if (tempRequest.nodeId != DEVICE_e::NONE_DEVICE){
        // Send Request
        if ((retCode = this->SendRequest(&tempRequest)) != RC_e::SUCCESS) {
            Debug("Error: SendRequest(...) in Node::SendNextRequest()");
            return retCode;
        }
    }
    
    return retCode;
}

//=====================================================================================================
RC_e Node::ReadNextRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::ReadNextRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check for incomming data is available
    if (this->m_serial->available()){
        // Read Request
        if ((retCode = this->ReadRequest(request)) != RC_e::SUCCESS){
            Debug("Error: ReadRequest(...) in Node::ReadNextRequest()");
            return retCode;
        }
    } else {
        request->nodeId = DEVICE_e::NONE_DEVICE;
    }

    return retCode;
}

//=====================================================================================================
RC_e Node::Run(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    if (this->m_start){
        
        // Temp request
        Request tempRequest;

        // Read Request
        if ((retCode = this->ReadNextRequest(&tempRequest)) != RC_e::SUCCESS){
            Debug("Error: ReadNextRequest(...) in Node::Run()");
            return retCode;
        }

        // Check if request was read
        if (tempRequest.nodeId != DEVICE_e::NONE_DEVICE) {
            // Check if the NodeId of the request belogns to the device
            if (tempRequest.nodeId == NODE_ID){
                // Call Request Handler
                if ((retCode = this->HandleRequest(&tempRequest)) != RC_e::SUCCESS){
                    Debug("Error: HandleRequest(...) in Node::Run()");
                    return retCode;
                }
            } else {
                // Check if the node is not the Manager
                if (NODE_ID != DEVICE_e::MANAGER){
                    // Add the request to the buffer
                    if ((retCode = this->AddRequest(&tempRequest)) != RC_e::SUCCESS){
                        Debug("Error: AddRequest(...) in Node::Run()");
                        return retCode;
                    }
                }
            }
        }

        // Write Request
        if ((retCode = SendNextRequest()) != RC_e::SUCCESS){
            Debug("Error: SendNextRequest() in Node::Run()");
            return retCode;
        }
    }

    return retCode;
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
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if array is null
    if (this->m_requestBuffer == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::PrintBuffer()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Print 
    if ((retCode = this->m_requestBuffer->PrintBuffer()) != RC_e::SUCCESS){
        Debug("Error: m_requestBuffer->PrintBuffer() in Node::PrintBuffer()");
        return retCode;
    }

    return retCode;
}  

//=====================================================================================================
RC_e Node::EnableDebugMode(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Set to true
    this->m_debugMode = true;

    // Enable Debug mode to lower levels
    if ((retCode = this->m_requestBuffer->EnableDebugMode()) != RC_e::SUCCESS){
        Debug("Error: m_requestBuffer->EnableDebugMode() in Node::EnableDebugMode()");
        return retCode;
    }

    return retCode;
}

//=====================================================================================================
RC_e Node::DisableDebugMode(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Set to false
    this->m_debugMode = false;

    // Disable Debug mode to lower levels
    if ((retCode = this->m_requestBuffer->DisableDebugMode()) != RC_e::SUCCESS){
        Debug("Error: m_requestBuffer->DisableDebugMode() in Node::DisableDebugMode()");
        return retCode;
    }

    return retCode;
}

//=====================================================================================================
RC_e Node::Debug(char* msg){
    // Check if Debug mode is active
    if (this->m_debugMode){
        // Print message
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
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::SendRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Char-Buffer
    uint8_t _buffer[NODE_REQUEST_SIZE] = {0};;

    // Convert request to Char-Buffer  
    if ((retCode = RequestToBuffer(request, _buffer)) != RC_e::SUCCESS){
        Debug("Error: RequestToBuffer in Node::SendRequest()");
        return retCode;
    }
    
    // Send Request
    this->m_serial->write(_buffer, NODE_REQUEST_SIZE);

    return retCode;
}

//=====================================================================================================
RC_e Node::ReadRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in Node::ReadRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Char-Buffer
    uint8_t _buffer[NODE_REQUEST_SIZE] = {0};

    // Read request
    this->m_serial->readBytes(_buffer, NODE_REQUEST_SIZE);
    
    // Convert Char-Buffer to request
    if ((retCode = BufferToRequest(_buffer, request)) != RC_e::SUCCESS){
        Debug("Error: BufferToRequest in Node::ReadRequest()");
        return retCode;
    }

    // Check CRC
    if (!CheckCRC(request)){
        Debug("Error: CheckCRC in Node::ReadRequest()");
        return RC_e::ERROR_CRC;
    }

    return retCode;
}

