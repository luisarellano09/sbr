/**
 * \file PollingController.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 08 Jun 2020
 *
 * \brief Class to describe a register of the Data Table in Runtime.
 *
 * 
 * 
 * Changes
 * 07.06.2020: Create Class.
 * 
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
/** \brief  States for the ESP32 polling.  */
enum StateEsp32Polling{
	IDLE,
    SEND_REQ,
    RECV_REQ
};

/** \brief  States for the ESP32 polling.  */
enum CommandEsp32Polling{
	ESP32_POLLING_START,
    ESP32_POLLING_STOP
};


/*******************************************************************************************************************************************
 *  												TableRT Class
 *******************************************************************************************************************************************/

/**
 * \brief Class to describe the Data Table in Runtime.
 */
class PollingController
{
public:  

    /**
     * \brief Constructor.
     */
    PollingController(SPI_MasterManager* spiMasterManager);

    /**
     * \brief Destructor.
     */
    ~PollingController();

    /**
     * \brief Function to run polling.
     */
    RC_e RunESP32();

    /**
     * \brief Start the state machine of polling between the ESP32.
     */
    RC_e StartEsp32Polling();

    /**
     * \brief Stop the state machine of polling between the ESP32.
     */
    RC_e StopEsp32Polling();

   
private:

    SPI_MasterManager* m_spiMasterManager;

    StateEsp32Polling m_currentStateEsp32Polling;
    StateEsp32Polling m_nextStateEsp32Polling;
    CommandEsp32Polling m_commandEsp32Polling;
    

    /**
     * \brief State Machine of polling between the ESP32.
     */
    RC_e SM_Esp32Polling();  


};

#endif // POLLINGCONTROLLER_H