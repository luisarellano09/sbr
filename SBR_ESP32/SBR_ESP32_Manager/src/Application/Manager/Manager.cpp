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

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

Manager::Manager(){
    // Wifi Manager
    this->m_wifiManager = new WifiManager(WIFI_SSID, WIFI_PASSWORD, ESP32_HOSTNAME);

    // Nodes Manager
    this->m_nodeESP32 = new NodeEsp32(&Serial1, NODE_ESP32s_BAUDRATE, NODE_ESP32s_RX, NODE_ESP32s_TX);
    this->m_nodeLinux = new NodeLinux(&Serial2, NODE_ESP32s_BAUDRATE, 5, 18);

    // Table RT
    this->m_tableRegister = new RegisterTable(this->m_nodeESP32, this->m_nodeLinux);
    this->AddSubscribers();

    this->m_nodeESP32->ConnectRegisterTable(this->m_tableRegister);
}

//=====================================================================================================
Manager::~Manager(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/


//=====================================================================================================
RC_e Manager::EnableDebugMode(){
    this->m_debugMode = true;
    this->m_wifiManager->EnableDebugMode();
    this->m_nodeESP32->EnableDebugMode();
    this->m_nodeLinux->EnableDebugMode();
    this->m_tableRegister->EnableDebugMode();
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Manager::DisableDebugMode(){
    this->m_debugMode = false;
    this->m_wifiManager->DisableDebugMode();
    this->m_nodeESP32->DisableDebugMode();
    this->m_nodeLinux->DisableDebugMode();
    this->m_tableRegister->DisableDebugMode();
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e Manager::AddSubscribers(){

    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::REGISTER_50, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::REGISTER_51, DEVICE_e::ESP32_NODE02);
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Manager::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}