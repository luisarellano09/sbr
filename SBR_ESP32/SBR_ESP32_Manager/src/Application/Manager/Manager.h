/**
 * @file Manager.h
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * @version 2.0
 * @date 09.01.2021
 * 
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
    NodeEsp32* m_nodeESP32 = NULL;                  /**@brief Instance for SPI Master Manager. */
    NodeLinux* m_nodeLinux = NULL;                  /**@brief Instance for SPI Master Manager. */
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

    bool m_debugMode = false;     /**< Debug Mode */

    /**
     * @brief Add Subscribers to the Table
     * 
     * @return RC_e Result code
     */
    RC_e AddSubscribers();

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // MANAGER_H