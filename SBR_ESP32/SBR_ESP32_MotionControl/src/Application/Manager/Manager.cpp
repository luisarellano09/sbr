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

    // Wifi Manager
    m_wifiManager = new WifiManager(WIFI_SSID, WIFI_PASSWORD, ESP32_HOSTNAME);

    // Register Manager
    m_registerManager = new RegisterManager(SO, SI, SCLK, SS);
}

//=====================================================================================================
Manager::~Manager(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e Manager::CommunicationTestStart(){
    m_TestingMode = true; 
    this->m_registerManager->StartTestMode();
}

//=====================================================================================================
RC_e Manager::CommunicationTestAnswer(){
    
}

//=====================================================================================================
RC_e Manager::EnableDebugMode(){
    this->m_debugMode = true;
    this->m_wifiManager->EnableDebugMode();
    this->m_registerManager->EnableDebugMode();
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Manager::DisableDebugMode(){
    this->m_debugMode = false;
    this->m_wifiManager->DisableDebugMode();
    this->m_registerManager->DisableDebugMode();
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e Manager::CommunicationTestPublish(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    if(this->m_TestingMode){
        int nodeOffset = 100*NODE_ID;
        for (int registerID = nodeOffset; registerID < nodeOffset + 10; registerID++){
            if ((retCode = this->m_registerManager->AddWriteRequest((COM_REQUEST_REG_ID_e)registerID, m_TestingCounter)) != RC_e::SUCCESS){
                Debug("Error: DisableDebugMode in SPI_MasterManager::DisableDebugMode()");
                return retCode;
            }
        }
        m_TestingCounter++;
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