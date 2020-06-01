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
}

SPI_MasterManager::~SPI_MasterManager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

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
    for(int i=0; i<=m_SPI_Slaves[slave].m_RequestsArrayIndex; i++){
        SPI_SendWriteRequest(m_SPI_Slaves[slave].m_RequestsArray[i], m_SPI_Slaves[slave].m_CS);
        delay(1);
    }

    // Clean Buffer
    m_SPI_Slaves[slave].CleanBuffer();
}

RC_e SPI_MasterManager::ReadSlaveRequests(ESP32_Slave_e slave){

    uint8_t countStops = 0;
    
    for(auto i = 0; i< SPI_SLAVE_REQUESTS_ARRAY_SIZE; i++){
        // Request to read
        COM_REQUEST_st request;
        
        // Read request
        if( SPI_ReadSlaveRequest(&request, m_SPI_Slaves[slave].m_CS) == RC_e::SUCCESS){
            
            if (request.comRequestType == COM_REQUEST_TYPE_e::STOP){
                Serial.println("GOT STOP!");
                countStops++;
            } else if (request.comRequestType == COM_REQUEST_TYPE_e::READ || request.comRequestType == COM_REQUEST_TYPE_e::WRITE){
                // Handle request
                HandleReadSlaveRequest(&request);
            }

            if(countStops == 5){
                return RC_e::SUCCESS;
            }
        }

        // Wait time
        //delay(1);
    }

    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::Run(){

    // Result code
    RC_e retCode = RC_e::ERROR;

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


        Serial.println("====== RX =======");
        Serial.print("Req: ");
        Serial.println(request->comRequestType);
        Serial.print("ReqID: ");
        Serial.println(request->comRequestRegId);
        Serial.print("Data: ");
        Serial.println(request->data);
        Serial.print("CRC: ");
        Serial.println(request->CRC);
    

    return RC_e::SUCCESS;
}
