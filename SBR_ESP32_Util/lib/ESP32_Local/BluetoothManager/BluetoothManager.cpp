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
    m_SerialBT.setTimeout(TIME_OUT);                   //100 miliseconds
}

RC_e BluetoothManager::CheckFrameAvaible(){
    
    RC_e retCode = RC_e::ERROR;

    if(m_SerialBT.available())
    {
        retCode = RC_e::SUCCESS;
    }
    return retCode;
}

RC_e BluetoothManager::CheckFrame(uint8_t* _BufferLocal){
    RC_e retCode;

    /*Initialize*/
    retCode = RC_e::ERROR;

    /*Initialize the buffer to all zeros*/
    for(int i= 0; i<FRAME_SIZE+NUMBER_BYTES_NEW_LINE; i++)
    {
        _BufferLocal[i] = 0x00;
    }

    /* Read the buffer with the numers of bytes+2*/
    m_SerialBT.readBytes(_BufferLocal,FRAME_SIZE+NUMBER_BYTES_NEW_LINE);

    /*Condition to valid the all frame -> the last 2 bytes shall be \r\n */
    if((_BufferLocal[FRAME_SIZE+NUMBER_BYTES_NEW_LINE-2] != '\r') && (_BufferLocal[FRAME_SIZE+NUMBER_BYTES_NEW_LINE-1] != '\n')) // 0xD or 0xA
    {
        return RC_e::ERROR_SIZE_BUFFER;         
    }
    /*function to compute CRC*/
    /*crc16 = computeCRC(_frame)  */

    /*if((retCode=CheckCRC(_frame))!=RC_e::SUCCESS)
    {
        return retCode;         
    }*/
    /*Clean all the register*/
    m_SerialBT.flush();

    return retCode;
}

RC_e BluetoothManager::ExecuteFrame(uint8_t* _buffer){
    RC_e retCode;
    /*initialize*/
    retCode = RC_e::ERROR;

    if(_buffer == NULL)
    {
        return RC_e::ERROR_NULL_POINTER; 
    }
    
    //_buffer[]
    /*if()
    {
        ReturnValue = true;  
    }
    else
    {
        
    }*/

    /*Update*/

    
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

    uint8_t BufferLocal[FRAME_SIZE];
 
    if((retCode=CheckFrame(BufferLocal))!= RC_e::SUCCESS){
        return retCode;
    }

    /*check if the Frame has the Valid Data*/
    /*validData = CheckAllData();
    if(validData == true)
    {
        validRun = true;
    }       */

    return RC_e::SUCCESS;
}