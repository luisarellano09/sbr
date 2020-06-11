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
#include <SPI.h>
#include "SPI_Slave.h"

#include "../Definition/LocalDef.h"
#include "../../lib/Definition/GlobalDef.h"

#include "../TableRT/TableRT.h"

/*******************************************************************************************************************************************
 *  												SPI Master Class
 *******************************************************************************************************************************************/
/**
 * \brief Class to Manage the SPI Master
 */
class SPI_MasterManager
{
public:  

    /**
     * \brief Constructor.
     */
    SPI_MasterManager(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK);

    /**
     * \brief Destructor.
     */
    ~SPI_MasterManager();

    /**
     * \brief Function to connect to the tableRT pointer.
     *
     * \return Error Code.
     */  
    RC_e ConnectTableRT(TableRT* tableRT);

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
    RC_e SendWriteRequests(ESP32_Slave_e slave);

    /**
     * \brief Function get the requests from a slave.
     *
     * \return Error Code.
     */  
    RC_e ReadSlaveRequests(ESP32_Slave_e slave);
    
private:

    SPISettings m_spi_setting;
    SPIClass m_master;
    SPI_Slave m_SPI_Slaves[ESP32_Slave_e::SLAVE_LENGTH];    /** Array of slaves */
    TableRT* m_tableRT = NULL;

    /**
     * \brief Function to configure the SPI .
     *
     * 
     * \return Error Code.
     */
    RC_e SPIConfigure(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK);

    /**
     * \brief Function to send a request .
     *
     * \return Error Code.
     */
    RC_e SPI_SendWriteRequest(COM_REQUEST_st request, uint8_t _CS);

    /**
     * \brief Function to send a request .
     *
     * \return Error Code.
     */
    RC_e SPI_ReadSlaveRequest(COM_REQUEST_st* request, uint8_t _CS);

    /**
     * \brief Function to handle a read slave request .
     *
     * \return Error Code.
     */
    RC_e HandleReadSlaveRequest(COM_REQUEST_st* request);

    /**
     * \brief Function Add a request to the subscribed slave 
     *
     * \return Error Code.
     */
    RC_e AddRequestToSubscriber(COM_REQUEST_st* request);



};

#endif // SPI_MASTERMANAGER_H