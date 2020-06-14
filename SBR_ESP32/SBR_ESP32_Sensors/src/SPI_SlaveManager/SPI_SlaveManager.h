/**
 * @file SPI_SlaveManager.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the SPI Slave communication
 * @version 1.0
 * @date 14-06-2020
 * 
 * 
 */

#ifndef SPI_SLAVEMANAGER_H
#define SPI_SLAVEMANAGER_H

/*******************************************************************************************************************************************
 *  												Includes
 *******************************************************************************************************************************************/

#include <Arduino.h>
#include <SPI.h>

#include "../Definition/LocalDef.h"
#include "../../lib/Definition/GlobalDef.h"

#include "../lib/SlaveSPI/SlaveSPI.h"
#include "../lib/SlaveSPI/SimpleArray.h"

/*******************************************************************************************************************************************
 *  												SPI Slave Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the SPI Slave
 * 
 */
class SPI_SlaveManager
{
    /**
     * @brief Type definition of a SimpleArray to be used by the SPI library functions.
     * 
     */
    typedef SimpleArray<uint8_t, int> array_t;

public:  

    /**
     * @brief Construct a new spi slavemanager object
     * 
     * @param _SO Slave Output pin
     * @param _SI Slave Input pin
     * @param _SCLK Slave clock pin
     * @param _SS Slave Select pin
     */
    SPI_SlaveManager(uint8_t _SO, uint8_t _SI, uint8_t _SCLK, uint8_t _SS);

    /**
     * @brief Destroy the spi slavemanager object
     * 
     */
    ~SPI_SlaveManager();

    /**
     * @brief Listen the incomming requests
     * 
     * @return RC_e Result code
     */
    RC_e ListenRequest();

    /**
     * @brief Add a write-type request to the buffer
     * 
     * @param regId Register ID
     * @param data Data value
     * @return RC_e Result code
     */
    RC_e AddWriteRequest(COM_REQUEST_REG_ID_e regId, uint32_t data);
    
private:

    SlaveSPI m_slave;   /**< \brief Instance of a SPI slave */
    gpio_num_t m_SS;    /**< \brief Slave select pin*/

    COM_REQUEST_st m_RequestsArray[SPI_SLAVE_REQUESTS_ARRAY_SIZE];      /**< Array of requests. */
    int8_t m_RequestsArrayIndex;                                        /**< Index of total requests added in array . */
    int8_t m_RequestsArrayIndexToSend;                                  /**< Index of sending request. */

    /**
     * @brief Configure the SPI Slave
     * 
     * @param _SO Slave Output pin
     * @param _SI Slave Input pin
     * @param _SCLK Slave clock pin
     * @param _SS Slave Select pin
     * @return RC_e Result code
     */
    RC_e SPIConfigure(uint8_t _SO, uint8_t _SI, uint8_t _SCLK, uint8_t _SS);

    /**
     * @brief Handle incomming request
     * 
     * @param buffer Reference of the buffer array
     * @return RC_e Result code
     */
    RC_e HandleRequest(array_t* buffer);

    /**
     * @brief Handle a Write-type request
     * 
     * @param request Reference of a request
     * @return RC_e Result code
     */
    RC_e HandleWriteRequest(COM_REQUEST_st* request);

    /**
     * @brief Handle a Read-type request
     * 
     * @return RC_e Result code
     */
    RC_e HandleReadRequest();

    /**
     * @brief Add request to the buffer
     * 
     * @param type Request type
     * @param regId Register ID
     * @param data Data value
     * @return RC_e Result code
     */
    RC_e AddRequest(COM_REQUEST_TYPE_e type, COM_REQUEST_REG_ID_e regId, uint32_t data);  

    /**
     * @brief Clean Buffer of requests
     * 
     * @return RC_e Result code
     */
    RC_e CleanBuffer();  
   
};

#endif // SPI_SLAVEMANAGER_H