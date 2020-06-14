/**
 * @file SPI_Slave.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a SPI Slave
 * @version 0.1
 * @date 13-06-2020
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												Includes
 *******************************************************************************************************************************************/
#include "SPI_Slave.h"
#include "../../lib/Utility/Utility.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

//=====================================================================================================
SPI_Slave::SPI_Slave(){
    // Init
    this->m_CS = 0;
    CleanBuffer();
}

//=====================================================================================================
SPI_Slave::~SPI_Slave(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e SPI_Slave::SetCS(uint8_t _CS){
    
    // Check if CS exists
    if(_CS <= 0){
        return RC_e::ERROR_NO_CS;
    }

    this->m_CS = _CS;

    return RC_e::SUCCESS;
}  

//=====================================================================================================
RC_e SPI_Slave::AddRequest(COM_REQUEST_TYPE_e type, COM_REQUEST_REG_ID_e regID, uint32_t data){

    // Check if array is null
    if (this->m_RequestsArray == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if max index is reached
    if(this->m_RequestsArrayIndex<(SPI_SLAVE_REQUESTS_ARRAY_SIZE-1)){
        this->m_RequestsArrayIndex++;
    }

    // Add request
    this->m_RequestsArray[this->m_RequestsArrayIndex].comRequestType = type;
    this->m_RequestsArray[this->m_RequestsArrayIndex].comRequestRegId = regID;
    this->m_RequestsArray[this->m_RequestsArrayIndex].data = data;
    this->m_RequestsArray[this->m_RequestsArrayIndex].CRC = CalculateCrcFromRequest(&this->m_RequestsArray[this->m_RequestsArrayIndex]);

    return RC_e::SUCCESS;
}  

//=====================================================================================================
RC_e SPI_Slave::CleanBuffer(){
    // Iterate through the requests
    for(int i=0; i<SPI_SLAVE_REQUESTS_ARRAY_SIZE; i++){
        this->m_RequestsArray[i].comRequestType = COM_REQUEST_TYPE_e::NONE;
        this->m_RequestsArray[i].comRequestRegId = 0;
        this->m_RequestsArray[i].data = 0;
        this->m_RequestsArray[i].CRC = 0;
    }

    // Init index
    this->m_RequestsArrayIndex=-1;

    return RC_e::SUCCESS;
}  

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/


