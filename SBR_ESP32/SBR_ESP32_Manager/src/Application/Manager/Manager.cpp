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
    this->m_tableRegister = new TableRegister(this->m_nodeESP32, this->m_nodeLinux);
    this->AddSubscribers();

    this->m_nodeESP32->ConnectTableRegister(this->m_tableRegister);
}

//=====================================================================================================
Manager::~Manager(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

void Manager::CommunicationTestStart(){
    m_TestingMode = true;
    this->CommunicationTestInit();    
}

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

    return RC_e::SUCCESS;
}

//=====================================================================================================
void Manager::CommunicationTestInit(){

    // for (uint16_t i=0; i<COM_REQUEST_REG_ID_e::LENGTH_REG_ID; i++ ){
    //     // Cleaning Subscribers
    //     this->m_tableRegister->m_registers[i].Clean();
    // }

    // // Iterate through Nodes to add subscribers
    // int nodeNumber = 2;
    // for (int node=0; node<nodeNumber; node++){
    //     for (int nodeSubs=0; nodeSubs<nodeNumber; nodeSubs++){
    //         if (nodeSubs != node){
    //             for (int registerOffset=0; registerOffset<10; registerOffset++){
    //                 int tempRegister = 100*nodeSubs + registerOffset;
    //                 this->m_tableRegister->AddSubscriber((COM_REQUEST_REG_ID_e)tempRegister, (DEVICE_e)node);
    //             }
    //         }
    //     }
    // }
}

//=====================================================================================================
RC_e Manager::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}