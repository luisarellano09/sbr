/**
 * @file NodeEsp32.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the NodeEsp32
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
#include "../TableRegister/TableRegister.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the NodeEsp32
 * 
 */
class NodeEsp32: public Node {
public:  

    /**
     * @brief Constructor
     * 
     */
    NodeEsp32(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Destructor
     * 
     */
    ~NodeEsp32();

    /**
     * @brief Function to connect with a Table Register object.
     * 
     * @param tableRegister Reference of a Table Register object
     * @return RC_e Result code
     */
    RC_e ConnectTableRegister(TableRegister* tableRegister);

    /**
     * @brief Function to execute the heart bit monitoring.
     * 
     * @return RC_e Result code
     */
    RC_e HeartBitMonitoring();

private:

    TableRegister* m_tableRegister = NULL;          /**< \brief Reference of Table Register object */

    /**
     * @brief Function to handle a request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e HandleRequest(Request* request);

};

#endif // NodeEsp32_H