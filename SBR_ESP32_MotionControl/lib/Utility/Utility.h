/**
 * \file Utility.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 03.05.2020
 *
 * \brief Library with various functions.
 *
 * 
 * 
 * Changes
 * 03.05.2020: Library was created
 * 
 *
 */

#ifndef UTILITY_H
#define UTILITY_H

/*******************************************************************************************************************************************
 *  												Includes
 *******************************************************************************************************************************************/
#include "../../lib/Definition/GlobalDef.h"

/*******************************************************************************************************************************************
 *  												REQUEST COMMUNICATION
 *******************************************************************************************************************************************/

RC_e RequestToBuffer(COM_REQUEST_st* request, uint8_t* buffer){

    if (request == NULL || buffer == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    buffer[0] = (request->comRequestType & 0x0F) + ((request->comRequestRegId & 0xF00)>>4);
    buffer[1] = (request->comRequestRegId & 0x0FF);
    buffer[2] = (byte)request->data;
    buffer[3] = (byte)(request->data>>8);
    buffer[4] = (byte)(request->data>>16);
    buffer[5] = (byte)(request->data>>24);
    buffer[6] = (byte)request->CRC;
    buffer[7] = (byte)(request->CRC>>8);
    
    return RC_e::SUCCESS;
}

RC_e BufferToRequest(uint8_t* buffer, COM_REQUEST_st* request){

    if (request == NULL || buffer == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // REQUEST
    request->comRequestType = (buffer[0] & 0x0F);

    // ID
    request->comRequestRegId = ((buffer[0] & 0xF0)<<4) + buffer[1];

    // DATA
    request->data = (buffer)[2];
    request->data += (buffer[3])<<8;
    request->data += (buffer[4])<<16;
    request->data += (buffer[5])<<24;

    // CRC
    request->CRC = buffer[6];
    request->CRC += (buffer[7])<<8;

    return RC_e::SUCCESS;
}


















#endif // UTILITY_H