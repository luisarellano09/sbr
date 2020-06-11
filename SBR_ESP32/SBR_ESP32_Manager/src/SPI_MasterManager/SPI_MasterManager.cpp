/**
 * \file SPI_MasterManager.cpp
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 03.05.2020
 *
 * \brief Class to Manage the SPI Master
 *
 * 
 * 
 * Changes
 * 03.05.2020: Create Class
 * 
 *
 */

/*******************************************************************************************************************************************
 *  												Includes
 *******************************************************************************************************************************************/
#include "SPI_MasterManager.h"
#include "../../lib/Utility/Utility.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

SPI_MasterManager::SPI_MasterManager(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK){

    SPIConfigure(clock, _MO, _MI, _MCLK);

    // Clear Chip Selects
    for(auto i=0; i<ESP32_Slave_e::SLAVE_LENGTH; i++){
        this->m_SPI_Slaves[i].m_CS = 0;
    }

}

SPI_MasterManager::~SPI_MasterManager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

RC_e SPI_MasterManager::ConnectTableRT(TableRT* tableRT){
    this->m_tableRT = tableRT;
}

RC_e SPI_MasterManager::SetSlave(ESP32_Slave_e slave, uint8_t _CS){

    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_SPI_Slaves[slave].m_CS = _CS;

    // Clean Buffer
    if((retCode = this->m_SPI_Slaves[slave].CleanBuffer()) != RC_e::SUCCESS){
        return retCode;
    }

    // Set the Chip Select to 1
    pinMode(_CS, OUTPUT);
    digitalWrite(_CS, HIGH);
    
    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::AddWriteRequest(ESP32_Slave_e slave, COM_REQUEST_REG_ID_e id, uint32_t data){

    // Result code
    RC_e retCode = RC_e::ERROR;

    if((retCode = this->m_SPI_Slaves[slave].AddRequest(COM_REQUEST_TYPE_e::WRITE, id, data)) != RC_e::SUCCESS){
        return retCode;
    }

    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::SendWriteRequests(ESP32_Slave_e slave){

    // Iterate to slaves
    for(int i=0; i<=m_SPI_Slaves[slave].m_RequestsArrayIndex; i++){
        SPI_SendWriteRequest(m_SPI_Slaves[slave].m_RequestsArray[i], m_SPI_Slaves[slave].m_CS);
        delay(1);
    }

    // Clean Buffer
    this->m_SPI_Slaves[slave].CleanBuffer();

    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::ReadSlaveRequests(ESP32_Slave_e slave){

    // Check if pointer is Null
    if(this->m_tableRT == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    uint8_t countStops = 0;
    
    for(auto i = 0; i< SPI_SLAVE_REQUESTS_ARRAY_SIZE; i++){
        // Request to read
        COM_REQUEST_st request;
        
        // Read request
        if( SPI_ReadSlaveRequest(&request, this->m_SPI_Slaves[slave].m_CS) == RC_e::SUCCESS){
            
            if (request.comRequestType == COM_REQUEST_TYPE_e::STOP || (request.comRequestType == 0 && request.comRequestRegId == 0 && request.data == 0)){
                countStops++;
            } else if (request.comRequestType == COM_REQUEST_TYPE_e::READ || request.comRequestType == COM_REQUEST_TYPE_e::WRITE){
                // Handle request
                HandleReadSlaveRequest(&request);
            }

            if(countStops > SPI_MANAGER_NUMBER_STOP_EMPTY){
                return RC_e::SUCCESS;
            }
        }
    }

    return RC_e::SUCCESS;
}


/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

RC_e SPI_MasterManager::SPIConfigure(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK){

    this->m_spi_setting = SPISettings(clock, MSBFIRST, SPI_MODE0);
    this->m_master = SPIClass(HSPI);  

    pinMode(_MCLK, OUTPUT);     // Set clock as output
    digitalWrite(_MCLK, LOW);   // Due to SPI_MODE0
    m_master.begin(_MCLK, _MI, _MO);    // Begin SPI master

    return RC_e::SUCCESS;
}


RC_e SPI_MasterManager::SPI_SendWriteRequest(COM_REQUEST_st request, uint8_t _CS){

    // Buffer
    uint8_t _buffer[SPI_MANAGER_REQUEST_SIZE];

    // Convert request to buffer  
    RequestToBuffer(&request, _buffer);
    
    // Begin transcation
    m_master.beginTransaction(m_spi_setting);
    digitalWrite(_CS, LOW);

    // Iterate all bytes from buffer
    for(int i=0; i<SPI_MANAGER_REQUEST_SIZE; i++){
        m_master.transfer(_buffer[i]);
    }

    // End Transaction
    digitalWrite(_CS, HIGH);
    m_master.endTransaction();

    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::SPI_ReadSlaveRequest(COM_REQUEST_st* request, uint8_t _CS){

    // Check if pointer is null
    if(request == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if CS exists
    if(_CS == 0){
        return RC_e::ERROR_NO_CS;
    }

    // Buffer
    uint8_t _buffer[SPI_MANAGER_REQUEST_SIZE] = {0};

    // Begin Transaction
    m_master.beginTransaction(m_spi_setting);
    digitalWrite(_CS, LOW);

    // Read request
    m_master.transferBytes(_buffer, _buffer, SPI_MANAGER_REQUEST_SIZE);
    
    // End Transaction
    digitalWrite(_CS, HIGH);
    m_master.endTransaction();

    // Convert buffer to request
    BufferToRequest(_buffer, request);

    // Check CRC
    if (request->CRC != CalculateCrcFromRequest(request)){
        return RC_e::ERROR_CRC;
    }

    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::HandleReadSlaveRequest(COM_REQUEST_st* request){

    if(request->comRequestType == COM_REQUEST_TYPE_e::WRITE){
        Serial.println("====== RX =======");
        Serial.print("Req: ");
        Serial.println(request->comRequestType);
        Serial.print("ReqID: ");
        Serial.println(request->comRequestRegId);
        Serial.print("Data: ");
        Serial.println(request->data);
        Serial.print("CRC: ");
        Serial.println(request->CRC);

        // Update Register
        m_tableRT->UpdateRegister((COM_REQUEST_REG_ID_e)request->comRequestRegId, request->data);

        // Add request to suscribers buffers
        AddRequestToSubscriber(request);


    } else if (request->comRequestType == COM_REQUEST_TYPE_e::READ){
        //TODO implement read request
    }
    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::AddRequestToSubscriber(COM_REQUEST_st* request){

    for(auto i=0; i<Devices_e::DEVICE_LENGTH; i++){
        // Get subscriber
        Devices_e _subscriber = m_tableRT->m_Registers[(COM_REQUEST_REG_ID_e)request->comRequestRegId].m_subscribers[i];

        // Select the devices
        if (_subscriber == Devices_e::DEVICE_LINUX){
            //TODO implement LInux buffer
        } else if (_subscriber != Devices_e::DEVICE_NONE){
            m_SPI_Slaves[_subscriber].AddRequest(COM_REQUEST_TYPE_e::WRITE, (COM_REQUEST_REG_ID_e)request->comRequestRegId, request->data);
        }
    }
}