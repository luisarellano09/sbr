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

RC_e SPI_MasterManager::SendRequests(ESP32_Slave_e slave){
    for(int i=0; i<=m_SPI_Slaves[slave].m_RequestsArrayIndex; i++){
        SPI_TX_Request(m_SPI_Slaves[slave].m_RequestsArray[i], m_SPI_Slaves[slave].m_CS);
        delay(1);
    }
    m_SPI_Slaves[slave].CleanBuffer();
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

    quick_fix_spi_timing(m_master.bus());   // Fix SPI timing

    return RC_e::SUCCESS;
}


RC_e SPI_MasterManager::SPI_TX_Request(COM_REQUEST_st request, uint8_t _CS){

    uint8_t _buffer[SPI_MANAGER_REQUEST_SIZE];

    _buffer[0] = request.comRequestType;
    _buffer[1] = request.comRequestRegId;
    _buffer[2] = (byte)request.data;
    _buffer[3] = (byte)(request.data>>8);
    _buffer[4] = (byte)(request.data>>16);
    _buffer[5] = (byte)(request.data>>24);
    _buffer[6] = (byte)request.CRC;
    _buffer[7] = (byte)(request.CRC>>8);
    
    m_master.beginTransaction(m_spi_setting);
    digitalWrite(_CS, LOW);

    for(int i=0; i<SPI_MANAGER_REQUEST_SIZE; i++){
        m_master.transfer(_buffer[i]);
    }

    digitalWrite(_CS, HIGH);
    m_master.endTransaction();

    return RC_e::SUCCESS;
}

