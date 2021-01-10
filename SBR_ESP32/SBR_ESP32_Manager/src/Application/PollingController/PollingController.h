/**
 * @file PollingController.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to control the polling of communication
 * @version 1.0
 * @date 13-06-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef POLLINGCONTROLLER_H
#define POLLINGCONTROLLER_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/

#include "../../lib/Definition/GlobalDef.h"
#include "../../Definition/LocalDef.h"

#include "../../Middleware/SPI_MasterManager/SPI_MasterManager.h"
#include "../../Middleware/TableRT/TableRT.h"

/*******************************************************************************************************************************************
 *  												ENUMERATION
 *******************************************************************************************************************************************/

/**
 * @brief States for the ESP32 polling state machine
 * 
 */
enum StatePolling{
	IDLE,       /**< \brief IDLE state */
    SEND_REQ,   /**< \brief Send requests to slaves state */
    RECV_REQ,   /**< \brief Recieve requests from slaves state */
    DONE        /**< \brief Pooling Done */
};

/**
 * @brief Commands of ESP32 polling
 * 
 */
enum CommandPolling{
	START_POLLING,    /**< \brief Start ESP32 Polling*/
    STOP_POLLING      /**< \brief Stop ESP32 Polling*/
};


/*******************************************************************************************************************************************
 *  												Polling Controller Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to control the polling of communication
 * 
 */
class PollingController
{
public:  

    /**
     * @brief Construct a new Polling Controller object
     * 
     * @param spiMasterManager Reference of the SPI_MasterManager
     */
    PollingController(SPI_MasterManager* spiMasterManager);

    /**
     * @brief Destroy the Polling Controller object
     * 
     */
    ~PollingController();

    /**
     * @brief Function to run polling
     * 
     * @return RC_e Result code
     */
    RC_e Run();

    /**
     * @brief Start the state machine of polling
     * 
     * @return RC_e Result code
     */
    RC_e StartPolling();

    /**
     * @brief Stop the state machine of polling
     * 
     * @return RC_e 
     */
    RC_e StopPolling();

    /**
     * @brief Get the current state of the state machine of the polling controller
     * 
     * @return StatePolling 
     */
    StatePolling GetPollingControllerState();

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

    SPI_MasterManager* m_spiMasterManager;  /**< \brief Reference of the SPI_MasterManager object*/
    StatePolling m_currentStatePolling;     /**< \brief Current state of the Polling state machine*/
    StatePolling m_nextStatePolling;        /**< \brief Next state of the Polling state machine*/
    CommandPolling m_commandPolling;        /**< \brief Command of the Polling state machine*/
    
    bool m_debugMode = false;               /**< Debug Mode */

    /**
     * @brief State Machine of polling
     * 
     * @return RC_e Result code
     */
    RC_e SM_Polling();  

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);
};

#endif // POLLINGCONTROLLER_H