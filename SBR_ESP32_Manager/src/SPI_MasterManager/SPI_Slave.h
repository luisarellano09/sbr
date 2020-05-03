/**
 * \file SPI_Slave.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 03.05.2020
 *
 * \brief Class to describe a SPI Slave.
 *
 * 
 * 
 * Changes
 * 03.05.2020: Class was created
 * 
 *
 */

#ifndef SPI_SLAVE_H
#define SPI_SLAVE_H

/*******************************************************************************************************************************************
 *  												Includes
 *******************************************************************************************************************************************/
#include "../../lib/Definition/GlobalDef.h"
#include "../Definition/LocalDef.h"


/*******************************************************************************************************************************************
 *  												WifiManager Class
 *******************************************************************************************************************************************/

/**
 * \brief Class to describe a SPI Slave.
 */
class SPI_Slave
{
public:  

    /**
     * \brief Constructor.
     */
    SPI_Slave();

    /**
     * \brief Destructor.
     */
    ~SPI_Slave();

    /**
     * \brief Function to set the Chip Select.
     */
    void SetCS(uint8_t _CS);


    /**
     * \brief Add frame to the buffer.
     */
    RC_e AddFrame(COM_FRAME_REQ_e _req, COM_FRAME_REG_ID_e _id, uint32_t _data);  

    /**
     * \brief Clean Buffer of frames.
     */
    RC_e CleanBuffer();  

    uint8_t m_CS;                                           /** Chip Select Pin. */
    COM_FRAME_st m_FrameBuffer[SPI_SLAVE_BUFFER_SIZE];      /** Array of frames. */
    int8_t m_FrameBufferIndex;

private:


};

#endif // SPI_SLAVE_H