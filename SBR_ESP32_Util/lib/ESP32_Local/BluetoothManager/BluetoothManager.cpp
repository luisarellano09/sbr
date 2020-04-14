#include "BluetoothManager.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif



//####################### class BluetoothManager
/**
 * \brief Configuration the Bluetooth.
 */
BluetoothManager::BluetoothManager(const char* nameDevice){
    /*Set attributes*/
    this->m_nameDevice = nameDevice;

    configBluetooth();

}

BluetoothManager::~BluetoothManager(){}


void BluetoothManager::configBluetooth(){

    m_SerialBT.begin(this->m_nameDevice);           //name of device bluetooth
    m_SerialBT.setTimeout(TIME_OUT);                
}

RC_e BluetoothManager::CheckFrameAvaible(){
    
    RC_e retCode = RC_e::ERROR;

    if(m_SerialBT.available())
    {
        retCode = RC_e::SUCCESS;
    }
    return retCode;
}

RC_e BluetoothManager::ComputeCRC(const COM_FRAME_st* _frame)
{
    if(_frame==NULL)
    {
        return RC_e::ERROR_NULL_POINTER;
    }
    return RC_e::SUCCESS;
}

RC_e BluetoothManager::CheckFrame(uint8_t* _BufferLocal, COM_FRAME_st* _FrameLocal){
    RC_e retCode;

    /*Initialize*/
    retCode = RC_e::ERROR;

    if((_BufferLocal ==NULL) ||(_FrameLocal==NULL))
    {
        Serial.println("CheckFrame() => ERROR_NULL_POINTER");
        /*Clean all the register*/
        m_SerialBT.flush();
        return RC_e::ERROR_NULL_POINTER;
    }
    /*Initialize the buffer to all zeros*/
    for(int i= 0; i<(FRAME_SIZE + NUMBER_BYTES_NEW_LINE); i++)
    {
        _BufferLocal[i] = 0x00;
    }

    /* Read the buffer with the numers of bytes+2*/
    m_SerialBT.readBytes(_BufferLocal,FRAME_SIZE+NUMBER_BYTES_NEW_LINE);

    /*Condition to valid the all frame -> the last 2 bytes shall be \r\n */
    if((_BufferLocal[FRAME_SIZE+NUMBER_BYTES_NEW_LINE-2] != '\r') && (_BufferLocal[FRAME_SIZE+NUMBER_BYTES_NEW_LINE-1] != '\n')) // 0xD or 0xA
    {
        /*Clean all the register*/
        m_SerialBT.flush();
        return RC_e::ERROR_SIZE_BUFFER;         
    }
    /*---------REQUEST--------*/
    _FrameLocal->comFrameReq = _BufferLocal[0];

    /*------------ID----------*/
    _FrameLocal->comFrameRegId = _BufferLocal[1];

    /*------------DATA----------*/
    _FrameLocal->data = (_BufferLocal[2]);
    _FrameLocal->data += (_BufferLocal[3])<<8;
    _FrameLocal->data += (_BufferLocal[4])<<16;
    _FrameLocal->data += (_BufferLocal[5])<<24;

    /*|-----------------CRC-------------------|*/ 
    _FrameLocal->CRC = _BufferLocal[6];
    _FrameLocal->CRC += (_BufferLocal[7])<<8;
    
    /*function to compute CRC*/
    if((retCode=ComputeCRC(_FrameLocal))!=RC_e::SUCCESS)
    {
        /*Clean all the register*/
        m_SerialBT.flush();
        return retCode;         
    }

    /*Clean all the register*/
    m_SerialBT.flush();

    return retCode;
}

RC_e BluetoothManager::ExecuteFrame(COM_FRAME_st* _frame){
    RC_e retCode;

    /*initialize*/
    retCode = RC_e::ERROR;

    if(_frame == NULL)
    {
        return RC_e::ERROR_NULL_POINTER; 
    }
    
    Serial.println("==== TEST TRAMA =====");
    Serial.println(_frame->comFrameReq, HEX);
    Serial.println(_frame->comFrameRegId, HEX);
    Serial.println(_frame->data, HEX);
    Serial.println(_frame->CRC, HEX);
    Serial.println("====================");
    return RC_e::SUCCESS;
}

RC_e BluetoothManager::Run(){
    
    RC_e retCode;

    /*initialize variables*/
    retCode = RC_e::ERROR;

    // buffer to know if get the number of bytes corrects
    if((retCode=CheckFrameAvaible())!= RC_e::SUCCESS)
    {
        return retCode;
    }

    uint8_t BufferLocal[FRAME_SIZE + NUMBER_BYTES_NEW_LINE];
    COM_FRAME_st FrameLocal;

    /*initialize*/
    
    if((retCode=CheckFrame(BufferLocal, &FrameLocal))!= RC_e::SUCCESS){
        Serial.println("Run() => Error at CheckFrame()");
        return retCode;
    }

    if((retCode=ExecuteFrame(&FrameLocal))!= RC_e::SUCCESS){
        Serial.println("Run() => Error at ExecuteFrame()");
        return retCode;
    }

    return RC_e::SUCCESS;
}

