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
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

void Manager::CommunicationTestStart(){
    m_TestingMode = true;
    this->CommunicationTestInit();    
}

//=====================================================================================================
void Manager::CommunicationTestCheck(){
    if (this->m_TestingMode){
        if (this->m_PollingController->GetPollingControllerState() == StatePolling::DONE){
            
            int nodeNumber = 2;
            for (int node=0; node<nodeNumber; node++){

                int resultFlag = 0;
                // Get limits
                int registerOffset = node*100 + 10;
                int registeMax = node*100 + nodeNumber*10;
                int nodeGroupValue = m_TableRT->m_Registers[registeMax-1].m_value;

                if ( nodeGroupValue != m_TestingNodeValues[node]) {
                    // Iteration
                    for (int registerID = registerOffset; registerID<registeMax; registerID++){
                        int32_t registerAnswerValue = m_TableRT->m_Registers[registerID].m_value;
                        //Serial.printf("\r\nNode(%d) \t\tPreviuos: %d \t\t New: %d", node, m_TestingNodeValues[node], registerAnswerValue);
                        if ( registerAnswerValue == m_TestingNodeValues[node] + 1 ){
                            resultFlag = 1;
                        } else {
                            resultFlag = 0;
                            break;
                        }
                    }

                    // Check result  
                    if (resultFlag) {
                        m_TestingNodeResultCorrect[node]++;
                    } else {
                        m_TestingNodeResultError[node]++;
                    }  

                    m_TestingNodeValues[node] = nodeGroupValue;                         
                }    
            }
        }
    }
}

//=====================================================================================================
RC_e Manager::EnableDebugMode(){
    this->m_debugMode = true;
    this->m_WifiManager->EnableDebugMode();
    this->m_SPI_MasterManager->EnableDebugMode();
    this->m_TableRT->EnableDebugMode();
    this->m_PollingController->EnableDebugMode();

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e Manager::DisableDebugMode(){
    this->m_debugMode = false;
    this->m_WifiManager->DisableDebugMode();
    this->m_SPI_MasterManager->DisableDebugMode();
    this->m_TableRT->DisableDebugMode();
    this->m_PollingController->DisableDebugMode();
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
RC_e Manager::AddSlavesCS(){
    // ESP32 - Motion Control
    this->m_SPI_MasterManager->SetSlaveCS(ESP32_SPI_Slave_e::SLAVE_NODE01, ESP32_NODE01_CS);
    // ESP32 - Sensors
    this->m_SPI_MasterManager->SetSlaveCS(ESP32_SPI_Slave_e::SLAVE_NODE02, ESP32_NODE02_CS);  
    // ESP32 - Util
    //this->m_SPI_MasterManager->SetSlaveCS(ESP32_SPI_Slave_e::SLAVE_UTIL, ESP32_UTIL_CS);  

    return RC_e::SUCCESS; 
}

//=====================================================================================================
void Manager::CommunicationTestInit(){

    for (int i=0; i<COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH; i++ ){
        // Cleaning Subscribers
        this->m_TableRT->m_Registers[i].CleanSubscribers();
    }

    // Iterate through Nodes to add subscribers
    int nodeNumber = 2;
    for (int node=0; node<nodeNumber; node++){
        for (int nodeSubs=0; nodeSubs<nodeNumber; nodeSubs++){
            if (nodeSubs != node){
                for (int registerOffset=0; registerOffset<10; registerOffset++){
                    int tempRegister = 100*nodeSubs + registerOffset;
                    this->m_TableRT->AddSubscriber((COM_REQUEST_REG_ID_e)tempRegister, (Devices_e)node);
                }
            }
        }
    }
}

//=====================================================================================================
RC_e Manager::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}