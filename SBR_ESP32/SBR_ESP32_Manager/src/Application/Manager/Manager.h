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

#include "../../lib/Definition/GlobalDef.h"
#include "../../Definition/LocalDef.h"

#include "../../lib/Middleware/WifiManager/WifiManager.h"
#include "../../Middleware/SPI_MasterManager/SPI_MasterManager.h"
#include "../../Middleware/TableRT/TableRT.h"
#include "../PollingController/PollingController.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief lass to Manage the ESP32
 * 
 */
class Manager {
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