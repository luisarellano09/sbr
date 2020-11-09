/**
 * @file RegisterManager.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the registers
 * @version 1.0
 * @date 14-06-2020
 * 
 * 
 */

#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

/*******************************************************************************************************************************************
 *  												Includes
 *******************************************************************************************************************************************/

#include <Arduino.h>

#include "../../src/Definition/LocalDef.h"
#include "../../lib/Definition/GlobalDef.h"

#include "../../lib/SPI_SlaveManager/SPI_SlaveManager.h"


/*******************************************************************************************************************************************
 *  												SPI Slave Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the registers
 * 
 */
class RegisterManager: public SPI_SlaveManager
{


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

    RC_e RegisterHandler(COM_REQUEST_REG_ID_e regId, uint32_t data);
    
private:

   
   
};

#endif // REGISTERMANAGER_H