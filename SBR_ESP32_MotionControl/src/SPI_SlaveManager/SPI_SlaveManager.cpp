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
    COM_REQUEST_st localFrame;

    // REQUEST
    localFrame.comRequestType = (*buffer)[0];

    // ID
    localFrame.comRequestRegId = (*buffer)[1];

    // DATA
    localFrame.data = ((*buffer)[2]);
    localFrame.data += ((*buffer)[3])<<8;
    localFrame.data += ((*buffer)[4])<<16;
    localFrame.data += ((*buffer)[5])<<24;

    // CRC
    localFrame.CRC = (*buffer)[6];
    localFrame.CRC += ((*buffer)[7])<<8;

    // Read Write Selector
    if(localFrame.comRequestType == COM_REQUEST_TYPE_e::WRITE){
        HandleWriteRequest(localFrame);
    } else if(localFrame.comRequestType == COM_REQUEST_TYPE_e::READ){
        HandleReadRequest();
    }

    return RC_e::SUCCESS;
}

RC_e SPI_SlaveManager::HandleWriteRequest(COM_REQUEST_st localFrame){

    // Serial.println("======== RX =========");
    // Serial.print("Req: ");
    // Serial.println(localFrame.comFrameReq);
    // Serial.print("ReqID: ");
    // Serial.println(localFrame.comFrameRegId);
    // Serial.print("Data: ");
    // Serial.println(localFrame.data);
    // Serial.print("CRC: ");
    // Serial.println(localFrame.CRC);

    if (test_data != localFrame.data){
        Serial.print("Error: ");
        Serial.print(test_data);
        Serial.print(" != ");
        Serial.println(localFrame.data);
        test_data = localFrame.data;
    }

    test_data++;

    if (test_data > 10000) test_data = 0;


    return RC_e::SUCCESS;
}

RC_e SPI_SlaveManager::HandleReadRequest(){

    COM_REQUEST_st localFrame;

    if(m_RequestsArrayIndexToSend<=m_RequestsArrayIndex){
        localFrame.comRequestType = m_RequestsArray[m_RequestsArrayIndexToSend].comRequestType;
        localFrame.comRequestRegId = m_RequestsArray[m_RequestsArrayIndexToSend].comRequestRegId;
        localFrame.data = m_RequestsArray[m_RequestsArrayIndexToSend].data;
        localFrame.CRC = m_RequestsArray[m_RequestsArrayIndexToSend].CRC;
        m_RequestsArrayIndexToSend++;
    } else{
        CleanBuffer();
        localFrame.comRequestType = COM_REQUEST_TYPE_e::STOP;
        localFrame.comRequestRegId = 0;
        localFrame.data = 0;
        localFrame.CRC = 169;
    }

    array_t buffer(SPI_MANAGER_REQUEST_SIZE);

    buffer.append(localFrame.comRequestType);
    buffer.append(localFrame.comRequestRegId);
    buffer.append((byte)localFrame.data);
    buffer.append((byte)(localFrame.data>>8));
    buffer.append((byte)(localFrame.data>>16));
    buffer.append((byte)(localFrame.data>>24));
    buffer.append((byte)localFrame.CRC);
    buffer.append((byte)(localFrame.CRC>>8));
    
    m_slave.writeFromArray(buffer);

    // Serial.println("======== TX =========");
    // Serial.print("Req: ");
    // Serial.println(localFrame.comRequestType);
    // Serial.print("ReqID: ");
    // Serial.println(localFrame.comRequestRegId);
    // Serial.print("Data: ");
    // Serial.println(localFrame.data);
    // Serial.print("CRC: ");
    // Serial.println(localFrame.CRC);

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
    m_RequestsArray[m_RequestsArrayIndex].CRC = 69;

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

