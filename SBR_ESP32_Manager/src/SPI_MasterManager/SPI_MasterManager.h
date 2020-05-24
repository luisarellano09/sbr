/**
 * \file SPI_MasterManager.h
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

#ifndef SPI_MASTERMANAGER_H
#define SPI_MASTERMANAGER_H

/*******************************************************************************************************************************************
 *  												Includes
 *******************************************************************************************************************************************/

#include <Arduino.h>
#include "../../lib/SlaveSPI/SlaveSPI.h"
#include <SPI.h>
#include "./SPI_Slave.h"

#include "../Definition/LocalDef.h"
#include "../../lib/Definition/GlobalDef.h"
#include "../../lib/Logger/Logger.h"

/*******************************************************************************************************************************************
 *  												WifiManager Class
 *******************************************************************************************************************************************/
/**
 * \brief Class to Manage the SPI Master
 */
class SPI_MasterManager
{
public:  

    SPI_Slave m_SPI_Slaves[SPI_MANAGER_NUMBER_SLAVES];    /** Array of slaves */

    /**
     * \brief Constructor.
     */
    SPI_MasterManager(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK);

    /**
     * \brief Destructor.
     */
    ~SPI_MasterManager();

    /**
     * \brief Function to set the Slave.
     *
     * \return Error Code.
     */  
    RC_e SetSlave(ESP32_Slave_e slave, uint8_t _CS);

    /**
     * \brief Function add a write request.
     *
     * \return Error Code.
     */  
    RC_e AddWriteRequest(ESP32_Slave_e slave, COM_REQUEST_REG_ID_e id, uint32_t data);

    /**
     * \brief Function send the requests to a slave.
     *
     * \return Error Code.
     */  
    RC_e SendRequests(ESP32_Slave_e slave);
    
    /**
     * \brief Function to execute the Manager.
     *
     * \return Error Code.
     */  
    RC_e Run();

    /**
     * \brief Function to set the Logger reference.
     * \param logger Pointer to reference the Logger object.
     *
     * \return Error Code.
     */  
    RC_e SetLogger(Logger* logger);
    
private:

    Logger* m_logger = NULL;    /** Reference to logger */
    SPISettings m_spi_setting;
    SPIClass m_master;

    /**
     * \brief Function to configure the SPI .
     *
     * \return Error Code.
     */
    RC_e SPIConfigure(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK);

    /**
     * \brief Function to send a request .
     *
     * \return Error Code.
     */
    RC_e SPI_TX_Request(COM_REQUEST_st request, uint8_t _CS);

    /**
     * \brief Function to Write a message using the Logger function.
     *
     * \return Error Code.
     */
    RC_e LoggerWrite(char* msg);



   

};

#endif // SPI_MASTERMANAGER_H