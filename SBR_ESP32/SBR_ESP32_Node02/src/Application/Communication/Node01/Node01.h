/**
 * @file Node01.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief class to Manage the Node01
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */


#ifndef Node01_H
#define Node01_H

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
class Node01: public Node {
public:  

    /**
     * @brief Construct a new spi mastermanager object
     * 
     */
    Node01(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Destroy the spi mastermanager object
     * 
     */
    ~Node01();

    void clear();

    void printtest();

private:

    RC_e HandleRequest(Request* request);

    int test[10000] = {0};
    int index = 0;

};

#endif // Node01_H