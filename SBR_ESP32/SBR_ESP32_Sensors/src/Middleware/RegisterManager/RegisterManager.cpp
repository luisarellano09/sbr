/**
 * @file RegisterManager.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the registers
 * @version 2.0
 * @date 10.01.2021
 * 
 * 
 */
/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "RegisterManager.h"

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

RegisterManager::RegisterManager(uint8_t _SO, uint8_t _SI, uint8_t _SCLK, uint8_t _SS)
    : SPI_SlaveManager(_SO, _SI, _SCLK, _SS){
}

//=====================================================================================================
RegisterManager::~RegisterManager(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e RegisterManager::Listen(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Listen Request
    if ((retCode = this->ListenRequest()) != RC_e::SUCCESS){
        Debug("Error: ListenRequest in RegisterManager::Listen()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
void RegisterManager::StartTestMode(){
    this->m_TestingMode = true;
}

//=====================================================================================================
RC_e RegisterManager::EnableDebugMode(){
    this->m_debugMode = true;
    this->SPI_SlaveManager::EnableDebugMode();
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e RegisterManager::DisableDebugMode(){
    this->m_debugMode = false;
    this->SPI_SlaveManager::DisableDebugMode();
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e RegisterManager::RegisterHandlerTesting(COM_REQUEST_REG_ID_e regId, int32_t data){
    // Result code
    RC_e retCode = RC_e::ERROR;

    int32_t incomingNode = regId/100;
    int32_t answerRegId = regId + 10 * ( (NODE_ID > incomingNode) ? (NODE_ID):(NODE_ID+1) );

    if ((retCode = this->AddWriteRequest((COM_REQUEST_REG_ID_e)answerRegId, data)) != RC_e::SUCCESS){
        Debug("Error: AddWriteRequest in RegisterManager::RegisterHandlerTesting()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												VIRTUAL METHODS
 *******************************************************************************************************************************************/

RC_e RegisterManager::RegisterHandler(COM_REQUEST_REG_ID_e regId, int32_t data){
    // Result code
    RC_e retCode = RC_e::ERROR;

    if (this->m_TestingMode) {
        if ((retCode = this->RegisterHandlerTesting(regId, data)) != RC_e::SUCCESS){
            Debug("Error: RegisterHandlerTesting in RegisterManager::RegisterHandler()");
            return retCode;
        }
    } else {
        Serial.println("======== REGISTER =========");
        Serial.print("Req: ");
        Serial.println(regId);
        Serial.print("Data: ");
        Serial.println(data);
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e RegisterManager::Debug(char* msg){
    if (this->m_debugMode) {
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}