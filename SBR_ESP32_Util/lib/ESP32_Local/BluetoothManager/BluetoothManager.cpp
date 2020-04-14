#include "BluetoothManager.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/*instance*/
BluetoothSerial SerialBT;

//####################### class BluetoothManager
/**
 * \brief Configuration the Bluetooth.
 */
BluetoothManager::BluetoothManager( char* buffer,uint8_t SizeOfBuffer, const char* nameDevice, uint8_t timeout){
    /*Set attributes*/
    this->m_buffer = buffer;
    this->m_SizeOfBuffer = SizeOfBuffer;
    this->m_nameDevice = nameDevice;
    this->m_timeout = timeout;

    configBluetooth();

}


BluetoothManager::~BluetoothManager(){}


void BluetoothManager::configBluetooth(){

    SerialBT.begin(this->m_nameDevice);           //name of device bluetooth
    SerialBT.setTimeout(this->m_timeout);         //100 miliseconds
}



boolean BluetoothManager::GetAllFrame(){
    // buffer to know if get the number of bytes corrects
    uint8_t BufferLocal[this->m_SizeOfBuffer+NumberOfBytesNewLine];    //Buffer with size of requested and 2 last characters \r\n
    boolean returnValue;

    /*Initialize*/
    returnValue = false;

    if(SerialBT.available()){                           //to know if get something from Register

        /*Initialize the buffer to all zeros*/
        for(int i= 0; i<this->m_SizeOfBuffer+NumberOfBytesNewLine; i++)
        {
            BufferLocal[i] = 0x00;
        }

        /* Read the buffer with the numers of bytes+2*/
        SerialBT.readBytes(BufferLocal,this->m_SizeOfBuffer+NumberOfBytesNewLine);

        /*Condition to valid the all frame -> the last 2 bytes shall be \r\n */
        if((BufferLocal[this->m_SizeOfBuffer+NumberOfBytesNewLine-2] == '\r') || (BufferLocal[this->m_SizeOfBuffer+NumberOfBytesNewLine-1] == '\n')) // 0xD or 0xA
        {
            /*Copy the Buffer All Data from the buffer local to the Buffer General */
            for(int j= 0; j<this->m_SizeOfBuffer; j++)
            {
                this->m_buffer[j] = (char)BufferLocal[j];
            }
            returnValue = true;         
        }
        else
        {
            
        }
        /*Clean all the register*/
        SerialBT.flush();
    }
    else
    {
        
    }
    return returnValue;
}

boolean BluetoothManager::CheckAllData(){
    boolean ReturnValue;
    char Byte0;
    char Byte1;
    char Byte2;
    char Byte3;

    /*initialize*/
    ReturnValue = false;
    Byte0 = (this->m_buffer[0]);
    Byte1 = (this->m_buffer[1]);
    Byte2 = (this->m_buffer[2]);
    Byte3 = (this->m_buffer[3]);

    if((Byte0 == 'A')&&(Byte1 == 'B')&&(Byte2 == 'C')&&(Byte3 == 'A'))
    {
         ReturnValue = true;  
    }
    else
    {
        
    }
    
    return ReturnValue; 
}

boolean BluetoothManager::Run(){
    
    boolean validframe;
    boolean validData;
    boolean validRun;
    
    /*initialize variables*/
    validframe = false;
    validData = false;
    validRun = false;

    /*check if the RX has the number of Byte configured in the frame received (NumberOfBytes)*/
    validframe = GetAllFrame();

    if(validframe == true)
    {
        /*check if the Frame has the Valid Data*/
        validData = CheckAllData();
        if(validData == true)
        {
            validRun = true;
        }       
    }
    else
    {
        /*Nothing to do*/
    }
    return validRun;
}