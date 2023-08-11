/**
 * @file RequestBuffer.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe the Buffer of requests
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "RequestBuffer.h"
#include "../Util/CommunicationBusUtil.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

RequestBuffer::RequestBuffer(){
    // Create Semaphore
    semaphoreMutex = xSemaphoreCreateMutex();

    // Clean Buffer
    if (this->CleanBuffer() != RC_e::SUCCESS){
        Log.errorln("[RequestBuffer::RequestBuffer] Error in CleanBuffer()");     
    }
}

//=====================================================================================================

RequestBuffer::~RequestBuffer(){}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e RequestBuffer::AddRequest(DEVICE_e nodeId, COM_REQUEST_TYPE_e reqType, COM_REQUEST_REG_ID_e regID, uint32_t data){
    // Block semaphore
    xSemaphoreTake(semaphoreMutex, 10);

    // Check if Request-Array is null
    if (this->m_RequestsArray == NULL){
        Log.fatalln("[RequestBuffer::AddRequest] m_RequestsArray ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if max index is reached
    if (this->m_RequestsArrayIndex >= REQUEST_BUFFER_SIZE){
        Log.fatalln("[RequestBuffer::AddRequest] m_RequestsArrayIndex MAX_NODE_REQUEST_INDEX");
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

    // Unblock semaphore
    xSemaphoreGive(semaphoreMutex);

    return RC_e::SUCCESS;
} 


//=====================================================================================================

RC_e RequestBuffer::AddRequest(Request* request){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (request == NULL){
        Log.errorln("[RequestBuffer::AddRequest] request ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Add Request
    if ((retCode = this->AddRequest((DEVICE_e)request->nodeId, (COM_REQUEST_TYPE_e)request->reqType, (COM_REQUEST_REG_ID_e)request->regId, request->data)) != RC_e::SUCCESS){
        Log.errorln("[RequestBuffer::AddRequest] Error in AddRequest()");
        return retCode;
    }
    return retCode;
}  


//=====================================================================================================

RC_e RequestBuffer::ConsumeRequest(Request* request){
    // Block semaphore
    xSemaphoreTake(semaphoreMutex, 10);

    // Check if index is valid
    if (m_RequestsArrayIndex < 0){
        // Set to NULL the pointer when there is no request
        request->nodeId = DEVICE_e::NONE_DEVICE; 
    } else {
        // Check if the pointer is null
        if (request == NULL){
            Log.fatalln("[RequestBuffer::ConsumeRequest] request ERROR_NULL_POINTER");
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

    // Unblock semaphore
    xSemaphoreGive(semaphoreMutex);

    return RC_e::SUCCESS;
}  


//=====================================================================================================

RC_e RequestBuffer::CleanBuffer(){
    // Block semaphore
    xSemaphoreTake(semaphoreMutex, 10);

    // Check if array is null
    if (this->m_RequestsArray == NULL){
        Log.fatalln("[RequestBuffer::CleanBuffer] m_RequestsArray ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Iterate through the requests
    for (int i=0; i<REQUEST_BUFFER_SIZE; i++){
        this->m_RequestsArray[i].Clean();
    }

    // Init index
    this->m_RequestsArrayIndex = -1;

    // Unblock semaphore
    xSemaphoreGive(semaphoreMutex);

    return RC_e::SUCCESS;
}  


//=====================================================================================================

RC_e RequestBuffer::PrintBuffer(){
    // Block semaphore
    xSemaphoreTake(semaphoreMutex, 10);
    
    // Check if array is null
    if (this->m_RequestsArray == NULL){
        Log.fatalln("[RequestBuffer::PrintBuffer] m_RequestsArray ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Iterate through the requests
    for (int i=0; i<=m_RequestsArrayIndex; i++){
        this->m_RequestsArray[i].Print();
    }

    // Unblock semaphore
    xSemaphoreGive(semaphoreMutex);

    return RC_e::SUCCESS;
}  

