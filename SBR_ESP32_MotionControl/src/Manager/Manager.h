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

#include "../../lib/SBR_Global/Definition/GlobalDef.h"
#include "../../lib/SBR_Global/WifiManager/WifiManager.h"
#include "../../lib/SBR_Global/Logger/Logger.h"


/*******************************************************************************************************************************************
 *  												DEFINE
 *******************************************************************************************************************************************/

#define SSID "ap01"
#define PASSWORD "12345678"
#define HOSTNAME "SBR_ESP32_MotionControl"
#define LOGGERPORT (uint16_t)4001
#define LOGGERHOST "ubuntudev"


/*******************************************************************************************************************************************
 *  												WifiManager Class
 *******************************************************************************************************************************************/

/**
 * \brief Class to Manage the ESP32.
 */
class Manager
{
public:  

    WifiManager* m_wifiManager = NULL;  /** Instance for Wifimanager */
    Logger* m_logger = NULL;            /** Instance for Logger */

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