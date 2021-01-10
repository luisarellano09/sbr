/**
 * @file RegisterManager.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the registers
 * @version 2.0
 * @date 10.01.2021
 * 
 * 
 */

#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/

#include <Arduino.h>

#include "../../src/Definition/LocalDef.h"
#include "../../lib/Definition/GlobalDef.h"

#include "../../lib/Middleware/SPI_SlaveManager/SPI_SlaveManager.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the registers
 * 
 */
class RegisterManager: public SPI_SlaveManager {


public:  

    /**
     * @brief Construct a new spi slavemanager object
     * 
     * @param _SO Slave Output pin
     * @param _SI Slave Input pin
     * @param _SCLK Slave clock pin
     * @param _SS Slave Select pin
     */
    RegisterManager(uint8_t _SO, uint8_t _SI, uint8_t _SCLK, uint8_t _SS);

    /**
     * @brief Destroy the spi slavemanager object
     * 
     */
    ~RegisterManager();

    /**
     * @brief Listen Requests
     * 
     */
    RC_e Listen();

    /**
     * @brief Function to start testing mode
     * 
     */
    void StartTestMode();

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

    bool m_TestingMode = false;     /**< Flag of testing mode. */
    bool m_debugMode = false;       /**< Debug Mode */

    RC_e RegisterHandlerTesting(COM_REQUEST_REG_ID_e regId, int32_t data);

    /**
     * @brief Register Handler
     * 
     * @param regId Register ID
     * @param data Data value
     * @return RC_e Result code
     */
    RC_e RegisterHandler(COM_REQUEST_REG_ID_e regId, int32_t data);

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);
   
};

#endif // REGISTERMANAGER_H