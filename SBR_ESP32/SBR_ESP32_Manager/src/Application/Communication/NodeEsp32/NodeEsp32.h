/**
 * @file NodeEsp32.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief class to Manage the NodeEsp32
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */


#ifndef NodeEsp32_H
#define NodeEsp32_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/

#include <Arduino.h>

#include "../../../Middleware/Communication/Node/Node.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the SPI Master
 * 
 */
class NodeEsp32: public Node {
public:  

    /**
     * @brief Construct a new spi mastermanager object
     * 
     */
    NodeEsp32(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Destroy the spi mastermanager object
     * 
     */
    ~NodeEsp32();

private:

    RC_e HandleRequest(Request* request);

};

#endif // NodeEsp32_H