/**
 * @file Manager.cpp
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Manager.h"
#include "../../Definition/Local/LocalConfig.h"
#include <ArduinoLog.h>

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

Manager::Manager(){

    // Wifi Manager
    this->m_wifiManager = new WifiManager();
    Log.traceln("[Manager::Manager] WifiManager instanced");

    // Nodes Manager
    this->m_nodeESP32 = new NodeEsp32(&Serial1, NODE_ESP32s_BAUDRATE, NODE_ESP32s_RX, NODE_ESP32s_TX);
    Log.traceln("[Manager::Manager] NodeEsp32 instanced");
    this->m_nodeLinux = new NodeLinux(&Serial2, NODE_ESP32s_BAUDRATE, 5, 18);
    Log.traceln("[Manager::Manager] NodeLinux instanced");

    // Table RT
    this->m_tableRegister = new RegisterTable(this->m_nodeESP32, this->m_nodeLinux);
    Log.traceln("[Manager::Manager] RegisterTable instanced");

    // Add Subscribers
    this->AddSubscribers();
    Log.traceln("[Manager::Manager] Subscribers added");

    // Connect table to Nodes
    this->m_nodeESP32->ConnectRegisterTable(this->m_tableRegister);
    Log.traceln("[Manager::Manager] Table connected to node ESP32");

    // Start Node 
    this->m_nodeESP32->Start();
    Log.traceln("[Manager::Manager] NodeEsp32 started");

    Log.traceln("[Manager::Manager] Manager initialization finished");
}


//=====================================================================================================

Manager::~Manager(){}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/



/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e Manager::AddSubscribers(){
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::REGISTER_50, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::REGISTER_51, DEVICE_e::ESP32_NODE02);
    return RC_e::SUCCESS;
}
