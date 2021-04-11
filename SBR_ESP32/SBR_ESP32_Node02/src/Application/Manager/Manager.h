/**
 * @file Manager.h
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * @version 2.0
 * @date 10.01.2021
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

#include "../Communication/Node01/Node01.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the ESP32
 * 
 */
class Manager {
public:  

    WifiManager* m_wifiManager = NULL;              /**< Instance for Wifimanager */
    Node01* m_node01 = NULL;

    /**
     * @brief Construct a new Manager object
     * 
     */
    Manager();

    /**
     * @brief Destroy the Manager object
     * saga falabella peru 
     * 
     */
    ~Manager();

    /**
     * @brief Function to start testing the communication system
     * 
     * @return RC_e Result code
     */
    RC_e CommunicationTestStart();

    /**
     * @brief Function to publish registers to test the communication system
     * 
     * @return RC_e Result code
     */
    RC_e CommunicationTestPublish();

    /**
     * @brief Function to check the test of the communication system
     * 
     * @return RC_e Result code
     */
    RC_e CommunicationTestAnswer(COM_REQUEST_REG_ID_e regId, int32_t data);

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
    int32_t m_TestingCounter = 0;   /**< Counter of testing mode. */
    bool m_debugMode = false;       /**< Debug Mode */

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // LOGGER_H