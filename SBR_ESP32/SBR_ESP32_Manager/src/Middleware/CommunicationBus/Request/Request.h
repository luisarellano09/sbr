/**
 * @file Request.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a request
 * 
 */

#ifndef REQUEST_H
#define REQUEST_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../../../Definition/Global/RC.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to describe a request
 * 
 */
class Request {
public:  

    uint8_t nodeId;     /**@brief Node ID. */
    uint8_t reqType;    /**@brief Request type: Read or Write. */
    uint16_t regId;     /**@brief Request ID. */
    int32_t data;       /**@brief Data payload. */
    uint16_t CRC;       /**@brief CRC. */
   
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
     * @brief Function to clean the request
     * 
     * @return RC_e Result code
     */
    RC_e Clean();  

    /**
     * @brief Function to print the request
     * 
     * @return RC_e Result code
     */
    RC_e Print();  

private:


};

#endif // REQUEST_H