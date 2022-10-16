/**
 * @file NodeLinux.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief class to Manage the NodeLinux
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */


/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "NodeLinux.h"

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

NodeLinux::NodeLinux(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX) : Node(serial, baud, RX, TX){    


}

//=====================================================================================================
NodeLinux::~NodeLinux(){}

/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/



/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e NodeLinux::HandleRequest(Request* request){

    request->Print();

    return RC_e::SUCCESS;
}

