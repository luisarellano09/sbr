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

#include "../../Definition/GlobalDef.h"
#include "../../Definition/LocalDef.h"

#include "../../Middleware/WifiManager/WifiManager.h"

#include "../Communication/NodeEsp32/NodeEsp32.h"
#include "../Communication/NodeLinux/NodeLinux.h"
#include "../Communication/TableRegister/TableRegister.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief lass to Manage the ESP32
 * 
 */
class Manager {
public:  

    WifiManager* m_wifiManager = NULL;              /**< \brief Instance for Wifimanager. */
    NodeEsp32* m_nodeESP32 = NULL;  /**< \brief Instance for SPI Master Manager. */
    NodeLinux* m_nodeLinux = NULL;  /**< \brief Instance for SPI Master Manager. */
    TableRegister* m_tableRegister = NULL;                      /**< \brief Instance for RT table. */

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
     * @brief Function to start testing the communication system
     * 
     */
    void CommunicationTestStart();

    /**
     * @brief Function to check the communication system
     * 
     */
    void CommunicationTestCheck();

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
   

    int32_t m_TestingNodeValues[10] = {0};
    int32_t m_TestingNodeResultCorrect[10] = {0};
    int32_t m_TestingNodeResultError[10] = {-1, -1, -1, -1, -1};

private:

    bool m_TestingMode = false;   /**< \brief Flag of testing mode. */
    bool m_debugMode = false;     /**< Debug Mode */

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

    /**
     * @brief Function to init the test of the communication system
     * 
     */
    void CommunicationTestInit();

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // MANAGER_H