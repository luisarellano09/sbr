/**
 * @file Manager.h
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * 
 */

#ifndef MANAGER_H
#define MANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "../../Definition/Global/RC.h"
#include "../../Middleware/WifiManager/WifiManager.h"
#include "../CommunicationBus/NodeEsp32/NodeEsp32.h"
#include "../CommunicationBus/NodeLinux/NodeLinux.h"
#include "../CommunicationBus/RegisterTable/RegisterTable.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the ESP32
 * 
 */
class Manager {
public:  

    WifiManager* m_wifiManager = NULL;              /**@brief Instance for Wifimanager. */
    NodeEsp32* m_nodeESP32 = NULL;                  /**@brief Instance for the node ESP32. */
    NodeLinux* m_nodeLinux = NULL;                  /**@brief Instance for the node Manager. */
    RegisterTable* m_tableRegister = NULL;          /**@brief Instance for RT table. */

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

};

#endif // MANAGER_H