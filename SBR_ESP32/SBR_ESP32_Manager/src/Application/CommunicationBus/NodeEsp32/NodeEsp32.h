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
#include "../RegisterTable/RegisterTable.h"

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
     * @brief Function to connect with a Table Register.
     * 
     * @param tableRegister Reference of a Table Register
     * @return RC_e Result code
     */
    RC_e ConnectRegisterTable(RegisterTable* tableRegister);

private:

    RegisterTable* m_tableRegister = NULL;          /**@brief Reference of Table Register object */

    /**
     * @brief Function to handle a request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e HandleRequest(Request* request);

};

#endif // NODEESP32_H