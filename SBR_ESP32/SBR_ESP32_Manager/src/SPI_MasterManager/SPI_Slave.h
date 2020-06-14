/**
 * @file SPI_Slave.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a SPI Slave
 * @version 0.1
 * @date 13-06-2020
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
 *  												SPI_Slave Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to describe a SPI Slave
 * 
 */
class SPI_Slave
{
public:  

    uint8_t m_CS;                                                       /**< Chip Select Pin. */
    COM_REQUEST_st m_RequestsArray[SPI_SLAVE_REQUESTS_ARRAY_SIZE];      /**< Array of requests. */
    int8_t m_RequestsArrayIndex;                                        /**< Index of array of requests. */

    /**
     * @brief Construct a new spi slave object
     * 
     */
    SPI_Slave();

    /**
     * @brief Destroy the spi slave object
     * 
     */
    ~SPI_Slave();

    /**
     * @brief Function to set the Chip Select
     * 
     * @param _CS Chip select pin
     * @return RC_e Result code
     */
    RC_e SetCS(uint8_t _CS);
    
    /**
     * @brief Add request to the buffer
     * 
     * @param type Request type
     * @param regID Register ID
     * @param data Data Value
     * @return RC_e Result code
     */
    RC_e AddRequest(COM_REQUEST_TYPE_e type, COM_REQUEST_REG_ID_e regID, uint32_t data);  

    /**
     * @brief Clean Buffer of requests
     * 
     * @return RC_e 
     */
    RC_e CleanBuffer();  

private:


};

#endif // SPI_SLAVE_H