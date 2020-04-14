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
#include "../SBR_Global/Definition/GlobalDef.h"

#define NUMBER_BYTES_NEW_LINE   (uint8_t)2u                  //at the end always new line [0xD 0xA] or \r\n 
#define FRAME_SIZE              (uint8_t)8u                 /*Number of Bytes of the Frame bluetooth*/
#define TIME_OUT                (uint16_t)10000u                 /*Number of Bytes of the Frame bluetooth*/
//####################### class
/**
 * \brief The purpose as well as the members and methos of a class have to be documented.
 *
 * Configuration the Bluetooth.
 */
class BluetoothManager{

public:
    /*attributes*/   
    const char* m_nameDevice;
    
    /*instance*/
    BluetoothSerial m_SerialBT;

    /*****/
    BluetoothManager(const char*);     //constructor
    ~BluetoothManager();                                        //Destructor
    
    /*Methos*/
    void configBluetooth();
   
   
    RC_e CheckFrameAvaible();

    RC_e ComputeCRC(const COM_FRAME_st*);
   
    RC_e CheckFrame(uint8_t*, COM_FRAME_st*);

    RC_e ExecuteFrame(COM_FRAME_st*);

    RC_e Run();  
};


#endif /* BLUETOOTH_H */