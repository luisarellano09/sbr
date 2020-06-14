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
#include "../SPI_MasterManager/SPI_MasterManager.h"
#include "../TableRT/TableRT.h"
#include "../PollingController/PollingController.h"


/*******************************************************************************************************************************************
 *  												MANAGER Class
 *******************************************************************************************************************************************/

/**
 * @brief lass to Manage the ESP32
 * 
 */
class Manager
{
public:  

    WifiManager* m_WifiManager = NULL;              /**< \brief Instance for Wifimanager. */
    SPI_MasterManager* m_SPI_MasterManager = NULL;  /**< \brief Instance for SPI Master Manager. */
    TableRT* m_TableRT = NULL;                      /**< \brief Instance for RT table. */
    PollingController* m_PollingController = NULL;  /**< \brief Instance for Polling Controller. */

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

    /**
     * @brief Add Subscribers to the Table
     * 
     * @return RC_e Result code
     */
    RC_e AddSubscribers();

    /**
     * @brief Add Chip Select of the Slaves
     * 
     * @return RC_e Result code
     */
    RC_e AddSlavesCS();

};

#endif // MANAGER_H