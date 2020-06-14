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
#include "../Definition/LocalDef.h"

#include "../SPI_MasterManager/SPI_MasterManager.h"
#include "../TableRT/TableRT.h"

/*******************************************************************************************************************************************
 *  												ENUMERATION
 *******************************************************************************************************************************************/

/**
 * @brief States for the ESP32 polling state machine
 * 
 */
enum StateEsp32Polling{
	IDLE,       /**< \brief IDLE state */
    SEND_REQ,   /**< \brief Send requests to slaves state */
    RECV_REQ    /**< \brief Recieve requests from slaves state */
};

/**
 * @brief Commands of ESP32 polling
 * 
 */
enum CommandEsp32Polling{
	ESP32_POLLING_START,    /**< \brief Start ESP32 Polling*/
    ESP32_POLLING_STOP      /**< \brief Stop ESP32 Polling*/
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
     * @brief Function to run polling on ESP32s
     * 
     * @return RC_e Result code
     */
    RC_e RunESP32();


    /**
     * @brief top the state machine of polling between the ESP32
     * 
     * @return RC_e Result code
     */
    RC_e StartEsp32Polling();

    /**
     * @brief top the state machine of polling between the ESP32
     * 
     * @return RC_e 
     */
    RC_e StopEsp32Polling();

   
private:

    SPI_MasterManager* m_spiMasterManager;          /**< \brief Reference of the SPI_MasterManager object*/
    StateEsp32Polling m_currentStateEsp32Polling;   /**< \brief Current state of the ESP32 Polling state machine*/
    StateEsp32Polling m_nextStateEsp32Polling;      /**< \brief Next state of the ESP32 Polling state machine*/
    CommandEsp32Polling m_commandEsp32Polling;      /**< \brief Command of the ESP32 Polling state machine*/
    

    /**
     * @brief State Machine of polling between the ESP32
     * 
     * @return RC_e Result code
     */
    RC_e SM_Esp32Polling();  


};

#endif // POLLINGCONTROLLER_H