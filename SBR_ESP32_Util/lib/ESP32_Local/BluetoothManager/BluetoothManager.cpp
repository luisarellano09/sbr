#include "BluetoothManager.h"

#define NumberOfBytesNewLine 2                  //at the end always new line [0xD 0xA] or \r\n 

BluetoothSerial SerialBT;

//constructor init attributes
BluetoothManager::BluetoothManager(char* _buffer,int _SizeOfBuffer, char* _nameDevice, int _timeout){
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

void BluetoothManager::updateBuffer(){
    // buffer to know if get the number of bytes corrects
    uint8_t buffer[this->SizeOfBuffer+NumberOfBytesNewLine];    //Buffer with size of requested and 2 last characters \r\n

    if(SerialBT.available()){                           //to know if get something from Register

        /*Initialize the buffer to all zeros*/
        for(int i= 0; i<this->SizeOfBuffer+NumberOfBytesNewLine; i++)
        {
            buffer[i] = 0x00;
        }

        /* Read the buffer with the numers of bytes*/
        SerialBT.readBytes(buffer,this->SizeOfBuffer+2);
    
        if((buffer[this->SizeOfBuffer+NumberOfBytesNewLine-2] == '\r') || (buffer[this->SizeOfBuffer+NumberOfBytesNewLine-1] == '\n')) // 0xD or 0xA
        {
            SerialBT.println("recevied OK");
        }
        else
        {
            SerialBT.println("Error Number of data");
        }
        SerialBT.flush();

    }
}
