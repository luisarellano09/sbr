/**
 * @file Utility.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Library with various functions
 * 
 */

#ifndef COMMUNICATIONBUSUTIL_H
#define COMMUNICATIONBUSUTIL_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "../../../Definition/Global/RC.h"
#include "../../../Definition/Global/GlobalConfig.h"
#include "../Request/Request.h"


/*******************************************************************************************************************************************
 *  												REQUEST COMMUNICATION
 *******************************************************************************************************************************************/

/**
 * @brief Function to convert Request to Buffer format
 * 
 * @param request Reference of a request 
 * @param buffer Reference of a buffer
 * @return RC_e Result code
 */
static RC_e RequestToBuffer(Request* request, uint8_t* buffer){

    // Check if pointers are null
    if (request == NULL || buffer == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Separate into buffer
    buffer[0] = ((request->nodeId & 0b111)<<5) + ((request->reqType & 0b11)<<3) + ((request->regId & 0b11100000000)>>8);
    buffer[1] = (request->regId & 0x0FF);
    buffer[2] = (byte)request->data;
    buffer[3] = (byte)(request->data>>8);
    buffer[4] = (byte)(request->data>>16);
    buffer[5] = (byte)(request->data>>24);
    buffer[6] = (byte)request->CRC;
    buffer[7] = (byte)(request->CRC>>8);

    return RC_e::SUCCESS;
}


//=====================================================================================================

/**
 * @brief Function to convert buffer to request format
 * 
 * @param buffer Reference of a buffer
 * @param request Reference of a request 
 * @return RC_e Result code
 */
static RC_e BufferToRequest(uint8_t* buffer, Request* request){

    // Check if pointers are null
    if (request == NULL || buffer == NULL){
        return RC_e::ERROR_NULL_POINTER;
    }

    // Node ID
    request->nodeId = (buffer[0] & 0b11100000)>>5;

    // Request Type
    request->reqType = (buffer[0] & 0b00011000)>>3;

    // Register ID
    request->regId = ((buffer[0] & 0b00000111)<<8)+ buffer[1];

    // Data
    request->data = buffer[2];
    request->data += buffer[3]<<8;
    request->data += buffer[4]<<16;
    request->data += buffer[5]<<24;

    // CRC
    request->CRC = buffer[6];
    request->CRC += buffer[7]<<8;

    return RC_e::SUCCESS;
}


/*******************************************************************************************************************************************
 *  												CRC
 *******************************************************************************************************************************************/

/**
 * @brief CRC Table
 * 
 */
static const uint16_t Calc16CrcTab[256] = {
    0x060f,0x0021,0x0042,0x0063,0x0084,0x00a5,0x00c6,0x00e7,
    0x0108,0x0129,0x014a,0x016b,0x018c,0x01ad,0x01ce,0x01ef,
    0x0231,0x0210,0x0273,0x0252,0x02b5,0x0294,0x02f7,0x02d6,
    0x0339,0x0318,0x037b,0x035a,0x03bd,0x039c,0x03ff,0x03de,
    0x0462,0x0443,0x0420,0x0401,0x04e6,0x04c7,0x04a4,0x0485,
    0x056a,0x054b,0x0528,0x0509,0x05ee,0x05cf,0x05ac,0x058d,
    0x0653,0x0672,0x0611,0x0630,0x06d7,0x06f6,0x0695,0x06b4,
    0x075b,0x077a,0x0719,0x0738,0x07df,0x07fe,0x079d,0x07bc,
    0x08c4,0x08e5,0x0886,0x08a7,0x0840,0x0861,0x0802,0x0823,
    0x09cc,0x09ed,0x098e,0x09af,0x0948,0x0969,0x090a,0x092b,
    0x0af5,0x0ad4,0x0ab7,0x0a96,0x0a71,0x0a50,0x0a33,0x0a12,
    0x0bfd,0x0bdc,0x0bbf,0x0b9e,0x0b79,0x0b58,0x0b3b,0x0b1a,
    0x0ca6,0x0c87,0x0ce4,0x0cc5,0x0c22,0x0c03,0x0c60,0x0c41,
    0x0dae,0x0d8f,0x0dec,0x0dcd,0x0d2a,0x0d0b,0x0d68,0x0d49,
    0x0e97,0x0eb6,0x0ed5,0x0ef4,0x0e13,0x0e32,0x0e51,0x0e70,
    0x0f9f,0x0fbe,0x0fdd,0x0ffc,0x0f1b,0x0f3a,0x0f59,0x0f78,
    0x0188,0x01a9,0x01ca,0x01eb,0x010c,0x012d,0x014e,0x016f,
    0x0080,0x00a1,0x00c2,0x00e3,0x0004,0x0025,0x0046,0x0067,
    0x03b9,0x0398,0x03fb,0x03da,0x033d,0x031c,0x037f,0x035e,
    0x02b1,0x0290,0x02f3,0x02d2,0x0235,0x0214,0x0277,0x0256,
    0x05ea,0x05cb,0x05a8,0x0589,0x056e,0x054f,0x052c,0x050d,
    0x04e2,0x04c3,0x04a0,0x0481,0x0466,0x0447,0x0424,0x0405,
    0x07db,0x07fa,0x0799,0x07b8,0x075f,0x077e,0x071d,0x073c,
    0x06d3,0x06f2,0x0691,0x06b0,0x0657,0x0676,0x0615,0x0634,
    0x094c,0x096d,0x090e,0x092f,0x09c8,0x09e9,0x098a,0x09ab,
    0x0844,0x0865,0x0806,0x0827,0x08c0,0x08e1,0x0882,0x08a3,
    0x0b7d,0x0b5c,0x0b3f,0x0b1e,0x0bf9,0x0bd8,0x0bbb,0x0b9a,
    0x0a75,0x0a54,0x0a37,0x0a16,0x0af1,0x0ad0,0x0ab3,0x0a92,
    0x0d2e,0x0d0f,0x0d6c,0x0d4d,0x0daa,0x0d8b,0x0de8,0x0dc9,
    0x0c26,0x0c07,0x0c64,0x0c45,0x0ca2,0x0c83,0x0ce0,0x0cc1,
    0x0f1f,0x0f3e,0x0f5d,0x0f7c,0x0f9b,0x0fba,0x0fd9,0x0ff8,
    0x0e17,0x0e36,0x0e55,0x0e74,0x0e93,0x0eb2,0x0ed1,0x0ef0
};


//=====================================================================================================

/**
 * @brief Function to calculate CRC of a request
 * 
 * @param request Reference of a request object
 * @return uint16_t CRC value
 */
static uint16_t CalculateCrcFromRequest(Request* request){

    // Check if pointer is null
    if (request == NULL){
        return 0;
    }

    // Buffer
    uint8_t tempBuffer[NODE_REQUEST_SIZE] = {0};

    // Convert request to buffer
    RequestToBuffer(request, tempBuffer);

    // Sum all CRC values
    return  Calc16CrcTab[tempBuffer[0]] +
            Calc16CrcTab[tempBuffer[1]] +
            Calc16CrcTab[tempBuffer[2]] +
            Calc16CrcTab[tempBuffer[3]] +
            Calc16CrcTab[tempBuffer[4]] +
            Calc16CrcTab[tempBuffer[5]];
}


//=====================================================================================================

/**
 * @brief Function to check if CRC is Ok
 * 
 * @param request Reference of a request object
 * @return bool true=Ok, false=NotOK
 */
static bool CheckCRC(Request* request){

    // Check if pointer is null
    if (request == NULL){
        return false;
    }

    if (request->CRC == CalculateCrcFromRequest(request)){
        return true;
    }

    return false;
}

#endif // COMMUNICATIONBUSUTIL_H