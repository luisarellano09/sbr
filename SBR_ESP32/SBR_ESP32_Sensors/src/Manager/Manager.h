/**
 * @file Manager.h
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * @version 1.0
 * @date 2020-06-13
 * 
 * 
 */

#ifndef MANAGER_H
#define MANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/

#include "../../lib/Definition/GlobalDef.h"
#include "../Definition/LocalDef.h"

#include "../../lib/WifiManager/WifiManager.h"
#include "../SPI_SlaveManager/SPI_SlaveManager.h"

/*******************************************************************************************************************************************
 *  												WifiManager Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the ESP32
 * 
 */
class Manager
{
public:  

    WifiManager* m_wifiManager = NULL;              /**< Instance for Wifimanager */
    SPI_SlaveManager* m_spiSlaveManager = NULL;     /**< Instance for SPI Slave manager */

    /**
     * @brief Construct a new Manager object
     * 
     */
    Manager();

    /**
     * @brief Destroy the Manager object
     * 
     */
    ~Manager();
   
private:


};

#endif // LOGGER_H