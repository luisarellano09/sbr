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

RC_e SPI_Slave::AddFrame(COM_FRAME_REQ_e _req, COM_FRAME_REG_ID_e _id, uint32_t _data){

    if (m_FrameBuffer == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check index
    if(m_FrameBufferIndex<(SPI_SLAVE_BUFFER_SIZE-1)){
        m_FrameBufferIndex++;
    }

    // Add Frame
    m_FrameBuffer[m_FrameBufferIndex].comFrameReq = _req;
    m_FrameBuffer[m_FrameBufferIndex].comFrameRegId = _id;
    m_FrameBuffer[m_FrameBufferIndex].data = _data;
    m_FrameBuffer[m_FrameBufferIndex].CRC = 69;

    return RC_e::SUCCESS;
}  

RC_e SPI_Slave::CleanBuffer(){
    for(int i=0; i<SPI_SLAVE_BUFFER_SIZE; i++){
        m_FrameBuffer[i].comFrameReq = COM_FRAME_REQ_e::STOP;
        m_FrameBuffer[i].comFrameRegId = 0;
        m_FrameBuffer[i].data = 0;
        m_FrameBuffer[i].CRC = 0;
    }
    m_FrameBufferIndex=-1;

    return RC_e::SUCCESS;
}  

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/


