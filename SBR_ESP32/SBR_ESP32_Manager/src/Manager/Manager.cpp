/**
 * @file Manager.cpp
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * @version 1.0
 * @date 2020-06-13
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

//=====================================================================================================
Manager::Manager(){

    // Wifi Manager
    this->m_WifiManager = new WifiManager(WIFI_SSID, WIFI_PASSWORD, ESP32_HOSTNAME);

    // Table RT
    this->m_TableRT = new TableRT();
    AddSubscribers();
    
    // SPI Master Manager
    this->m_SPI_MasterManager = new SPI_MasterManager(SPI_CLOCK, MO, MI, MCLK);
    this->m_SPI_MasterManager->ConnectTableRT(m_TableRT);
    AddSlavesCS();

    // Polling Controller
    this->m_PollingController = new PollingController(m_SPI_MasterManager);
}

//=====================================================================================================
Manager::~Manager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/


/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e Manager::AddSubscribers(){
    // R2
    this->m_TableRT->AddSubscriber(COM_REQUEST_REG_ID_e::TEST_R02, Devices_e::DEVICE_SENSOR);
    // R3
    this->m_TableRT->AddSubscriber(COM_REQUEST_REG_ID_e::TEST_R03, Devices_e::DEVICE_SENSOR);
    // R4
    this->m_TableRT->AddSubscriber(COM_REQUEST_REG_ID_e::TEST_R04, Devices_e::DEVICE_SENSOR);
    // R5
    this->m_TableRT->AddSubscriber(COM_REQUEST_REG_ID_e::TEST_R05, Devices_e::DEVICE_SENSOR);
    // R6
    this->m_TableRT->AddSubscriber(COM_REQUEST_REG_ID_e::TEST_R06, Devices_e::DEVICE_SENSOR);
    // R7
    this->m_TableRT->AddSubscriber(COM_REQUEST_REG_ID_e::TEST_R07, Devices_e::DEVICE_SENSOR);
    // R8
    this->m_TableRT->AddSubscriber(COM_REQUEST_REG_ID_e::TEST_R08, Devices_e::DEVICE_SENSOR);
    // R9
    this->m_TableRT->AddSubscriber(COM_REQUEST_REG_ID_e::TEST_R09, Devices_e::DEVICE_SENSOR);

}

//=====================================================================================================
RC_e Manager::AddSlavesCS(){
    // ESP32 - Motion Control
    this->m_SPI_MasterManager->SetSlaveCS(ESP32_Slave_e::SLAVE_MOTION, MOTION_CS);
    // ESP32 - Sensors
    this->m_SPI_MasterManager->SetSlaveCS(ESP32_Slave_e::SLAVE_SENSOR, SENSORS_CS);   
}