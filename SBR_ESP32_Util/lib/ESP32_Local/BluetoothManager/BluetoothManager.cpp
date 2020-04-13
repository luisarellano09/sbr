#include "BluetoothManager.h"

#define NumberOfBytesNewLine 2                  //at the end always new line [0xD 0xA] or \r\n 

BluetoothSerial SerialBT;

//####################### class
/**
 * \brief The purpose as well as the members and methos of a class have to be documented.
 *
 * Configuration the Bluetooth.
 */
BluetoothManager::BluetoothManager( char* _buffer,int _SizeOfBuffer, char* _nameDevice, int _timeout){
    this->buffer = _buffer;
    this->SizeOfBuffer = _SizeOfBuffer;
    this->nameDevice = _nameDevice;
    this->timeout = _timeout;

    configBluetooth();

}
BluetoothManager::~BluetoothManager(){}

void BluetoothManager::configBluetooth(){
    SerialBT.begin(this->nameDevice);           //name of device bluetooth
    SerialBT.setTimeout(this->timeout);         //100 miliseconds
}

boolean BluetoothManager::GetAllFrame(){
    // buffer to know if get the number of bytes corrects
    uint8_t BufferLocal[this->SizeOfBuffer+NumberOfBytesNewLine];    //Buffer with size of requested and 2 last characters \r\n
    boolean returnValue;

    /*Initialize*/
    returnValue = false;

    if(SerialBT.available()){                           //to know if get something from Register

        /*Initialize the buffer to all zeros*/
        for(int i= 0; i<this->SizeOfBuffer+NumberOfBytesNewLine; i++)
        {
            BufferLocal[i] = 0x00;
        }

        /* Read the buffer with the numers of bytes*/
        SerialBT.readBytes(BufferLocal,this->SizeOfBuffer+NumberOfBytesNewLine);

        /*Condition to valid the all frame -> the last 2 bytes shall be \r\n */
        if((BufferLocal[this->SizeOfBuffer+NumberOfBytesNewLine-2] == '\r') || (BufferLocal[this->SizeOfBuffer+NumberOfBytesNewLine-1] == '\n')) // 0xD or 0xA
        {
            /*Copy the Buffer All Data from the buffer local to the Buffer General */
            for(int j= 0; j<this->SizeOfBuffer; j++)
            {
                this->buffer[j] = (char)BufferLocal[j];
            }
            returnValue = true;         
        }
        else
        {
            returnValue = false;
        }
        /*Clean all the register*/
        SerialBT.flush();
    }
    else
    {
        returnValue = false;
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
    Byte0 = (this->buffer[0]);
    Byte1 = (this->buffer[1]);
    Byte2 = (this->buffer[2]);
    Byte3 = (this->buffer[3]);

    if((Byte0 == 'A')&&(Byte1 == 'B')&&(Byte2 == 'C')&&(Byte3 == 'A'))
    {
         ReturnValue = true;  
    }
    else
    {
        
    }
    
    return ReturnValue; 
}