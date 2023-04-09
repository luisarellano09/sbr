/**
 * @file NodeLinux.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the NodeLinux
 * 
 */

#ifndef NODELINUX_H
#define NODELINUX_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../../../Middleware/CommunicationBus/Node/Node.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the NodeLinux
 * 
 */
class NodeLinux: public Node {
public:  

    /**
     * @brief Construct a new Node Linux object
     * 
     * @param serial Serial port
     * @param baud Baudrate
     * @param RX RX Pin
     * @param TX TX Pin
     */
    NodeLinux(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Destroy the spi mastermanager object
     * 
     */
    ~NodeLinux();

private:

    /**
     * @brief Handle a request
     * 
     * @param request Request
     * @return RC_e Result code
     */
    RC_e HandleRequest(Request* request);

};

#endif // NODELINUX_H