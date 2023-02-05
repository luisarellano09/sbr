/**
 * @file RequestBuffer.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe the Buffer of requests
 * @version 1.0
 * @date 16.10.2022
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "RequestBuffer.h"
#include "../Util/Util.h"

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

RequestBuffer::RequestBuffer(){
    // Clean Buffer
    if (this->CleanBuffer() != RC_e::SUCCESS){
        Debug("Error: CleanBuffer() in RequestBuffer::RequestBuffer()");     
    }
}

//=====================================================================================================
RequestBuffer::~RequestBuffer(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e RequestBuffer::AddRequest(DEVICE_e nodeId, COM_REQUEST_TYPE_e reqType, COM_REQUEST_REG_ID_e regID, uint32_t data){
    // Check if Request-Array is null
    if (this->m_RequestsArray == NULL){
        Debug("Error: ERROR_NULL_POINTER in RequestBuffer::AddRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if max index is reached
    if (this->m_RequestsArrayIndex >= REQUEST_BUFFER_SIZE){
        Debug("Error: MAX_NODE_REQUEST_INDEX in RequestBuffer::AddRequest()");
        return RC_e::ERROR_MAX_NODE_REQUEST_INDEX;
    }

    // Increase index
    this->m_RequestsArrayIndex++;

    // Add request
    this->m_RequestsArray[this->m_RequestsArrayIndex].nodeId = nodeId;
    this->m_RequestsArray[this->m_RequestsArrayIndex].reqType = reqType;
    this->m_RequestsArray[this->m_RequestsArrayIndex].regId = regID;
    this->m_RequestsArray[this->m_RequestsArrayIndex].data = data;
    this->m_RequestsArray[this->m_RequestsArrayIndex].CRC = CalculateCrcFromRequest(&this->m_RequestsArray[this->m_RequestsArrayIndex]);

    return RC_e::SUCCESS;
}  

//=====================================================================================================
RC_e RequestBuffer::AddRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in RequestBuffer::AddRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Add Request
    if ((retCode = this->AddRequest((DEVICE_e)request->nodeId, (COM_REQUEST_TYPE_e)request->reqType, (COM_REQUEST_REG_ID_e)request->regId, request->data)) != RC_e::SUCCESS){
        Debug("Error: AddRequest(...) in RequestBuffer::AddRequest()");
        return retCode;
    }
    return retCode;
}  

//=====================================================================================================
RC_e RequestBuffer::ConsumeRequest(Request* request){
    // Check if index is valid
    if (m_RequestsArrayIndex < 0){
        // Set to NULL the pointer when there is no request
        request->nodeId = DEVICE_e::NONE_DEVICE; 
    } else {
        // Check if the pointer is null
        if (request == NULL){
            Debug("Error: ERROR_NULL_POINTER in RequestBuffer::ConsumeRequest()");
            return RC_e::ERROR_NULL_POINTER;
        }

        // Assign values
        request->nodeId     = this->m_RequestsArray[0].nodeId;
        request->reqType    = this->m_RequestsArray[0].reqType;
        request->regId      = this->m_RequestsArray[0].regId;
        request->data       = this->m_RequestsArray[0].data;
        request->CRC        = this->m_RequestsArray[0].CRC;

        // Move the requests in the buffer
        for (int i=1; i<=m_RequestsArrayIndex; i++){
            this->m_RequestsArray[i-1].nodeId   = this->m_RequestsArray[i].nodeId;
            this->m_RequestsArray[i-1].reqType  = this->m_RequestsArray[i].reqType;
            this->m_RequestsArray[i-1].regId    = this->m_RequestsArray[i].regId;
            this->m_RequestsArray[i-1].data     = this->m_RequestsArray[i].data;
            this->m_RequestsArray[i-1].CRC      = this->m_RequestsArray[i].CRC;
        }

        // Clean 
        this->m_RequestsArray[m_RequestsArrayIndex].Clean();

        // Decrease index
        this->m_RequestsArrayIndex--;
    }

    return RC_e::SUCCESS;
}  

//=====================================================================================================
RC_e RequestBuffer::CleanBuffer(){
    // Check if array is null
    if (this->m_RequestsArray == NULL){
        Debug("Error: ERROR_NULL_POINTER in RequestBuffer::CleanBuffer()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Iterate through the requests
    for (int i=0; i<REQUEST_BUFFER_SIZE; i++){
        this->m_RequestsArray[i].Clean();
    }

    // Init index
    this->m_RequestsArrayIndex = -1;

    return RC_e::SUCCESS;
}  

//=====================================================================================================
RC_e RequestBuffer::PrintBuffer(){
    // Check if array is null
    if (this->m_RequestsArray == NULL){
        Debug("Error: ERROR_NULL_POINTER in RequestBuffer::PrintBuffer()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Iterate through the requests
    for (int i=0; i<=m_RequestsArrayIndex; i++){
        this->m_RequestsArray[i].Print();
    }

    return RC_e::SUCCESS;
}  

//=====================================================================================================
RC_e RequestBuffer::EnableDebugMode(){
    this->m_debugMode = true;
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e RequestBuffer::DisableDebugMode(){
    this->m_debugMode = false;
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e RequestBuffer::Debug(char* msg){
    // Check if Debug mode is active
    if (this->m_debugMode){
        // Print message
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}

