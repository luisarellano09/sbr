/**
 * \file doxygen_template.h
 * \author The Author
 * \date 13 Jun 2020
 * \todo TODO for this file.
 *
 * \brief A brief description of the file
 *
 * A more detailed description can be placed here.
 * Multiple lines of description have to start with *.
 *
 * If you want to end a command, add an empty line (starting with *).
 *
 * Inside of a comment block, the user can use doxygen commands like "brief" etc..
 * A list of all available commands can be found at \see https://www.stack.nl/~dimitri/doxygen/manual/commands.html .
 *
 * You can reference to entries in the documentation by using #. Example: #myEnum_t.
 * 
 * 
 * Changes
 * 13.04.2020: Doc was created
 * 
 *
 */

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "BluetoothSerial.h"

//####################### class
/**
 * \brief The purpose as well as the members and methos of a class have to be documented.
 *
 * Configuration the Bluetooth.
 */
class BluetoothManager{

public:
    /*attributes*/   
    char* buffer;
    int SizeOfBuffer;
    char* nameDevice;
    int timeout;

    /*****/
    BluetoothManager(char*, int, char*, int);   //constructor
    ~BluetoothManager();                        //Destructor
    
    /*Methos*/
    void configBluetooth();

    boolean GetAllFrame();

    boolean CheckAllData();
    
};


#endif /* BLUETOOTH_H */