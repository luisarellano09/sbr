/**
 * \file SPI_SlaveManager.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 03.05.2020
 *
 * \brief Class to Manage the SPI Slave
 *
 * 
 * 
 * Changes
 * 30.05.2020: Create Class
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

SPI_SlaveManager::SPI_SlaveManager(gpio_num_t _MO, gpio_num_t _MI, gpio_num_t _MCLK, gpio_num_t _SS){
    m_SS = _SS;
    CleanBuffer();
    SPIConfigure(_MO, _MI, _MCLK, _SS);
}

SPI_SlaveManager::~SPI_SlaveManager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

RC_e SPI_SlaveManager::ListenRequest(){

    // Get length of the buffer stream
    int length = m_slave.getInputStream()->length();

    if (length >= SPI_MANAGER_REQUEST_SIZE && digitalRead(m_SS) == HIGH) {  // Slave SPI has got data in.

        array_t _buffer(length);

        while (m_slave.getInputStream()->length()) {
            m_slave.readToArray(_buffer);
        }

        // Flush the input buffer
        m_slave.flushInputStream();
        
        for(int i=0; i<length/SPI_MANAGER_REQUEST_SIZE; i++){
            // Create Buffer for one frame
            array_t _bufferOneFrame(SPI_MANAGER_REQUEST_SIZE);

            // Calculate offset
            auto _offset = SPI_MANAGER_REQUEST_SIZE*i;

            // Assign buffer bytes
            _bufferOneFrame.append(_buffer[_offset + 0]);
            _bufferOneFrame.append(_buffer[_offset + 1]);
            _bufferOneFrame.append(_buffer[_offset + 2]);
            _bufferOneFrame.append(_buffer[_offset + 3]);
            _bufferOneFrame.append(_buffer[_offset + 4]);
            _bufferOneFrame.append(_buffer[_offset + 5]);
            _bufferOneFrame.append(_buffer[_offset + 6]);
            _bufferOneFrame.append(_buffer[_offset + 7]);

            // Get frame
            DecodeRequest(&_bufferOneFrame);
        }
    }

    return RC_e::SUCCESS;
}

RC_e SPI_SlaveManager::AddWriteRequest(COM_REQUEST_REG_ID_e id, uint32_t data){

    // Result code
    RC_e retCode = RC_e::ERROR;

    if (m_RequestsArray == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Add Request
    if((retCode = AddRequest(COM_REQUEST_TYPE_e::WRITE, id, data)) != RC_e::SUCCESS){
        return retCode;
    }

    return RC_e::SUCCESS;
} 

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

RC_e SPI_SlaveManager::SPIConfigure(gpio_num_t _MO, gpio_num_t _MI, gpio_num_t _MCLK, gpio_num_t _SS){

    m_slave.begin(SO, SI, SCLK, SS, 8);

    return RC_e::SUCCESS;
}

RC_e SPI_SlaveManager::DecodeRequest(array_t* buffer){

    // Local Frame
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
    BufferToRequest(_buffer, &request);

    // Check CRC
    if (request.CRC != CalculateCrcFromRequest(&request)){
        return RC_e::ERROR_CRC;
    }

    // Read Write Selector
    if(request.comRequestType == COM_REQUEST_TYPE_e::WRITE){
        HandleWriteRequest(request);
    } else if(request.comRequestType == COM_REQUEST_TYPE_e::READ){
        HandleReadRequest();
    }

    return RC_e::SUCCESS;
}

RC_e SPI_SlaveManager::HandleWriteRequest(COM_REQUEST_st request){

    // Serial.println("======== RX =========");
    // Serial.print("Req: ");
    // Serial.println(request.comFrameReq);
    // Serial.print("ReqID: ");
    // Serial.println(request.comFrameRegId);
    // Serial.print("Data: ");
    // Serial.println(request.data);
    // Serial.print("CRC: ");
    // Serial.println(request.CRC);

    if (test_data != request.data){
        Serial.print("Error: ");
        Serial.print(test_data);
        Serial.print(" != ");
        Serial.println(request.data);
        test_data = request.data;
    }

    test_data++;

    if (test_data > 10000) test_data = 0;


    return RC_e::SUCCESS;
}

RC_e SPI_SlaveManager::HandleReadRequest(){

    COM_REQUEST_st _request;

    if(m_RequestsArrayIndexToSend<=m_RequestsArrayIndex){
        _request.comRequestType = m_RequestsArray[m_RequestsArrayIndexToSend].comRequestType;
        _request.comRequestRegId = m_RequestsArray[m_RequestsArrayIndexToSend].comRequestRegId;
        _request.data = m_RequestsArray[m_RequestsArrayIndexToSend].data;
        _request.CRC = m_RequestsArray[m_RequestsArrayIndexToSend].CRC;
        m_RequestsArrayIndexToSend++;
    } else{
        CleanBuffer();
        _request.comRequestType = COM_REQUEST_TYPE_e::STOP;
        _request.comRequestRegId = 0;
        _request.data = 0;
        _request.CRC = CalculateCrcFromRequest(&_request);
    }

    // SPI Buffer
    array_t _buffer(SPI_MANAGER_REQUEST_SIZE);

    // Local buffer for conversion
    uint8_t _partialBuffer[SPI_MANAGER_REQUEST_SIZE] = {0};

    RequestToBuffer(&_request, _partialBuffer);

    // Assign from partialBuffer to buffer
    _buffer.append(_partialBuffer[0]);
    _buffer.append(_partialBuffer[1]);
    _buffer.append(_partialBuffer[2]);
    _buffer.append(_partialBuffer[3]);
    _buffer.append(_partialBuffer[4]);
    _buffer.append(_partialBuffer[5]);
    _buffer.append(_partialBuffer[6]);
    _buffer.append(_partialBuffer[7]);
    
    m_slave.writeFromArray(_buffer);

    // Serial.println("======== TX =========");
    // Serial.print("Req: ");
    // Serial.println(_request.comRequestType);
    // Serial.print("ReqID: ");
    // Serial.println(_request.comRequestRegId);
    // Serial.print("Data: ");
    // Serial.println(_request.data);
    // Serial.print("CRC: ");
    // Serial.println(_request.CRC);

    return RC_e::SUCCESS;
}


RC_e SPI_SlaveManager::AddRequest(COM_REQUEST_TYPE_e type, COM_REQUEST_REG_ID_e id, uint32_t data){

    if (m_RequestsArray == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check index
    if(m_RequestsArrayIndex<(SPI_SLAVE_REQUESTS_ARRAY_SIZE-1)){
        m_RequestsArrayIndex++;
    }

    // Add Frame
    m_RequestsArray[m_RequestsArrayIndex].comRequestType = type;
    m_RequestsArray[m_RequestsArrayIndex].comRequestRegId = id;
    m_RequestsArray[m_RequestsArrayIndex].data = data;
    m_RequestsArray[m_RequestsArrayIndex].CRC = CalculateCrcFromRequest(&m_RequestsArray[m_RequestsArrayIndex]);

    return RC_e::SUCCESS;
}  

RC_e SPI_SlaveManager::CleanBuffer(){

    for(int i=0; i<SPI_SLAVE_REQUESTS_ARRAY_SIZE; i++){
        m_RequestsArray[i].comRequestType = COM_REQUEST_TYPE_e::NONE;
        m_RequestsArray[i].comRequestRegId = 0;
        m_RequestsArray[i].data = 0;
        m_RequestsArray[i].CRC = 0;
    }
    m_RequestsArrayIndex=-1; //2
    m_RequestsArrayIndexToSend=0;

    return RC_e::SUCCESS;
}  

