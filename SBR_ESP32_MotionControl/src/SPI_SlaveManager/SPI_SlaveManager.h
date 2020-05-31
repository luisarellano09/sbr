/**
 * \file SPI_SlaveManager.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 03.05.2020
 *
 * \brief Class to Manage the SPI Slave
 *
 * 
 * 
 * Changes
 * 30.05.2020: Create Class
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
 * \brief Class to Manage the SPI Slave
 */
class SPI_SlaveManager
{

    typedef SimpleArray<uint8_t, int> array_t;

public:  

    /**
     * \brief Constructor.
     */
    SPI_SlaveManager(gpio_num_t _MO, gpio_num_t _MI, gpio_num_t _MCLK, gpio_num_t _SS);

    /**
     * \brief Destructor.
     */
    ~SPI_SlaveManager();

    /**
     * \brief Function to get request.
     *
     * \return Error Code.
     */
    RC_e ListenRequest();

    /**
     * \brief Function add a write request.
     *
     * \return Error Code.
     */  
    RC_e AddWriteRequest(COM_REQUEST_REG_ID_e id, uint32_t data);
    
private:

    SlaveSPI m_slave;
    gpio_num_t m_SS;

    COM_REQUEST_st m_RequestsArray[SPI_SLAVE_REQUESTS_ARRAY_SIZE];      /** Array of requests. */
    int8_t m_RequestsArrayIndex;
    int8_t m_RequestsArrayIndexToSend;                                         /** Index of array of frames. */

    uint32_t count = 0;
    uint32_t count_logger = 0;
    uint32_t test_data = 0;

    /**
     * \brief Function to configure the SPI .
     *
     * 
     * \return Error Code.
     */
    RC_e SPIConfigure(gpio_num_t _MO, gpio_num_t _MI, gpio_num_t _MCLK, gpio_num_t _SS);

    /**
     * \brief Function to decode request.
     *
     * \return Error Code.
     */
    RC_e DecodeRequest(array_t* buffer);

    /**
     * \brief Function to handle RX request.
     *
     * \return Error Code.
     */
    RC_e HandleWriteRequest(COM_REQUEST_st localFrame);

    /**
     * \brief Function to hanfle RX request.
     *
     * \return Error Code.
     */
    RC_e HandleReadRequest();

    /**
     * \brief Add request to the buffer.
     */
    RC_e AddRequest(COM_REQUEST_TYPE_e type, COM_REQUEST_REG_ID_e id, uint32_t data);  

    /**
     * \brief Clean Buffer of requests.
     */
    RC_e CleanBuffer();  
   
};

#endif // SPI_SLAVEMANAGER_H