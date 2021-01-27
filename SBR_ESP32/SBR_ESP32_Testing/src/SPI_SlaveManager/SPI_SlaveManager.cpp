/**
 * @file SPI_SlaveManager.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the SPI Slave communication
 * @version 1.0
 * @date 14-06-2020
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												Includes
 *******************************************************************************************************************************************/
#include "SPI_SlaveManager.h"
#include "../../lib/Utility/Utility.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

//=====================================================================================================
SPI_SlaveManager::SPI_SlaveManager(uint8_t _SO, uint8_t _SI, uint8_t _SCLK, uint8_t _SS){
    // Init
    CleanBuffer();
    this->m_SS = (gpio_num_t)_SS;

    // Configure SPI 
    SPIConfigure(_SO, _SI, _SCLK, _SS);
}

//=====================================================================================================
SPI_SlaveManager::~SPI_SlaveManager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e SPI_SlaveManager::ListenRequest(){

    // Result code
    RC_e retCode = RC_e::ERROR;

    // Get length of the buffer stream
    int length = m_slave.getInputStream()->length();

    // Slave SPI has got data in
    if (length >= SPI_MANAGER_REQUEST_SIZE && digitalRead(m_SS) == HIGH){  

        // Buffer
        array_t _buffer(length);

        // Collect data in buffer
        while (m_slave.getInputStream()->length()) {
            m_slave.readToArray(_buffer);
        }

        // Flush the input buffer
        m_slave.flushInputStream();
        
        // Handle data in packages of SPI_MANAGER_REQUEST_SIZE
        for(int i=0; i<length/SPI_MANAGER_REQUEST_SIZE; i++){
            // Create Buffer for one frame
            array_t _bufferOneRequest(SPI_MANAGER_REQUEST_SIZE);

            // Calculate offset
            auto _offset = SPI_MANAGER_REQUEST_SIZE*i;

            // Assign buffer bytes
            _bufferOneRequest.append(_buffer[_offset + 0]);
            _bufferOneRequest.append(_buffer[_offset + 1]);
            _bufferOneRequest.append(_buffer[_offset + 2]);
            _bufferOneRequest.append(_buffer[_offset + 3]);
            _bufferOneRequest.append(_buffer[_offset + 4]);
            _bufferOneRequest.append(_buffer[_offset + 5]);
            _bufferOneRequest.append(_buffer[_offset + 6]);
            _bufferOneRequest.append(_buffer[_offset + 7]);

            // Handle request
            if((retCode = HandleRequest(&_bufferOneRequest)) != RC_e::SUCCESS){
                return retCode;
            }
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_SlaveManager::AddWriteRequest(COM_REQUEST_REG_ID_e regId, uint32_t data){

    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if array is null
    if (m_RequestsArray == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Add Write Request to the buffer
    if((retCode = AddRequest(COM_REQUEST_TYPE_e::WRITE, regId, data)) != RC_e::SUCCESS){
        return retCode;
    }

    return RC_e::SUCCESS;
} 

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e SPI_SlaveManager::SPIConfigure(uint8_t _SO, uint8_t _SI, uint8_t _SCLK, uint8_t _SS){

    m_slave.begin((gpio_num_t)_SO, (gpio_num_t)_SI, (gpio_num_t)_SCLK, (gpio_num_t)_SS, SPI_MANAGER_REQUEST_SIZE);

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_SlaveManager::HandleRequest(array_t* buffer){

    // Result code
    RC_e retCode = RC_e::ERROR;
    
    // Check if the pointer is null
    if (buffer == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Local request
    COM_REQUEST_st request;

    // Local buffer
    uint8_t _buffer[SPI_MANAGER_REQUEST_SIZE] = {0};

    // Assign from array_t to uint8_t
    _buffer[0] = (*buffer)[0];
    _buffer[1] = (*buffer)[1];
    _buffer[2] = (*buffer)[2];
    _buffer[3] = (*buffer)[3];
    _buffer[4] = (*buffer)[4];
    _buffer[5] = (*buffer)[5];
    _buffer[6] = (*buffer)[6];
    _buffer[7] = (*buffer)[7];

    // Convert buffer to request
    if((retCode = BufferToRequest(_buffer, &request)) != RC_e::SUCCESS){
        return retCode;
    }

    // Check CRC
    if(request.CRC != CalculateCrcFromRequest(&request)){
        return RC_e::ERROR_CRC;
    }

    // Read-Write Selector
    switch(request.comRequestType){
        case COM_REQUEST_TYPE_e::WRITE:
            if((retCode = HandleWriteRequest(&request)) != RC_e::SUCCESS){
                return retCode;
            }
            break;

        case COM_REQUEST_TYPE_e::READ:
            if((retCode = HandleReadRequest()) != RC_e::SUCCESS){
                return retCode;
            }
            break;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_SlaveManager::HandleWriteRequest(COM_REQUEST_st* request){

    // Check if the pointer is null
    if (request == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Serial.println("======== RX =========");
    // Serial.print("Req: ");
    // Serial.println(request->comRequestType);
    // Serial.print("ReqID: ");
    // Serial.println(request->comRequestRegId);
    // Serial.print("Data: ");
    // Serial.println(request->data);
    // Serial.print("CRC: ");
    // Serial.println(request->CRC);

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_SlaveManager::HandleReadRequest(){

    // Result code
    RC_e retCode = RC_e::ERROR;

    // Local request
    COM_REQUEST_st _request;

    // Check if the sending request index max value is reached
    if(m_RequestsArrayIndexToSend <= m_RequestsArrayIndex){
        // Get values from array
        _request.comRequestType = m_RequestsArray[m_RequestsArrayIndexToSend].comRequestType;
        _request.comRequestRegId = m_RequestsArray[m_RequestsArrayIndexToSend].comRequestRegId;
        _request.data = m_RequestsArray[m_RequestsArrayIndexToSend].data;
        _request.CRC = m_RequestsArray[m_RequestsArrayIndexToSend].CRC;

        // Increase request sending index
        m_RequestsArrayIndexToSend++;
    } else{
        // Clean
        if((retCode = CleanBuffer()) != RC_e::SUCCESS){
            return retCode;
        }

        // Create Stop request
        _request.comRequestType = COM_REQUEST_TYPE_e::STOP;
        _request.comRequestRegId = 0;
        _request.data = 0;
        _request.CRC = CalculateCrcFromRequest(&_request);
    }

    // SPI Buffer
    array_t _buffer(SPI_MANAGER_REQUEST_SIZE);

    // Local buffer for conversion
    uint8_t _tempBuffer[SPI_MANAGER_REQUEST_SIZE] = {0};

    // Convert Request to buffer
    if((retCode = RequestToBuffer(&_request, _tempBuffer)) != RC_e::SUCCESS){
        return retCode;
    }

    // Assign from _tempBuffer to buffer
    _buffer.append(_tempBuffer[0]);
    _buffer.append(_tempBuffer[1]);
    _buffer.append(_tempBuffer[2]);
    _buffer.append(_tempBuffer[3]);
    _buffer.append(_tempBuffer[4]);
    _buffer.append(_tempBuffer[5]);
    _buffer.append(_tempBuffer[6]);
    _buffer.append(_tempBuffer[7]);
    
    // Send request
    m_slave.writeFromArray(_buffer);

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_SlaveManager::AddRequest(COM_REQUEST_TYPE_e type, COM_REQUEST_REG_ID_e regId, uint32_t data){

    // Check if array is null
    if (m_RequestsArray == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if index max value is reached
    if(m_RequestsArrayIndex<(SPI_SLAVE_REQUESTS_ARRAY_SIZE-1)){
        m_RequestsArrayIndex++;
    }

    // Add request to the array
    m_RequestsArray[m_RequestsArrayIndex].comRequestType = type;
    m_RequestsArray[m_RequestsArrayIndex].comRequestRegId = regId;
    m_RequestsArray[m_RequestsArrayIndex].data = data;
    m_RequestsArray[m_RequestsArrayIndex].CRC = CalculateCrcFromRequest(&m_RequestsArray[m_RequestsArrayIndex]);

    return RC_e::SUCCESS;
}  

RC_e SPI_SlaveManager::CleanBuffer(){
    // Iterate through the array of requests
    for(int i=0; i<SPI_SLAVE_REQUESTS_ARRAY_SIZE; i++){
        // Clear
        m_RequestsArray[i].comRequestType = COM_REQUEST_TYPE_e::NONE1;
        m_RequestsArray[i].comRequestRegId = 0;
        m_RequestsArray[i].data = 0;
        m_RequestsArray[i].CRC = 0;
    }

    // Init
    m_RequestsArrayIndex=-1;
    m_RequestsArrayIndexToSend=0;

    return RC_e::SUCCESS;
}  

