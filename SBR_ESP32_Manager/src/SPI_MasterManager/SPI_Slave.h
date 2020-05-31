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

    uint8_t m_CS;                                                       /** Chip Select Pin. */
    COM_REQUEST_st m_RequestsArray[SPI_SLAVE_REQUESTS_ARRAY_SIZE];      /** Array of requests. */
    int8_t m_RequestsArrayIndex;                                        /** Index of array of frames. */

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
     * \brief Add request to the buffer.
     */
    RC_e AddRequest(COM_REQUEST_TYPE_e type, COM_REQUEST_REG_ID_e id, uint32_t data);  

    /**
     * \brief Clean Buffer of requests.
     */
    RC_e CleanBuffer();  

private:


};

#endif // SPI_SLAVE_H