/**
 * \file SPI_Slave.cpp
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 03.05.2020
 *
 * \brief Class to describe a SPI Slave
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
#include "SPI_Slave.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

SPI_Slave::SPI_Slave(){}

SPI_Slave::~SPI_Slave(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

void SPI_Slave::SetCS(uint8_t _CS){
    this->m_CS = _CS;
}  

RC_e SPI_Slave::AddRequest(COM_REQUEST_TYPE_e type, COM_REQUEST_REG_ID_e id, uint32_t data){

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

RC_e SPI_Slave::CleanBuffer(){
    for(int i=0; i<SPI_SLAVE_REQUESTS_ARRAY_SIZE; i++){
        m_RequestsArray[i].comRequestType = COM_REQUEST_TYPE_e::STOP;
        m_RequestsArray[i].comRequestRegId = 0;
        m_RequestsArray[i].data = 0;
        m_RequestsArray[i].CRC = 0;
    }
    m_RequestsArrayIndex=-1;

    return RC_e::SUCCESS;
}  

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/


