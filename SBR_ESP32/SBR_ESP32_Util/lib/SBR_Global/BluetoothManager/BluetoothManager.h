/**
 * \file BluetoothManager.cpp
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \author Jorge SALGADO - jorgesalgado23@gmail.com
 * \date 16 April 2020
 *
 * \brief Class to Manage the Bluetooth
 *
 * 
 * 
 * Changes
 * 16.04.2020: Class comments and RC_e concept
 * 13.04.2020: Doc was created
 * 
 *
 */

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

/**
 * \file WifiManager.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 16 April 2020
 *
 * \brief Class to Manage the Wifi
 *
 * 
 * 
 * Changes
 * 16.04.2020: Class comments and RC_e concept
 * 13.04.2020: Doc was created
 * 
 *
 */

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/

#include "BluetoothSerial.h"
#include "../Definition/GlobalDef.h"

#define NUMBER_BYTES_NEW_LINE   (uint8_t)2u                  /*at the end always new line [0xD 0xA] or \r\n */
#define FRAME_SIZE              (uint8_t)8u                 /*Number of Bytes of the Frame bluetooth*/
#define TIME_OUT                (uint16_t)100u              /*the timeout Bluetooth communication  */


#define DEBUG
/*******************************************************************************************************************************************
 *  												WifiManager Class
 *******************************************************************************************************************************************/

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

    RC_e Run();  
   
private:
    RC_e CheckFrameAvaible();

    RC_e ComputeCRC(const COM_FRAME_st*);
   
    RC_e CheckFrame(uint8_t*, COM_FRAME_st*);

    RC_e ExecuteFrame(COM_FRAME_st*);

};


#endif /* BLUETOOTH_H */