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
 * 26.04.2020: Create Class
 * 
 *
 */


/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "Manager.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/
Manager::Manager(){

    // Wifi Manager
    m_WifiManager = new WifiManager(WIFI_SSID, WIFI_PASSWORD, ESP32_HOSTNAME);

    // Table RT
    m_TableRT = new TableRT();
    AddSubscribers();
    
    // SPI Master Manager
    m_SPI_MasterManager = new SPI_MasterManager(SPI_CLOCK, MO, MI, MCLK);
    m_SPI_MasterManager->ConnectTableRT(m_TableRT);
    AddSlavesCS();

    // Polling Controller
    m_PollingController = new PollingController(m_SPI_MasterManager);
}

Manager::~Manager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/


/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

RC_e Manager::AddSubscribers(){
    m_TableRT->AddSubscriber(COM_REQUEST_REG_ID_e::R0, Devices_e::DEVICE_MOTION);
}

RC_e Manager::AddSlavesCS(){
    m_SPI_MasterManager->SetSlave(ESP32_Slave_e::SLAVE_MOTION, MOTION_CS);   // ESP32 - Motion Control
}