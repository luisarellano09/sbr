/**
 * \file Manager.cpp
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 26 April 2020
 *
 * \brief Class to Manager the ESP32.
 *
 * 
 * 
 * Changes
 * 30.04.2020: Add Wifimanager and logger instances.
 * 26.04.2020: Create Class.
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
#include "../../lib/Logger/Logger.h"
#include "../SPI_MasterManager/SPI_MasterManager.h"


/*******************************************************************************************************************************************
 *  												WifiManager Class
 *******************************************************************************************************************************************/

/**
 * \brief Class to Manage the ESP32.
 */
class Manager
{
public:  

    WifiManager* m_wifiManager = NULL;              /** Instance for Wifimanager. */
    SPI_MasterManager* m_SPI_MasterManager = NULL;  /** Instance for SPI Master Manager. */
    Logger* m_logger = NULL;                        /** Instance for Logger. */

    /**
     * \brief Constructor.
     */
    Manager();

    /**
     * \brief Destructor.
     */
    ~Manager();

   
private:


};

#endif // LOGGER_H