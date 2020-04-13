#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "BluetoothSerial.h"

class BluetoothManager{

public:
    /*attributes*/
    char* buffer;
    int SizeOfBuffer;
    char* nameDevice;
    int timeout;

    BluetoothManager(char*, int, char*, int);   //constructor
    ~BluetoothManager();                        //Destructor
    
    /*Methods*/
    void configBluetooth();

    void updateBuffer();
    
};

#endif // BLUETOOTH_H