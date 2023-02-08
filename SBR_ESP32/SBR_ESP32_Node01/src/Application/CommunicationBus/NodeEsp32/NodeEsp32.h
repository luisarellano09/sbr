/**
 * @file NodeEsp32.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the NodeEsp32
 * @version 1.0
 * @date 16.10.2022
 * 
 */

#ifndef NODEESP32_H
#define NODEESP32_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../../../Middleware/CommunicationBus/Node/Node.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the Node
 * 
 */
class NodeEsp32: public Node {
public:  

    /**
     * @brief Construct a new mastermanager object
     * 
     */
    NodeEsp32(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Destroy the mastermanager object
     * 
     */
    ~NodeEsp32();

    /**
     * @brief Update Register
     * 
     * @param regId Register ID
     * @param data Data Value
     * 
     * @return RC_e Result code
     */
    RC_e UpdateRegister(COM_REQUEST_REG_ID_e regId, int32_t data);    

private:

    /**
     * @brief Function to handle a request
     * 
     * @param request Reference of a request object
     * 
     * @return RC_e Result code
     */
    RC_e HandleRequest(Request* request);

};

#endif // NodeEsp32_H