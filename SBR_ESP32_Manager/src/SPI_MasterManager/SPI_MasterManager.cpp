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

SPI_MasterManager::SPI_MasterManager(uint32_t _clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK){

    SPIConfigure(_clock, _MO, _MI, _MCLK);

}

SPI_MasterManager::~SPI_MasterManager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

RC_e SPI_MasterManager::SetSlave(ESP32_Slave_e slave, uint8_t _CS){

    this->m_SPI_Slaves[slave].m_CS = _CS;
    this->m_SPI_Slaves[slave].CleanBuffer();
    
    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::Run(){
    // Error code
    RC_e retCode = RC_e::ERROR;

    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::SetLogger(Logger* logger){
    this->m_logger = logger;
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

RC_e SPI_MasterManager::SPIConfigure(uint32_t _clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK){
    this->m_spi_setting = SPISettings(_clock, MSBFIRST, SPI_MODE0);
    this->m_master = SPIClass(HSPI);  

    pinMode(MS, OUTPUT);
    digitalWrite(MS, HIGH);

    pinMode(_MCLK, OUTPUT);
    digitalWrite(_MCLK, LOW);  // Due to SPI_MODE0
    m_master.begin(_MCLK, _MI, _MO);

    quick_fix_spi_timing(m_master.bus()); 

    return RC_e::SUCCESS;
}

RC_e SPI_MasterManager::LoggerWrite(char* msg){
    if(m_logger != NULL){
        m_logger->Write(msg);
    }
    
    return RC_e::SUCCESS;
}

