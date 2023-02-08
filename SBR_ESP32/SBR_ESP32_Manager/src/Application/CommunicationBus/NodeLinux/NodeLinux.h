/**
 * @file NodeLinux.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the NodeLinux
 * @version 1.0
 * @date 09.01.2021
 * 
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
 * @brief Class to Manage the SPI Master
 * 
 */
class NodeLinux: public Node {
public:  

    /**
     * @brief Construct a new spi mastermanager object
     * 
     */
    NodeLinux(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Destroy the spi mastermanager object
     * 
     */
    ~NodeLinux();

private:

    RC_e HandleRequest(Request* request);

};

#endif // NODELINUX_H