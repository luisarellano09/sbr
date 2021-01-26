/**
 * @file Request.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a request
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

#ifndef Request_H
#define Request_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>

#include "../../../Definition/GlobalDef.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to describe a request
 * 
 */
class Request {
public:  

    uint8_t nodeId;     /**< Node ID. */
    uint8_t reqType;    /**< Request type: Read or Write. */
    uint16_t regId;     /**< Request ID. */
    int32_t data;       /**< Data payload. */
    uint16_t CRC;       /**< Frame consistency. */
   
    /**
     * @brief Constructor
     * 
     */
    Request();

    /**
     * @brief Destructor
     * 
     */
    ~Request();

    /**
     * @brief Clean request
     * 
     * @return RC_e Result code
     */
    RC_e Clean();  

    /**
     * @brief Print request
     * 
     * @return RC_e Result code
     */
    RC_e Print();  

private:


};

#endif // Request_H