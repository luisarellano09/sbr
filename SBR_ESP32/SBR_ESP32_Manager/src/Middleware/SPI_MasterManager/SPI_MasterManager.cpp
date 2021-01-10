/**
 * @file SPI_MasterManager.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief class to Manage the SPI Master
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */


/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "SPI_MasterManager.h"
#include "../../lib/Utility/Utility.h"

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

SPI_MasterManager::SPI_MasterManager(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK){

    SPIConfigure(clock, _MO, _MI, _MCLK);

    // Clear Chip Selects
    for (int i=0; i<ESP32_SPI_Slave_e::SLAVE_LENGTH; i++){
        this->m_SPI_Slaves[i].m_CS = 0;
    }
}

//=====================================================================================================
SPI_MasterManager::~SPI_MasterManager(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e SPI_MasterManager::ConnectTableRT(TableRT* tableRT){

    // Check if the pointer is null
    if (tableRT == NULL){
        Debug("Error: ERROR_NULL_POINTER in SPI_MasterManager::ConnectTableRT()");
        return RC_e::ERROR_NULL_POINTER;
    }

    this->m_tableRT = tableRT;

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::SetSlaveCS(ESP32_SPI_Slave_e slave, uint8_t _CS){

    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_SPI_Slaves[slave].m_CS = _CS;

    // Clean Buffer
    if ((retCode = this->m_SPI_Slaves[slave].CleanBuffer()) != RC_e::SUCCESS){
        Debug("Error: CleanBuffer in SPI_MasterManager::SetSlaveCS()");
        return retCode;
    }

    // Set the Chip Select to 1
    pinMode(_CS, OUTPUT);
    digitalWrite(_CS, HIGH);

    
    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::AddWriteRequest(ESP32_SPI_Slave_e slave, COM_REQUEST_REG_ID_e regId, uint32_t data){

    // Result code
    RC_e retCode = RC_e::ERROR;

    if ((retCode = this->m_SPI_Slaves[slave].AddRequest(COM_REQUEST_TYPE_e::WRITE, regId, data)) != RC_e::SUCCESS){
        Debug("Error: AddRequest in SPI_MasterManager::AddWriteRequest()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::SendWriteRequests(ESP32_SPI_Slave_e slave){
    // Result code
    RC_e retCode = RC_e::SUCCESS;
    RC_e tempRetCode = RC_e::SUCCESS;

    // Iterate to slaves
    for (int i=0; i<=this->m_SPI_Slaves[slave].m_RequestsArrayIndex; i++){
        if ( (tempRetCode = SPI_SendWriteRequest(this->m_SPI_Slaves[slave].m_RequestsArray[i], this->m_SPI_Slaves[slave].m_CS)) != RC_e::SUCCESS){
            Debug("Error: AddRequest in SPI_MasterManager::SendWriteRequests()");
            retCode = tempRetCode;
        }
        delayMicroseconds(50);
    }

    // Clean Buffer
     if ((tempRetCode = this->m_SPI_Slaves[slave].CleanBuffer()) != RC_e::SUCCESS){
        Debug("Error: CleanBuffer in SPI_MasterManager::SendWriteRequests()");
        return tempRetCode;
    }

    return retCode;
}

//=====================================================================================================
RC_e SPI_MasterManager::ReadSlaveRequests(ESP32_SPI_Slave_e slave){
    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if pointer is Null
    if (this->m_tableRT == NULL){
        Debug("Error: ERROR_NULL_POINTER in SPI_MasterManager::ReadSlaveRequests()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Stops counter
    uint8_t countStops = 0;
    
    // Iterate through the requests
    for (int i = 0; i< SPI_SLAVE_REQUESTS_ARRAY_SIZE; i++){
        // Request to read
        COM_REQUEST_st request;

        // check if counter max is reached
        if(countStops > SPI_MANAGER_NUMBER_STOP_EMPTY){
            return RC_e::SUCCESS;
        }
        
        // Read request
        if ((retCode = this->SPI_ReadSlaveRequest(&request, this->m_SPI_Slaves[slave].m_CS)) != RC_e::SUCCESS){
            Debug("Error: SPI_ReadSlaveRequest in SPI_MasterManager::ReadSlaveRequests()");
            return retCode;
        }

        // Check Answer
        if (request.comRequestType == COM_REQUEST_TYPE_e::STOP){
            countStops++;
        } else if (request.comRequestType == COM_REQUEST_TYPE_e::READ || request.comRequestType == COM_REQUEST_TYPE_e::WRITE){
            HandleReadSlaveRequest(&request);
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::EnableDebugMode(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_debugMode = true;

    // Iterate all slaves
    for (int i=0; i<ESP32_SPI_Slave_e::SLAVE_LENGTH; i++){
        if ((retCode = this->m_SPI_Slaves[i].EnableDebugMode()) != RC_e::SUCCESS){
            Debug("Error: EnableDebugMode in SPI_MasterManager::EnableDebugMode()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::DisableDebugMode(){
    // Result code
    RC_e retCode = RC_e::ERROR;

    this->m_debugMode = false;

    // Iterate all slaves
    for (int i=0; i<ESP32_SPI_Slave_e::SLAVE_LENGTH; i++){
        if ((retCode = this->m_SPI_Slaves[i].DisableDebugMode()) != RC_e::SUCCESS){
            Debug("Error: DisableDebugMode in SPI_MasterManager::DisableDebugMode()");
            return retCode;
        }
    }

    return RC_e::SUCCESS;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

//=====================================================================================================
RC_e SPI_MasterManager::SPIConfigure(uint32_t clock, uint8_t _MO, uint8_t _MI, uint8_t _MCLK){

    // Set values
    this->m_spi_setting = SPISettings(clock, MSBFIRST, SPI_MODE0);
    this->m_master = SPIClass(HSPI);  

    // Set pins
    pinMode(_MCLK, OUTPUT);     // Set clock as output
    digitalWrite(_MCLK, LOW);   // Due to SPI_MODE0

    // Begin SPI Master
    m_master.begin(_MCLK, _MI, _MO);    // Begin SPI master

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::SPI_SendWriteRequest(COM_REQUEST_st request, uint8_t _CS){

    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if CS exists
    if (_CS <= 0){
        Debug("Error: ERROR_NO_CS in SPI_MasterManager::SPI_SendWriteRequest()");
        return RC_e::ERROR_NO_CS;
    }

    // Buffer
    uint8_t _buffer[SPI_MANAGER_REQUEST_SIZE];

    // Convert request to buffer  
    if ((retCode = RequestToBuffer(&request, _buffer)) != RC_e::SUCCESS){
        Debug("Error: RequestToBuffer in SPI_MasterManager::SPI_SendWriteRequest()");
        return retCode;
    }
    
    // Begin transcation
    m_master.beginTransaction(m_spi_setting);
    digitalWrite(_CS, LOW);

    // Iterate all bytes from buffer
    for (int i=0; i<SPI_MANAGER_REQUEST_SIZE; i++){
        m_master.transfer(_buffer[i]);
    }

    // End Transaction
    digitalWrite(_CS, HIGH);
    m_master.endTransaction();

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::SPI_ReadSlaveRequest(COM_REQUEST_st* request, uint8_t _CS){

    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in SPI_MasterManager::SPI_ReadSlaveRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Check if CS exists
    if (_CS <= 0){
        Debug("Error: ERROR_NO_CS in SPI_MasterManager::SPI_ReadSlaveRequest()");
        return RC_e::ERROR_NO_CS;
    }

    // Buffer
    uint8_t _buffer[SPI_MANAGER_REQUEST_SIZE] = {0};

    // Begin Transaction
    m_master.beginTransaction(m_spi_setting);
    digitalWrite(_CS, LOW);

    // Read request
    m_master.transferBytes(_buffer, _buffer, SPI_MANAGER_REQUEST_SIZE);
    
    // End Transaction
    digitalWrite(_CS, HIGH);
    m_master.endTransaction();

    // Delay to wait for response
    delayMicroseconds(50); //100

    // Convert buffer to request
    if ((retCode = BufferToRequest(_buffer, request)) != RC_e::SUCCESS){
        Debug("Error: BufferToRequest in SPI_MasterManager::SPI_ReadSlaveRequest()");
        return retCode;
    }

    // Check CRC
    if (request->CRC != CalculateCrcFromRequest(request)){
        Debug("Error: CalculateCrcFromRequest in SPI_MasterManager::SPI_ReadSlaveRequest()");
        return RC_e::ERROR_CRC;
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::HandleReadSlaveRequest(COM_REQUEST_st* request){

    // Result code
    RC_e retCode = RC_e::ERROR;
    
    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in SPI_MasterManager::HandleReadSlaveRequest()");
        return RC_e::ERROR_NULL_POINTER;
    }

    if (request->comRequestRegId >= COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH || request->comRequestRegId < COM_REQUEST_REG_ID_e::REQUEST_INITIAL_RED_ID){
        Debug("Error: ERROR_INVALID_REG_ID in SPI_MasterManager::HandleReadSlaveRequest()");
        return RC_e::ERROR_INVALID_REG_ID;
    }

    // Types of Request from the Slave
    if (request->comRequestType == COM_REQUEST_TYPE_e::WRITE){

        // Serial.println("====== RX =======");
        // Serial.print("Req: ");
        // Serial.println(request->comRequestType);
        // Serial.print("ReqID: ");
        // Serial.println(request->comRequestRegId);
        // Serial.print("Data: ");
        // Serial.println(request->data);
        // Serial.print("CRC: ");
        // Serial.println(request->CRC);

        // Update Register
        if ((retCode = m_tableRT->UpdateRegister((COM_REQUEST_REG_ID_e)request->comRequestRegId, request->data)) != RC_e::SUCCESS){
            Debug("Error: UpdateRegister in SPI_MasterManager::HandleReadSlaveRequest()");
            return retCode;
        }

        // Add request to suscribers slaves
        if ((retCode = AddRequestToSubscribers(request)) != RC_e::SUCCESS){
            Debug("Error: UpdateRegister in SPI_MasterManager::AddRequestToSubscribers()");
            return retCode;
        }

    } else if (request->comRequestType == COM_REQUEST_TYPE_e::READ){
        //TODO implement read request
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::AddRequestToSubscribers(COM_REQUEST_st* request){

    // Result code
    RC_e retCode = RC_e::ERROR;

    // Check if the pointer is null
    if (request == NULL){
        Debug("Error: ERROR_NULL_POINTER in SPI_MasterManager::AddRequestToSubscribers()");
        return RC_e::ERROR_NULL_POINTER;
    }

    // Iterate through devices
    for (int i=0; i<Devices_e::DEVICE_LENGTH; i++){
        // Get subscriber
        Devices_e _subscriber = m_tableRT->m_Registers[(COM_REQUEST_REG_ID_e)request->comRequestRegId].m_subscribers[i];

        // Select the devices
        if (_subscriber == Devices_e::DEVICE_LINUX){
            //TODO implement Linux buffer
        } else if (_subscriber != Devices_e::DEVICE_NONE){
            if ((retCode = m_SPI_Slaves[_subscriber].AddRequest(COM_REQUEST_TYPE_e::WRITE, (COM_REQUEST_REG_ID_e)request->comRequestRegId, request->data)) != RC_e::SUCCESS){
                Debug("Error: AddRequest in SPI_MasterManager::AddRequestToSubscribers()");
                return retCode;
            }
        }
    }

    return RC_e::SUCCESS;
}

//=====================================================================================================
RC_e SPI_MasterManager::Debug(char* msg){
    if (this->m_debugMode){
        Serial.println(msg);
    }
    
    return RC_e::SUCCESS;
}