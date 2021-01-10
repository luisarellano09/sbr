/**
 * @file SPI_MasterManager.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief class to Manage the SPI Master
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */


#ifndef SPI_MASTERMANAGER_H
#define SPI_MASTERMANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/

#include <Arduino.h>
#include <SPI.h>

#include "../../Definition/LocalDef.h"
#include "../../lib/Definition/GlobalDef.h"

#include "../TableRT/TableRT.h"
#include "../SPI_Slave/SPI_Slave.h"

#include <soc/spi_struct.h>

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the SPI Master
 * 
 */
class SPI_MasterManager {
public:  

    /**
     * @brief Construct a new spi mastermanager object
     * 
     * @param clock Clock speed Hz
     * @param _MO MOSI pin
     * @param _MI MISO pin
     * @param _MCLK Clock pin
     */
    SPI_MasterManager(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK);

    /**
     * @brief Destroy the spi mastermanager object
     * 
     */
    ~SPI_MasterManager();

    /**
     * @brief Function to connect to the tableRT pointer
     * 
     * @param tableRT Reference to the TableRT object
     * @return RC_e Result code
     */
    RC_e ConnectTableRT(TableRT* tableRT);

    /**
     * @brief SFunction to set the Slave chip select
     * 
     * @param slave ESP32 Slave
     * @param _CS Chip select pin
     * @return RC_e Result code
     */
    RC_e SetSlaveCS(ESP32_SPI_Slave_e slave, uint8_t _CS);

    /**
     * @brief Function add a write request
     * 
     * @param slave ESP32 Slave
     * @param regId Register ID
     * @param data Data Value
     * @return RC_e Result code
     */
    RC_e AddWriteRequest(ESP32_SPI_Slave_e slave, COM_REQUEST_REG_ID_e regId, uint32_t data);

    /**
     * @brief Function send the requests to a slave   
     * 
     * @param slave ESP32 Slave
     * @return RC_e Result code
     */
    RC_e SendWriteRequests(ESP32_SPI_Slave_e slave);

    /**
     * @brief Function get the requests from a slave
     * 
     * @param slave ESP32 Slave
     * @return RC_e Result code
     */
    RC_e ReadSlaveRequests(ESP32_SPI_Slave_e slave);

    /**
     * @brief Enable the debug mode of the class
     * 
     * @return RC_e Result code
     */
    RC_e EnableDebugMode();

    /**
     * @brief Disable the debug mode of the class
     * 
     * @return RC_e Result code
     */
    RC_e DisableDebugMode();

private:

    SPISettings m_spi_setting;                                  /**< \brief SPI setting object */
    SPIClass m_master;                                          /**< \brief SPI master object */
    SPI_Slave m_SPI_Slaves[ESP32_SPI_Slave_e::SLAVE_LENGTH];    /**< \brief Array of SPI Slaves */
    TableRT* m_tableRT = NULL;                                  /**< \brief Reference of the TableRT object */

    bool m_debugMode = false;                                   /**< Debug Mode */

    /**
     * @brief Function to configure the SPI
     * 
     * @param clock Clock speed Hz
     * @param _MO MOSI pin
     * @param _MI MISO pin
     * @param _MCLK Clock pin
     * @return RC_e Result code
     */
    RC_e SPIConfigure(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK);

    /**
     * @brief Function to send a request through SPI
     * 
     * @param request Request
     * @param _CS Chip select pin
     * @return RC_e Result code
     */
    RC_e SPI_SendWriteRequest(COM_REQUEST_st request, uint8_t _CS);

    /**
     * @brief Function to send a request
     * 
     * @param request Reference of a request object
     * @param _CS Chip select pin
     * @return RC_e Result code
     */
    RC_e SPI_ReadSlaveRequest(COM_REQUEST_st* request, uint8_t _CS);

    /**
     * @brief Function to handle a read slave request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e HandleReadSlaveRequest(COM_REQUEST_st* request);

    /**
     * @brief Function to add a request to the subscribed slaves
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e AddRequestToSubscribers(COM_REQUEST_st* request);

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // SPI_MASTERMANAGER_H