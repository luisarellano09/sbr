/**
 * @file Manager.cpp
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * @version 2.0
 * @date 10.01.2021
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

    // Wifi
    this->m_wifiManager = new WifiManager(WIFI_SSID, WIFI_PASSWORD, ESP32_HOSTNAME);

    // Node
    this->m_node01 = new Node01(&Serial1, NODE_ESP32s_BAUDRATE, NODE_ESP32s_RX, NODE_ESP32s_TX);

}

//=====================================================================================================
Manager::~Manager(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e Manager::CommunicationTestStart(){
    m_TestingMode = true; 
}

//=====================================================================================================
RC_e Manager::EnableDebugMode(){
    this->m_debugMode = true;
    this->m_wifiManager->EnableDebugMode();
    this->m_node01->EnableDebugMode();
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Manager::DisableDebugMode(){
    this->m_debugMode = false;
    this->m_wifiManager->DisableDebugMode();
    this->m_node01->DisableDebugMode();
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e Manager::CommunicationTestPublish(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    int32_t nodeId = DEVICE_e::ESP32_NODE01;

    if (this->m_TestingMode){
        int nodeOffset = 100*nodeId;
        for (int registerID = nodeOffset; registerID < nodeOffset + 10; registerID++){
            if ((retCode = this->m_node01->AddRequest(DEVICE_e::MANAGER, COM_REQUEST_TYPE_e::WRITE, (COM_REQUEST_REG_ID_e)registerID, m_TestingCounter)) != RC_e::SUCCESS){
                Debug("Error: DisableDebugMode in SPI_MasterManager::DisableDebugMode()");
                return retCode;
            }
        }
        m_TestingCounter++;
    }

    return RC_e::SUCCESS;
}

RC_e Manager::CommunicationTestAnswer(COM_REQUEST_REG_ID_e regId, int32_t data){
    // Result code
    RC_e retCode = RC_e::ERROR;

    int32_t nodeId = DEVICE_e::ESP32_NODE01;
    int32_t incomingNode = regId/100;
    int32_t answerRegId = regId + 10 * ( (nodeId > incomingNode) ? (nodeId):(nodeId+1) );

    if ((retCode = this->m_node01->AddRequest(DEVICE_e::MANAGER, COM_REQUEST_TYPE_e::WRITE, (COM_REQUEST_REG_ID_e)answerRegId, data)) != RC_e::SUCCESS){
        Debug("Error: AddWriteRequest in NodeManager::RegisterHandlerTesting()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Manager::Debug(char* msg){
    if (this->m_debugMode) {
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}